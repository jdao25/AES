#ifndef FUNCTIONS_H
#define FUNCTIONS_H


std::string removeSpacing(const std::string&);
unsigned char *PKCS5Padding(unsigned char *, int);
void convertCharToHex(const std::string&);


std::string removeSpacing(const std::string& key)
{
    std::string newKey;
    for (int idx = 0; idx < key.length(); idx++)
    {
        if (key[idx] != ' ')
            newKey += key[idx];
    }

    return newKey;
}


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


void convertCharToHex(const std::string& inputKey, unsigned char *key)
{
    // Given that inputKey is the original user key input

    std::istringstream hexStream(inputKey);

    unsigned int c;
    int idx = 0;
    while (hexStream >> std::hex >> c)
        key[idx++] = c;
}


#endif // !FUNCTIONS_H
