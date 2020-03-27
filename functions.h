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


void padding(unsigned char *msg, int msgSize)
{
    // How much we need to pad the msg
    int padSize = (BLOCK_SIZE - msgSize) % BLOCK_SIZE;

    if (padSize == 0)
        padSize = BLOCK_SIZE;

    int start = msgSize;
    for (int idx = 0; idx < padSize; idx++)
        msg[start++] = 0;
}


#endif // !FUNCTIONS_H
