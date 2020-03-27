#include "aes.h"
#include "functions.h"


int main(int argc, char const *argv[])
{
    std::string inputFile;
    std::ifstream infile;

    // If there is an argument besides the executable
    if (argc == 2)
    {
        // Get the filename from the terminal/cmd line
        inputFile = argv[1];

        // Open the filename that user gave
        infile.open(inputFile, std::ios_base::binary);

        // If there is no file or unable to find path to file
        if (!infile)
        {
            std::cerr
                << "Unable to find file or file doesn\'t exist. "
                << "Please make sure both file\'s path & filename are correct."
                << std::endl;

            // Error message that should only be displayed when using Windows
            #ifdef _WIN32
            std::cout
                << "Common error: "
                << "Path could be C:\\Path\\....\\filename.txt.txt "
                << "instead of C:\\Path\\....\\filename.txt" << std::endl;
            #endif // ! _WIN32

            return -1;   // End program unsuccessfully
        }
    }
    else
    {
        std::cerr
            << "Take in 2 arguments. " << std::endl
            << "eg. AES128encrypt Argument2" << std::endl;
        return -1;  // End program unsuccessfully
    }


    // *** If there are no errors execute the code below ***


    // Create an encrypted file name. File named as filename.enc
    std::string encryptedFilename =
        inputFile.substr(0, inputFile.find_last_of(".")) + ".enc";

    // Prompt the user for their key
    std::cout << "Please enter your key:  ";
    std::string inputKey;
    std::getline(std::cin, inputKey);
    inputKey = removeSpacing(inputKey);     // Remove whitespace if any

    unsigned char *key = (unsigned char*)inputKey.c_str();

    unsigned char allRoundKeys[176];
    keyScheduling(key, allRoundKeys);   // Generating all 10 round keys

    unsigned char message[BLOCK_SIZE];
    int bytesRead = 0;  // This will be used to track how bytes is read

    // while there is 16 bytes of the message
    while(!infile.eof())
    {
        infile.read((char *)message, BLOCK_SIZE);
        bytesRead = infile.gcount();

        if (bytesRead < BLOCK_SIZE)
        {
            int padSize = (BLOCK_SIZE - bytesRead) % BLOCK_SIZE;

            if (padSize == 0)
                padSize = BLOCK_SIZE;

            // unsigned char value = (unsigned char)padSize;

            int start = bytesRead;
            for (int idx = 0; idx < BLOCK_SIZE; idx++)
                message[start++] = 0;
        }

        encryption(message, allRoundKeys, encryptedFilename);
    }

    // Properly close the file
    infile.close();

    return 0;   // Successful
}
