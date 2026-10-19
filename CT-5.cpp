#include <fstream>
#include <iostream>
#include <string>


// Return a new string with its characters in reverse order.

std::string reverseCharacters(const std::string& inputString)
{
    std::string reversed;

    for (std::size_t i = inputString.length(); i > 0; --i)
    {
        reversed += inputString[i - 1];
    }
    return reversed;
}

int main()
{
    std::string userInput;
    const std::string originalFilename = "CSC450_CT5_mod5.txt";
    const std::string reversedFilename = "CSC450_CT5_mod5 - Reverse.txt";
    const std::size_t maximumInputLength = 1000;

    // Check for the provided file before append mode could create a new one.
    std::ifstream originalFile(originalFilename);

    if (!originalFile)
    {
        std::cerr << "Unable to open " << originalFilename
                  << ". Run from the folder containing this file.\n";
        return 1;
    }

    originalFile.close();

    // Read a complete line, including spaces.
    std::cout << "Enter your input (up to 1000 characters): ";

    if (!std::getline(std::cin, userInput))
    {
        std::cerr << "Unable to read your input.\n";
        return 1;
    }

    if (userInput.length() > maximumInputLength)
    {
        std::cerr << "Input is too long. No changes were made.\n";
        return 1;
    }

    std::cout << "You entered: " << userInput << std::endl;

    // Append to the ORIGINAL file without deleting its existing contents.
    std::ofstream inputFile(originalFilename, std::ios::app);

    if (!inputFile)
    {
        std::cerr << "Unable to open the original file for writing.\n";
        return 1;
    }

    // Finish writing before reopening the file for reading.
    inputFile << userInput << std::endl;
    inputFile.close();

    if (!inputFile)
    {
        std::cerr << "Unable to finish saving your input.\n";
        return 1;
    }

    // Binary mode preserves every byte, including Windows line endings.
    std::ifstream readFile(originalFilename, std::ios::binary);

    if (!readFile)
    {
        std::cerr << "Input was appended, but the file could not be reopened.\n";
        return 1;
    }

    std::string fileContents;
    char currentCharacter;

    while (readFile.get(currentCharacter))
    {
        fileContents += currentCharacter;
    }

    if (!readFile.eof())
    {
        std::cerr << "An error occurred while reading the file.\n";
        return 1;
    }

    readFile.close();

    // Reverse all of the file contents, not just the latest input.
    std::string reversedContents = reverseCharacters(fileContents);

    // Replace the previous result with the exact reversed bytes.
    std::ofstream resultFile(reversedFilename, std::ios::binary);

    if (!resultFile)
    {
        std::cerr << "Unable to open the reversed file for writing.\n";
        return 1;
    }

    resultFile << reversedContents;
    resultFile.close();

    if (!resultFile)
    {
        std::cerr << "Unable to finish saving the reversed file.\n";
        return 1;
    }

    std::cout << "Your input was appended to " << originalFilename << '\n';
    std::cout << "The entire file was reversed and saved to "
              << reversedFilename << '\n';

    return 0;
}
