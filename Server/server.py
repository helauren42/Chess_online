import sqlite3
import fastapi
from pydantic import BaseModel
from fastapi import Response
from fastapi.responses import JSONResponse

connect = sqlite3.connect("database.db")
cursor = connect.cursor()

cursor.execute("CREATE TABLE IF NOT EXISTS account ( \
				id INTEGER PRIMARY KEY AUTOINCREMENT, \
				username CHAR(25) NOT NULL,\
				password CHAR(25) NOT NULL, \
			dob TEXT NOT NULL)")

app = fastapi.FastAPI()

class Validate():

	def correctLength(s: str) -> bool:
		if len(s) < 5 or len(s) > 25:
			return False
		return True

	def userValidCharacters(user: str) -> bool:
		for c in user:
			if not c.isalnum() and c != "_" and c != "-":
				return False
		return True
	
	def findUserId(search : str) -> int:
		print("find user id")
		cursor.execute("SELECT username FROM account")
		usernames = cursor.fetchall()
		id:int = 1
		for user in usernames:
			if(user[0] == search):
				print("found: ", user[0])
				return id
			id += 1
		return -1

	def loginValidPassword(search : str, id : int) -> bool:
		print("valid password")
		cursor.execute("SELECT password FROM account")
		passwords = cursor.fetchall()
		if(passwords[id -1][0] == search):
			return True
		return False

@app.get("/")
async def home(request: fastapi.Request):
	return {"message": "GET Hello World Your Home Baby"}

@app.post("/login")
async def home(request: fastapi.Request, response: Response):

	body = await request.json()
	print("!!!BODY: ", body)
	username = body.get("username")
	id = Validate.findUserId(username) # verifies user is in db and retrieves his id
	print("id: ", id)
	if(id < 0):
		return JSONResponse(
			status_code=401,
			content={"message": "Wrong Credentials"}
		)

	password = body.get("password")

	if not Validate.loginValidPassword(password, id):
		return JSONResponse(
			status_code=401,
			content={"message": "Wrong Credentials"}
		)
	return {"message": "Login successful"}

@app.post("/signup")
async def signup(request: fastapi.Request):
	# parse and check
	try:
		body = await request.json()
		print("body: ", body)
		username = body.get("username")
		password = body.get("password")
		dob = body.get("dob")
		if not Validate.correctLength(username) or not Validate.correctLength(password):
			return JSONResponse(
				status_code=401,
				content={"message": "Lengths must be between 5 and 25"}
			)
		if not Validate.userValidCharacters(username):
			return JSONResponse(
				status_code=401,
				content={"message": "Username allows a-z, A-Z, 0-9, _ and -."}
			)
		if Validate.findUserId(username) >= 0:
			return JSONResponse(
					status_code=401,
					content={"message": "Username already taken"}
			)
	except Exception as e:
		print(f"Signup failed invalid request: {e}")
		return {"message": "invalid request"}

	# insertion to db
	try:
		cursor.execute("SELECT COUNT(*) FROM account")
		result = cursor.fetchone()
		id = str(result[0])
		cursor.execute("INSERT INTO account (id, username, password, dob) VALUES (?, ?, ?, ?)", (id, username, password, dob))
		connect.commit()
		print("id", f"{id}", "message", "Signup successful")
		return {"id": f"{id}", "message": "Signup successful"}
	except Exception as e:
		print("!!!!", e)
		return {"message": "Failed connecting to db"}

# @app.delete("delete_account")
# async def delete_account(request: fastapi.Request):
# 	try:
# 		body = await request.json()
# 		#  use id to delete account I guess
# 	except Exception as e:
# 		print(e)
# 		return {"message": "Invalid request"}