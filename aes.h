#ifndef AES_H
#define AES_H

// Headers 
#include <iostream>
#include <fstream>
#include <map>

#ifdef _WIN32
#include <string>   // This is for the getline function to read key for Windows
#endif // ! _WIN32

#include "constants.h"


// Functions Declarations
void gFunction(unsigned char *, unsigned char); // Will be used in keyExpansion
void keyExpansion(unsigned char *, unsigned char *); // Expand key to 176 bytes. 16 bytes per round. 11 rounds
void keyAddition(unsigned char *, unsigned char *); // XOR Round key with state
void byteSubstitution(unsigned char *); // replace bytes with value in sbox
void shiftRows(unsigned char *); // Shift rows
void  mixColumns(unsigned char *); // Matrix multiplication  column with given matrix


void gFunction(unsigned char *in, unsigned char rcon_iter)
{
    unsigned int * q = (unsigned int *) in;
    // Left rotate bytes
    *q = (*q >> 8 | ((*q & 0xff) << 24));

    in[0] = sbox[in[0]]; in[1] = sbox[in[1]];
    in[2] = sbox[in[2]]; in[3] = sbox[in[3]];

    // RCon XOR
    in[0] ^= rcon[rcon_iter];
}


void keyExpansion(unsigned char *inputKey, unsigned char *expandedKey)
{
    for (int idx = 0; idx < 16; idx++)
        expandedKey[idx] = inputKey[idx];

    unsigned int numBytes = 16;
    int rcon_iter = 1;
    unsigned char temp[4];

    // Generate the next 160 bytes
    while (numBytes < 176)
    {
        // Read 4 bytes for the core
        for (int idx = 0; idx < 4; idx++)
        temp[idx] = expandedKey[idx + numBytes - 4];

        // Perform the core once for each 16 byte key
        if (numBytes % 16 == 0)
            gFunction(temp, rcon_iter++);

        // XOR temp with [numBytes - 16], and store in expandedKey
        for (unsigned char a = 0; a < 4; a++)
        {
            expandedKey[numBytes] = expandedKey[numBytes - 16] ^ temp[a];
            numBytes++;
        }
    }
}

void keyAddition(unsigned char *state, unsigned char *key)
{
    for (int idx = 0; idx < 16; idx++)
        state[idx] ^= key[idx];
}


void byteSubstitution(unsigned char *state)
{
    for (int idx = 0; idx < 16; idx++)
        state[idx] = sbox[state[idx]];
}


void shiftRows(unsigned char *state)
{
    std::map<int, int> row = { {12, 1}, {13, 2}, {14, 3} };
    unsigned char tmp[16];
    int idx = 0;    // Loop index
    int s1 = 0, s2 = 4, s3 = 8, s4 = 12;   // state index

    // Loop 4 times. One time per column
    for (idx = 0; idx < 4; idx++)
    {
        // Shifting each row in each column
        tmp[idx + 0] = state[s1];
        tmp[idx + 4] = state[s2];
        tmp[idx + 8] = state[s3];
        tmp[idx + 12] = state[s4];

        // Increment the state index
        s1 = ((s1 >= 12)? row[s1] : (s1 + 5) );
        s2 = ((s2 >= 12)? row[s2] : (s2 + 5) );
        s3 = ((s3 >= 12)? row[s3] : (s3 + 5) );
        s4 = ((s4 >= 12)? row[s4] : (s4 + 5) );
    }

    for (idx = 0; idx < 16; idx++)
        state[idx] = tmp[idx];
}


void  mixColumns(unsigned char *state)
{
    unsigned char tmp[16];
    int idx = 0;

    for (idx = 0; idx < 4; idx++)
    {
        tmp[(idx << 2) + 0] = (unsigned char) (mul2[state[(idx << 2) + 0]] ^ mul_3[state[(idx << 2) + 1]] ^ state[(idx << 2) + 2] ^ state[(idx << 2) + 3]);
        tmp[(idx << 2) + 1] = (unsigned char) (state[(idx << 2) + 0] ^ mul2[state[(idx << 2) + 1]] ^ mul_3[state[(idx << 2) + 2]] ^ state[(idx << 2) + 3]);
        tmp[(idx << 2) + 2] = (unsigned char) (state[(idx << 2) + 0] ^ state[(idx << 2) + 1] ^ mul2[state[(idx << 2) + 2]] ^ mul_3[state[(idx << 2) + 3]]);
        tmp[(idx << 2) + 3] = (unsigned char) (mul_3[state[(idx << 2) + 0]] ^ state[(idx << 2) + 1] ^ state[(idx << 2) + 2] ^ mul2[state[(idx << 2) + 3]]);
    }

    for (idx = 0; idx < 16; idx++)
        state[idx] = tmp[idx];
}

#endif // ! AES_H
