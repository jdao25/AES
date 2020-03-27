#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <cstring>

std::string removeSpacing(const std::string&);
void padding(unsigned char *, int);   // PKCS5 will be used


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


void padding(unsigned char *message, int msgSize)
{
    // How much we need to pad the msg
    int padSize = (BLOCK_SIZE - msgSize) % BLOCK_SIZE;

    if (padSize == 0)
        padSize = BLOCK_SIZE;

    unsigned char value = (unsigned char)padSize;

    int start = msgSize;
    for (int idx = 0; idx < padSize; idx++)
        message[start++] = value;
}


unsigned char *PKCS5Padding(unsigned char *message)
{
    int messageLen = std::strlen((char *)message);
    int paddingSize = BLOCK_SIZE - (messageLen % BLOCK_SIZE);
    unsigned char* paddedMessage = (unsigned char *) malloc(messageLen + paddingSize);

    // Copy the message to paddedMessage
    memcpy(paddedMessage, message, messageLen);

    for (int idx = messageLen; idx < (messageLen + paddingSize); idx++)
    	paddedMessage[idx] = paddingSize;

    return paddedMessage;
}


#endif // !FUNCTIONS_H
