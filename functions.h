#ifndef FUNCTIONS_H
#define FUNCTIONS_H


unsigned char *PKCS5Padding(unsigned char *, int);  // Padding the plaintext
void convertCharToHex(const std::string&);  // This is used to convert the key's hex values


// This function is supposed to pad using PKCS5
unsigned char *PKCS5Padding(unsigned char *message, int messageLen)
{
    int paddingSize = BLOCK_SIZE - (messageLen % BLOCK_SIZE);
    unsigned char* paddedMessage = (unsigned char *) malloc(messageLen + paddingSize);

    // Copy the message to paddedMessage
    memcpy(paddedMessage, message, messageLen);

    for (int idx = messageLen; idx < (messageLen + paddingSize); idx++)
    	paddedMessage[idx] = paddingSize;

    return paddedMessage;
}


// Convert the key's hex values 
void convertCharToHex(const std::string& inputKey, unsigned char *key)
{
    std::istringstream hexStream(inputKey);

    unsigned int c;
    int idx = 0;
    while (hexStream >> std::hex >> c)
        key[idx++] = c;
}


#endif // !FUNCTIONS_H
