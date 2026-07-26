#include <iostream>
#include "lexer/token.h"

int main()
{
    Token token(
        TokenType::Identifier,
        "age"
    );

    std::cout << token.lexeme << "\n";

    return 0;
}