#include <iostream>
#include <new>

int main()
{
    int firstNumber = 0;
    int secondNumber = 0;
    int thirdNumber = 0;

    std::cout << "Integer Pointers Program\n\n";

    // Store the user's input in three separate variables.
    std::cout << "Enter the first integer: ";
    std::cin >> firstNumber;

    std::cout << "Enter the second integer: ";
    std::cin >> secondNumber;

    std::cout << "Enter the third integer: ";
    std::cin >> thirdNumber;

    // Stop before allocating memory if an input could not be read.
    if (!std::cin)
    {
        std::cout << "\nInvalid input. Please run the program again using integers.\n";
        return 1;
    }

    // Give each pointer its own memory and a copy of the matching value.
    int* firstPointer = new (std::nothrow) int(firstNumber);
    int* secondPointer = new (std::nothrow) int(secondNumber);
    int* thirdPointer = new (std::nothrow) int(thirdNumber);

    // A failed allocation returns nullptr when nothrow is used.
    if (firstPointer == nullptr || secondPointer == nullptr ||
        thirdPointer == nullptr)
    {
        std::cout << "\nMemory could not be allocated.\n";
        delete firstPointer;
        delete secondPointer;
        delete thirdPointer;
        return 1;
    }

    std::cout << "\nValues stored in the variables\n";
    std::cout << "First number: " << firstNumber << '\n';
    std::cout << "Second number: " << secondNumber << '\n';
    std::cout << "Third number: " << thirdNumber << '\n';

    // The * operator reads the integer stored at a pointer's address.
    std::cout << "\nValues stored in dynamic memory\n";
    std::cout << "First pointer value: " << *firstPointer << '\n';
    std::cout << "Second pointer value: " << *secondPointer << '\n';
    std::cout << "Third pointer value: " << *thirdPointer << '\n';

    std::cout << "\nAddresses stored in the pointers\n";
    std::cout << "First pointer address: " << firstPointer << '\n';
    std::cout << "Second pointer address: " << secondPointer << '\n';
    std::cout << "Third pointer address: " << thirdPointer << '\n';

    // Release each allocation once, after its value has been displayed.
    delete firstPointer;
    delete secondPointer;
    delete thirdPointer;

    // These pointers no longer refer to memory owned by the program.
    firstPointer = nullptr;
    secondPointer = nullptr;
    thirdPointer = nullptr;

    std::cout << "\nDynamic memory has been released.\n";

    return 0;
}
