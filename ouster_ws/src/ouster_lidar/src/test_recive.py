import socket, json

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('localhost', 8080))

data, addr = sock.recvfrom(200)



while 1:
	data = pickle.load(data)
	print ("Server is recived data: ", data.decode())
	print ("Send Client IP: ", addr[0])
	print ("Send Client Port: ", addr[1])

