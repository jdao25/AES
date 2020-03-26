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


// char * right_pad_str(char * str, unsigned int pad_len)
// {
//     const unsigned int str_len = std::strlen(str);
//     unsigned int padded_str_len = str_len;
//
//     if (padded_str_len % pad_len != 0)
//         padded_str_len = (padded_str_len / pad_len + 1) * pad_len;
//
//     unsigned char *padded_str = malloc(padded_str_len);
//
//     for (int i = 0; i < padded_str_len; i++)
//     {
//         if (i >= str_len) padded_str[i] = 0;
//         else padded_str[i] = str[i];
//     }
//
//     return padded_str;
// }


// unsigned char* PKCS5Padding(char *strParams, int unBlockSize)
// {
//     int nRaw_size = std::strlen(strParams);
//     int i = 0, j = nRaw_size / 8 + 1, k = nRaw_size % 8;
//     int nPidding_size = 8 - k;
//     unsigned char* szArray;
//
//     szArray = (unsigned char *) malloc(nRaw_size + nPidding_size);
//     memcpy(szArray, strParams, nRaw_size);
//
//     for (int i1 = nRaw_size; i1 < (nRaw_size + nPidding_size); i1++)
//     {
//     	szArray[i1] = nPidding_size;
//     }
//
//     return szArray;
// }


#endif // !FUNCTIONS_H
