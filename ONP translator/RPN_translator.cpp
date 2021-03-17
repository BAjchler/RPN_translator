#include <iostream>
#include <string>
#include "text_handler.h"
#include "translator.h"
int main()
{
    std::string input, dummy;
    std::cout << "Input algebra equation that needs to be translated\n";
    // Take an expression from user
    std::getline(std::cin, input);
    clean_text(input);
    translate(input);
    // Ask to enter anything so the program doesn't close immediately after outputing the translated expression.
    std::cout << '\n' << input << '\n' << "Input any character to exit";
    std::cin >> dummy;
}