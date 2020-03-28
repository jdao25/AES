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
    std::cout
        << "Please enter your hex key (with spaces):  " << std::endl
        << "Formating: 85 0b ca d3 af 16 d5 08 31 2d 76 65 a3 db ee 94\n" << std::endl
        << "Key -->  ";

    std::string inputKey;
    std::getline(std::cin, inputKey);

    // Write to the output file
    std::ofstream outfile;
    outfile.open(encryptedFilename, std::ios::out | std::ios::ate | std::ios::app | std::ios::binary);

    unsigned char key[BLOCK_SIZE];
    convertCharToHex(inputKey, key);

    unsigned char allRoundKeys[176];    // This will hold all round keys
    keyScheduling(key, allRoundKeys);   // Generate round key of round 1 - 10

    unsigned char message[BLOCK_SIZE];
    char *encryptedMessage;     // This will contain the encrypted message
    int bytesRead = 0;  // This will be used to track how bytes is read

    // while there is 16 bytes of the message
    while(!infile.eof())
    {
        infile.read((char *)message, BLOCK_SIZE);
        bytesRead = infile.gcount();    // Grabbing the num of bytes of message

        if (bytesRead < BLOCK_SIZE)
        {
            unsigned char *paddedMessage = PKCS5Padding(message, bytesRead);
            encryptedMessage = encryption(paddedMessage, allRoundKeys);
        }
        else
            encryptedMessage = encryption(message, allRoundKeys);

       outfile.write(encryptedMessage, BLOCK_SIZE);
    }

    // Properly close the file
    infile.close();
    outfile.close();

    return 0;   // Successful
}
