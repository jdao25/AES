#ifndef FUNCTIONS_H
#define FUNCTIONS_H

std::string removeSpacing(const std::string&);
void padding();  // PKCS5 will be used

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


void padding()
{

}


#endif // !FUNCTIONS_H
