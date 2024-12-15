import fastapi
import logging

logging.basicConfig(level=logging.DEBUG)

app = fastapi.FastAPI()

@app.post("/signup")
def index():
	return {"message": "Hello World"}

