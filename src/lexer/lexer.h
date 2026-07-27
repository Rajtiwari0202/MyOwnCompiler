#pragma once

#include <string>
#include <vector>

#include "token.h"

class Lexer
{
private:
    std::string source;
    size_t current;

public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();

private:
    bool isAtEnd() const;

    char advance();

    char peek() const;

    void skipWhitespace();

    Token identifier();

    Token number();
};