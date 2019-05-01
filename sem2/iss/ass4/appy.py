import random

def rando():
	ret = ""
	for i in range(5):
		ret += str(random.randint(0,1))
	return ret