#include <iostream>

#include "lexer/lexer.h"

void runTest(const std::string& source)
{
    std::cout << "\n========================\n";
    std::cout << source << "\n";
    std::cout << "========================\n";

    Lexer lexer(source);

    auto tokens = lexer.tokenize();

    for (const auto& token : tokens)
    {
        std::cout
            << tokenTypeToString(token.type)
            << "\t\t"
            << token.lexeme
            << '\n';
    }
}

int main()
{
    runTest("let x = 10 + 5 * 2;");

    runTest("(10 + 20)");

    runTest("{ }");

    runTest("if while print let");

    runTest("count studentName x1 _temp");

    return 0;
}