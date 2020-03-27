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



    // Write to the output file
    std::ofstream outfile;

    // Create an encrypted file name. File named as filename.enc
    std::string encryptedFilename =
        inputFile.substr(0, inputFile.find_last_of(".")) + ".enc";

    outfile.open(encryptedFilename, std::ios::app | std::ios::binary);

    // Prompt the user for their key
    std::cout << "Please enter your key:  ";
    std::string inputKey;
    std::getline(std::cin, inputKey);
    inputKey = removeSpacing(inputKey);     // Remove whitespace if any

    unsigned char *key = (unsigned char*)inputKey.c_str();

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
            encryptedMessage = encryption(paddedMessage, key);
        }
        else
            encryptedMessage = encryption(message, key);

       outfile.write(encryptedMessage, BLOCK_SIZE);
    }

    // Properly close the file
    infile.close();
    outfile.close();

    return 0;   // Successful
}
