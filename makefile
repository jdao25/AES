CC=g++

compile:
	@clear
	@$(CC) main.cpp -o AES128Encrypt && ./AES128Encrypt

atom:
	@clear
	@cd .. && atom AES && cd AES
