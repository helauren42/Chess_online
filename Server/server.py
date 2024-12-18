import sqlite3
import fastapi

connect = sqlite3.connect("database.db")
cursor = connect.cursor()

cursor.execute("CREATE TABLE IF NOT EXISTS account (\
				id INTEGER PRIMARY KEY AUTOINCREMENT, \
				username CHAR(25) NOT NULL,\
				password CHAR(25) NOT NULL, \
			dob TEXT NOT NULL)")

app = fastapi.FastAPI()

@app.get("/")
async def home(request: fastapi.Request):
	return {"message": "GET Hello World Your Home Baby"}

@app.get("/login")
async def home(request: fastapi.Request):
	return {"message": "GET Hello World Your Home Baby"}

@app.post("/signup")
async def signup(request: fastapi.Request):
	try:
		body = await request.json()
		print("body: ", body)
		username = body.get("username")
		password = body.get("password")
		dob = body.get("dob")
	except Exception as e:
		print(e)
		return {"message": "Invalid request"}

	try:
		cursor.execute("SELECT COUNT(*) FROM account")
		result = cursor.fetchone()
		id = str(result[0])
		cursor.execute("INSERT INTO account (id, username, password, dob) VALUES (?, ?, ?, ?)", (id, username, password, dob))
		return {"id": f"{id}", "message": "Signup successful"}
	except Exception as e:
		print("!!!!", e)
		return {"message": "Signup failed"}
