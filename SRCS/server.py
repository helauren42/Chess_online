import fastapi
import logging

logging.basicConfig(level=logging.DEBUG)

app = fastapi.FastAPI()

@app.get("/")
def index():
	return {"message": "Hello World"}

	# def __init__(self):
	# 	super(Account, self).__init__(prefix="/account")
# class Account(fastapi.APIRouter):
	# 	@self.get("/")
	# 	def index():
	# 		return {"message": "Account page"}
