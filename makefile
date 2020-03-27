CC=g++

compile:
	@clear
	@$(CC) main.cpp -o AES128Encrypt && ./AES128Encrypt ~/Desktop/Test.txt

atom:
	@clear
	@cd .. && atom AES && cd AES
