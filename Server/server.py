import sqlite3
import fastapi

connect = sqlite3.connect("database.db")
cursor = connect.cursor()

app = fastapi.FastAPI()

@app.get("/")
async def home(request: fastapi.Request):
	return {"message": "GET Hello World Your Home Baby"}

@app.post("/signup")
async def signup(request: fastapi.Request):
	print(request.headers)
	try:
		body = await request.json()
		print("body: ", body)
		username = body.get("username")
		password = body.get("password")
		dob = body.get("dob")
	except Exception as e:
		print(e)
		return {"message": "Invalid request"}

	print("message: ", "Signup successful")
	return {"message": "Signup successful"}
