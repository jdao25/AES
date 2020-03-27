#ifndef FUNCTIONS_H
#define FUNCTIONS_H

std::string removeSpacing(const std::string&);
void padding(unsigned char *, int);   // PKCS5 will be used
std::string convertToHex(int);


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

    std::string hexVal = convertToHex(padSize);
    std::string padding;

    for (int idx = 0; idx < padSize; idx++)
        padding += hexVal;

    int start = msgSize;
    for (int idx = 0; idx < padding.length(); idx++)
        msg[start++] = padding[idx];

    int newSize = padding.length() + msgSize;

    std::cout << newSize << std::endl;

}


std::string convertToHex(int padSize)
{
    if (padSize == 16)
        return "10";

    std::string hex;
    char hexVals[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    int idx = padSize;
    while (idx > 0)
    {
        int r = idx % 16;
        hex = hexVals[r] + hex;
        idx = padSize / 16;
    }

    return "0" + hex;
}


#endif // !FUNCTIONS_H
