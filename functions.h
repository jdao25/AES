#ifndef FUNCTIONS_H
#define FUNCTIONS_H


std::string removeSpacing(const std::string&);
unsigned char *PKCS5Padding(unsigned char *, int);


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


#endif // !FUNCTIONS_H
