compile:
	@clear
	@g++ main.cpp -o AES128Encrypt && ./AES128Encrypt

atom:
	@clear
	@cd .. && atom AES && cd AES