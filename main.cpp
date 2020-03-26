#include "aes.h"


int main(int argc, char const *argv[])
{
    std::string fullPath;
    std::ifstream infile;

    // If there is an argument besides the executable
    if (argc == 2)
    {
        // Get the filename from the terminal/cmd line
        fullPath = argv[1];

        // Open the filename that user gave
        infile.open(fullPath);

        // If there is no file or unable to find path to file
        if (!infile)
        {
            std::cerr
                << "Unable to find file or file doesn\'t exist. "
                << "Please make sure both file\'s path & filename are correct."
                << std::endl;

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


    // Prompt the user for their key
    std::cout << "Please enter your key:  ";
    std::string inputKey;
    std::getline(std::cin, inputKey);

    // Run the encryption algorithm
    unsigned char *key = (unsigned char*)inputKey.c_str();

    #define BUFFER_SIZE 16
    unsigned char buffer[BUFFER_SIZE];
    unsigned char expandedKey[176];
    keyExpansion(key, expandedKey);

    // Once encrypted, output encrypted file as filename.enc
    std::string encryptedFilename = fullPath.substr(0, fullPath.find_last_of(".") + 1) + "enc";

    // Create a file named filename.enc in directory as plaintext
    // std::ofstream outfile(encryptedFilename);
    // outfile << file;

    // Properly close the files
    infile.close();
    // outfile.close();

    return 0;   // Successful
}
