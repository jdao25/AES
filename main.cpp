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
        inputFile.substr(inputFile.find_last_of(".") + 1) + ".enc";

    std::cout << "encryptedFilename:  " << encryptedFilename << std::endl;

    std::ofstream outfile(encryptedFilename, std::ios_base::app);

    // Prompt the user for their key
    std::cout << "Please enter your key:  ";
    std::string inputKey;
    std::getline(std::cin, inputKey);
    inputKey = removeSpacing(inputKey);     // Remove whitespace if any

    // Run the encryption algorithm
    unsigned char *key = (unsigned char*)inputKey.c_str();

    unsigned char expandedKey[176];
    keyScheduling(key, expandedKey);    // Key is now expanded to 176 bytes

    unsigned char state[BUFFER_SIZE];

    while(infile.read((char *)state, BUFFER_SIZE))
    {
        int originalLen = std::strlen((const char *)state);
        int lenOfPaddedMessage = originalLen;

        if (lenOfPaddedMessage % 16 != 0)
            lenOfPaddedMessage = (lenOfPaddedMessage / 16 + 1) * 16;

        unsigned char *paddedMessage = new unsigned char[lenOfPaddedMessage];

        for (int idx = 0; idx < lenOfPaddedMessage; idx++)
        {
            if (idx > originalLen) paddedMessage[idx] = 0;
            else paddedMessage[idx] = state[idx];
        }

        // Function will take in the file to be encrypted along w/ the expanded key
        encryption((unsigned char *)paddedMessage, expandedKey);

        outfile << state;
    }

    // Properly close the files
    infile.close();
    outfile.close();

    return 0;   // Successful
}
