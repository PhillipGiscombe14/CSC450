#include <iostream>
#include <string>

int main()
{
    std::string firstString;
    std::string secondString;
    std::string combinedString;

    std::cout << "Enter two strings each round. Try different lengths.\n\n";

    // Repeat the string input and output three times.
    for (int count = 1; count <= 3; count++)
    {
        std::cout << "Round " << count << '\n';

        std::cout << "Enter the first string: ";
        std::getline(std::cin, firstString);

        std::cout << "Enter the second string: ";
        std::getline(std::cin, secondString);

        // Join the two strings together.
        combinedString = firstString + secondString;

        std::cout << "Combined string: " << combinedString << "\n\n";
    }

    return 0;
}
