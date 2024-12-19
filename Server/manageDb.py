import sqlite3
import fastapi
import sys

connect = sqlite3.connect("database.db")
cursor = connect.cursor()

ERROR = "Provide an argument, format: ./script.py accounts / online"

# def listOnline():

def rmOnline():
	cursor.execute("DROP TABLE IF EXISTS online")

def listOnline():
	cursor.execute("SELECT * FROM online")
	print("\nONLINE:\n")
	all = cursor.fetchall()
	for account in all:
		print(account)

def listDb():
	cursor.execute("SELECT * FROM accounts")
	print("\nACCOUNTS:\n")
	all = cursor.fetchall()
	for account in all:
		print(account)

def main():
	if len(sys.argv) != 2:
		print(ERROR)
		sys.exit(1)
	arg = sys.argv[1]
	match arg:
		case "accounts":
			listDb()
		case "online":
			listOnline()
		case "rmonline":
			rmOnline()
		case _:
			print(ERROR)
			sys.exit(1)

if __name__ == "__main__":
	main()
