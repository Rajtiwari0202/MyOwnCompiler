#include <iostream>

#include "lexer/lexer.h"

int main()
{
    std::string source =
        "let x = 10;";

    Lexer lexer(source);

    auto tokens = lexer.tokenize();

    for (const auto& token : tokens)
    {
        std::cout
            << static_cast<int>(token.type)
            << " : "
            << token.lexeme
            << '\n';
    }

    return 0;
}