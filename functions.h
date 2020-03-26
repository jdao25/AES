#ifndef FUNCTIONS_H
#define FUNCTIONS_H

std::string removeSpacing(const std::string&);
void padding();  // PKCS5 will be used
// unsigned char* PKCS5Padding(char *strParams, int unBlockSize);


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


#endif // !FUNCTIONS_H
