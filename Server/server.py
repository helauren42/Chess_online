import sqlite3
import fastapi
from pydantic import BaseModel
import json
from fastapi import Response, WebSocket
from fastapi.responses import JSONResponse
from asyncio import Queue
import asyncio
import random

connect = sqlite3.connect("database.db")
cursor = connect.cursor()

connections = {}

cursor.execute("CREATE TABLE IF NOT EXISTS accounts ( \
				id NOT NULL, \
				username CHAR(25) NOT NULL, \
				password CHAR(25) NOT NULL, \
			dob TEXT NOT NULL)")

cursor.execute("CREATE TABLE IF NOT EXISTS online ( \
				id INTEGER NOT NULL, \
				username CHAR(25) NOT NULL)")

app = fastapi.FastAPI()

def addOnline(add_id: int, add_user: str, ws: WebSocket):
	cursor.execute("SELECT username FROM online")
	usernames = cursor.fetchall()
	for username in usernames:
		if username[0] == add_user:
			print("already online")
			return
	connections[add_user] = ws
	print("adding to online table: ", add_user)
	cursor.execute("INSERT INTO online (id, username) VALUES (?, ?)", (add_id, add_user))
	connect.commit()
	connections

def rmOnline(rm_user: str) -> bool:
	print("rm online: ", rm_user)
	cursor.execute("SELECT username FROM online")
	usernames = cursor.fetchall()
	for username in usernames:
		if username[0] == rm_user:
			connections.pop(rm_user)
			cursor.execute("DELETE FROM online WHERE username = ?", (rm_user, ))
			connect.commit()
			return True
	return False

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
		cursor.execute("SELECT username FROM accounts")
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
		cursor.execute("SELECT password FROM accounts")
		passwords = cursor.fetchall()
		if(passwords[id -1][0] == search):
			return True
		return False

@app.get("/online_players")
async def menu(request: fastapi.Request):
	ret = {}
	i = 0
	for username in connections.keys():
		ret[i] = username
		i+=1
	return JSONResponse(
		status_code=200,
		content = ret
	)

@app.get("/")
async def home(request: fastapi.Request):
	return JSONResponse(
		status_code=200,
		content = {"message": "you are at home"}
	)

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
			print("length not correct")
			return JSONResponse(
				status_code=401,
				content={"message": "Lengths must be between 5 and 25"}
			)
		if not Validate.userValidCharacters(username):
			print("user unvalid characters found")
			return JSONResponse(
				status_code=401,
				content={"message": "Username allows a-z, A-Z, 0-9, _ and -."}
			)
		if Validate.findUserId(username) >= 0:
			print("user nane already taken")
			return JSONResponse(
					status_code=401,
					content={"message": "Username already taken"}
			)
	except Exception as e:
		print(f"Signup failed invalid request: {e}")
		return JSONResponse(
			status_code=404,
			content = {"message": "sign up invalid request"}
		)

	# insertion to db
	try:
		cursor.execute("SELECT COUNT(*) FROM accounts")
		result = cursor.fetchone()
		id = str(result[0])
		cursor.execute("INSERT INTO accounts (id, username, password, dob) VALUES (?, ?, ?, ?)", (id, username, password, dob))
		connect.commit()
		print("id", f"{id}", "message", "Signup successful")
		return {"id": f"{id}", "message": "Signup successful"}
	except Exception as e:
		print("!!!!", e)
		return JSONResponse(
			status_code=404,
			content={"message": "Failed connecting to db"}
		)

@app.post("/challenge")	
async def challenge(request: fastapi.Request):
	body = await request.json()
	challenger = body.get("challenger")
	challenged = body.get("challenged")
	challenged_id = Validate.findUserId(challenged)
	if challenged_id < 0:
		return JSONResponse(
			status_code=401,
			content={"message":"Challenged player not online"}
		)
	return JSONResponse(
		status_code=200,
		content={"message":"Challenge sent to player"}
	)

@app.post("/logout")
async def logout(request: fastapi.Request, response: Response):
	body = await request.json()
	print("logout BODY: ", body)
	username = body.get("username")

	if not rmOnline(username):
		print("Could not log out: ", username)
		return {"message": "Log out failed"}
	await updateOnlinePlayersClientSide()
	print("Logged out successful")
	return {"message": "Log out successful"}

@app.post("/login")
async def login(request: fastapi.Request, response: Response):
	body = await request.json()
	print("response body: ", body)
	username = body.get("username")
	id = Validate.findUserId(username) # verifies user is in db and retrieves his id
	print("id: ", id)
	if(id < 0):
		print("user could not be found")
		return JSONResponse(
			status_code=401,
			content={"message": "Wrong Credentials"}
		)
	cursor.execute("SELECT username FROM online")
	names = cursor.fetchall()
	for name in names:
		if name[0] == username:
			print("Login failed: User already logged in")
			return JSONResponse(
				status_code=401,
				content={"message": "User already logged in"}
			)

	password = body.get("password")
	if not Validate.loginValidPassword(password, id):
		print("password does not match username")
		return JSONResponse(
			status_code=401,
			content={"message": "Wrong Credentials"}
		)
	print("Logging in successful")
	return {"id:": f"{id}", "message": "Login successful"}

async def messageAll(message: str):
	print("message all: ", message)
	for ws in connections.values():
		print("ws: ", ws)
		await ws.send_text(message)

async def updateOnlinePlayersClientSide():
	print("update online players client side: ", connections)
	await messageAll("update connections")
	# for ws in connections.values():
		# ws.send_text("update connection")

opponents = {}
active_games = []
game_ws = {}
game_message_queues = {}

@app.websocket("/ws/game/{id}/{user}")
async def gameConnection(ws: WebSocket, id: str, user: str):
	print("game websocket connection: ", id)
	await ws.accept()
	game_ws[user] = ws
	game_list = id.split("-")
	challenger = game_list[0]
	challenged = game_list[1]
	game = (challenger, challenged)
	game_message_queues[user] = Queue()
	if game not in active_games:
		print("appending game")
		print("challenger: ", challenger)
		print("challenged: ", challenged)
		active_games.append(game)
	print("connection accepted")

	async def game_send_messages():
		while True:
			message = await game_message_queues[user].get()
			print("game sending message: ", message)
			print("to: ", user)
			await ws.send_text(message)
			print("sent")

	asyncio.create_task(game_send_messages())

	try:
		while True:
			data = await ws.receive_text()
			jsonData = json.loads(data)
			type: str = jsonData.get("type")
			if type == "click":
				sender = jsonData["from"]
				receiver = challenger if challenged == sender else challenged
				print("game message to: ", receiver)
				await game_message_queues[receiver].put(
					json.dumps({"type": "make click", "x": jsonData.get("x"), "y": jsonData.get("y")})
				)
	except Exception as e:
		print("disconnected from game: ", e)

message_queues = {}

@app.websocket("/ws/{user}")
async def WebsocketConnection(ws: WebSocket, user: str):
	print("websocketconnections 1")
	await ws.accept()
	print("ws User: ", user, "accepted connection")
	id = Validate.findUserId(user)
	await updateOnlinePlayersClientSide()
	connections[user] = ws
	message_queues[user] = Queue()

	addOnline(id, user, ws)

	async def send_messages():
		"""Background task to send messages from the queue to the WebSocket."""
		while True:
			message = await message_queues[user].get()
			print("sending message: ", message)
			print("to: ", user)
			await ws.send_text(message)
			print("sent")

	send_task = asyncio.create_task(send_messages())

	try:
		while True:
			data = await ws.receive_text()
			print("ws received: ", data)
			print("from: ", user)
			jsonData = json.loads(data)
			type = jsonData.get("type")

			if type == "challenge":
				print("is challenge")
				challenged_user = jsonData.get("challenged")
				if challenged_user in connections and challenged_user != user:
					print(f"I {challenged_user} have been challenged by {jsonData.get('challenger')}")
					# Add the challenge message to the challenged user's queue
					color = "white" if random.choice([True, False]) else "black"
					await message_queues[challenged_user].put(
						json.dumps({"type": "challenge", "from": user, "color": color})
					)
			if type == "invite answer" and jsonData.get("answer") == "accept":
				challenged = jsonData.get("challenged")
				challenger = jsonData.get("challenger")
				color = "white" if jsonData.get("color") == "black" else "black"
				await message_queues[challenger].put(
					json.dumps({"type": "start online game", "opponent": challenged, "color": color})
				)

	except Exception as e:
		print(f"{user} disconnected")
		print("Exception: ", e)
	finally:
		# Clean up resources
		rmOnline(user)
		await updateOnlinePlayersClientSide()
		connections.pop(user, None)
		message_queues.pop(user, None)
		send_task.cancel()
