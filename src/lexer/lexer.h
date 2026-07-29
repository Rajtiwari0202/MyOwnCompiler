#pragma once

#include <string>
#include <vector>

#include "token.h"

class Lexer
{
private:
    std::string source;

    size_t current;

    int line;
    int column;

public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();

private:
    bool isAtEnd() const;

    bool isCommentStart() const;

    char advance();

    char peek() const;

    void skipWhitespace();

    void skipComment();

    Token identifier();

    Token number();
};