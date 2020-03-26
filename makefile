CC=g++

compile:
	@clear
	@$(CC) main.cpp -o AES128Encrypt && ./AES128Encrypt ~/Desktop/Python_Assessment_Test

atom:
	@clear
	@cd .. && atom AES && cd AES
