#ifndef AES_H
#define AES_H

// Headers
#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <sstream>

#ifdef _WIN32
#include <string>   // This is for the getline function to read key for Windows
#endif // ! _WIN32

#include "constants.h"


// Functions Declarations
void gFunction(unsigned char *, unsigned char); // Will be used in key scheduling process
void keyScheduling(unsigned char *, unsigned char *); // Expand key to 176 bytes. 16 bytes per round. 11 rounds
void keyAddition(unsigned char *, unsigned char *); // XOR Round key with state
void byteSubstitution(unsigned char *); // replace bytes with value in sbox
void shiftRows(unsigned char *); // Shift rows
void  mixColumns(unsigned char *); // Matrix multiplication  column with given matrix
char *encryption(unsigned char *, unsigned char *); // Encrypt the message using the key


void gFunction(unsigned char *input, unsigned char rcon_iter)
{
    // Rotate the word
    // The input should be the last word of the key
    unsigned char byteZero = input[0];

    for (int idx = 0; idx < 3; idx++)
        input[idx] = input[idx + 1];
    input[3] = byteZero;

    // Replace using the substitution box
    for (int idx = 0; idx < 4; idx++)
        input[idx] = sbox[input[idx]];

    // XOR
    input[0] ^= rcon[rcon_iter];
}


void keyScheduling(unsigned char *inputKey, unsigned char *expandedKey)
{
    // Copy over the key to the key that will hold all round keys
    for (int idx = 0; idx < BLOCK_SIZE; idx++)
        expandedKey[idx] = inputKey[idx];

    unsigned char temp[WORD];   // This will be used to hold the last word in keys
    unsigned int rconIter = 1;

    unsigned char currentKey[BLOCK_SIZE];  // This is the current round's key

    // Copy over the first 16 bytes of the expandedKey to the current round key
    for (int idx = 0; idx < BLOCK_SIZE; idx++)
        currentKey[idx] = expandedKey[idx];

    const int totalRounds = 10;
    for (int round = 1; round <= totalRounds; round++)  // Execute for each round key
    {
        // This will get the last word of the key of the current round
        for (int idx = 0; idx < WORD; idx++)
            temp[idx] = currentKey[idx + BLOCK_SIZE - 4];

        // This g function will only be run once per round
        gFunction(temp, rconIter++);

        // XOR first word of current round key with the last word of the current round key
        for (int idx = 0; idx < WORD; idx++)
            currentKey[idx] ^= temp[idx];

        // XOR with the previous word
        for (int idx = 4; idx < BLOCK_SIZE; idx++)
            currentKey[idx] ^= currentKey[idx - 4];

        // Appending the currentKey to the expanded key
        for (int idx = 0; idx < BLOCK_SIZE; idx++)
            expandedKey[idx + (round * BLOCK_SIZE)] = currentKey[idx];
    }
}


void keyAddition(unsigned char *state, unsigned char *roundKey)
{
    // XOR the state with the round key
    for (int idx = 0; idx < BLOCK_SIZE; idx++)
        state[idx] ^= roundKey[idx];
}


void byteSubstitution(unsigned char *state)
{
    // Substituting each box with what equivalent in the sbox
    for (int idx = 0; idx < BLOCK_SIZE; idx++)
        state[idx] = sbox[state[idx]];
}


void shiftRows(unsigned char *state)
{
    unsigned char tmp[BLOCK_SIZE];

    std::map<int, int> row = { {12, 1}, {13, 2}, {14, 3} };
    int s1 = 0, s2 = 4, s3 = 8, s4 = 12;   // state index

    // Loop 4 times. One time per column
    for (int idx = 0; idx < 4; idx++)
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

    // Copying all in temp to state
    for (int idx = 0; idx < BLOCK_SIZE; idx++)
        state[idx] = tmp[idx];
}


void  mixColumns(unsigned char *state)
{
    unsigned char tmp[BLOCK_SIZE];
    int idx = 0;

    for (idx = 0; idx < 4; idx++)
    {
        tmp[(idx << 2) + 0] =
            (unsigned char) (mul2[state[(idx << 2) + 0]] ^ mul_3[state[(idx << 2) + 1]]
            ^ state[(idx << 2) + 2] ^ state[(idx << 2) + 3]);
        tmp[(idx << 2) + 1] =
            (unsigned char) (state[(idx << 2) + 0] ^ mul2[state[(idx << 2) + 1]]
            ^ mul_3[state[(idx << 2) + 2]] ^ state[(idx << 2) + 3]);
        tmp[(idx << 2) + 2] =
            (unsigned char) (state[(idx << 2) + 0] ^ state[(idx << 2) + 1]
            ^ mul2[state[(idx << 2) + 2]] ^ mul_3[state[(idx << 2) + 3]]);
        tmp[(idx << 2) + 3] =
            (unsigned char) (mul_3[state[(idx << 2) + 0]] ^ state[(idx << 2) + 1]
            ^ state[(idx << 2) + 2] ^ mul2[state[(idx << 2) + 3]]);
    }

    for (idx = 0; idx < BLOCK_SIZE; idx++)
        state[idx] = tmp[idx];
}


char *encryption(unsigned char *message, unsigned char *key)
{
    unsigned char state[BLOCK_SIZE];

    // Copying message to state
    for (int idx = 0; idx < BLOCK_SIZE; idx++)
        state[idx] = message[idx];

    // First key addition
    keyAddition(state, key);

    // For encryption, the first 9 rounds are idenical
    const unsigned int numRounds = 9;

    //  For rounds 1 - 9
    for (int round = 1; round <= numRounds; round++)
    {
        byteSubstitution(state);
        shiftRows(state);
        mixColumns(state);
        keyAddition(state, key + (BLOCK_SIZE * round));   // from the roundKeys skip to index (BLOCK_SIZE * round)
    }

    // Round 10
    byteSubstitution(state);
    shiftRows(state);
    keyAddition(state, key + 160);    // The word starting at roundKeys[160] is the last round key

    // Copying over the state to the encryptedMessage.
    char * encryptedMessage  = (char *) malloc(16);     // Contains the encryptedMessage for this particular block
    memcpy(encryptedMessage, state, 16);

    return encryptedMessage;    // Returning the encryptedMessage
}


#endif // ! AES_H
