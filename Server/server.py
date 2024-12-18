import sqlite3
import fastapi

connect = sqlite3.connect("database.db")
cursor = connect.cursor()

app = fastapi.FastAPI()

@app.get("/")
async def home(request: fastapi.Request):
	return {"message": "Hello World Your Home Baby"}

@app.post("/signup")
async def signup(request: fastapi.Request):
	body = await request.json()
	username = body.get("username")
	password = body.get("password")
	dob = body.get("dob")
	print("message: ", "Signup successful")
	return {"message": "Signup successful"}
