#include "lexer.h"

#include <cctype>

Lexer::Lexer(const std::string &source)
    : source(source),
      current(0)
{
}

bool Lexer::isAtEnd() const
{
    return current >= source.length();
}

char Lexer::advance()
{
    return source[current++];
}

char Lexer::peek() const
{
    if (isAtEnd())
    {
        return '\0';
    }

    return source[current];
}

void Lexer::skipWhitespace()
{
    while (!isAtEnd())
    {
        char c = peek();

        if (c == ' ' ||
            c == '\t' ||
            c == '\n' ||
            c == '\r')
        {
            advance();
        }
        else
        {
            break;
        }
    }
}

Token Lexer::identifier()
{
    std::string value;

    while (!isAtEnd() &&
           (std::isalnum(peek()) || peek() == '_'))
    {
        value += advance();
    }

    if (value == "let")
        return Token(TokenType::Let, value);

    if (value == "if")
        return Token(TokenType::If, value);

    if (value == "while")
        return Token(TokenType::While, value);

    if (value == "print")
        return Token(TokenType::Print, value);

    return Token(TokenType::Identifier, value);
}

Token Lexer::number()
{
    std::string value;

    while (!isAtEnd() &&
           std::isdigit(peek()))
    {
        value += advance();
    }

    return Token(TokenType::Number, value);
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    while (!isAtEnd())
    {
        skipWhitespace();

        if (isAtEnd())
            break;

        char c = peek();

        if (std::isalpha(c) || c == '_')
        {
            tokens.push_back(identifier());
            continue;
        }

        if (std::isdigit(c))
        {
            tokens.push_back(number());
            continue;
        }

        switch (advance())
        {
        case '+':
            tokens.emplace_back(TokenType::Plus, "+");
            break;

        case '-':
            tokens.emplace_back(TokenType::Minus, "-");
            break;

        case '*':
            tokens.emplace_back(TokenType::Star, "*");
            break;

        case '/':
            tokens.emplace_back(TokenType::Slash, "/");
            break;

        case '=':
            tokens.emplace_back(TokenType::Equal, "=");
            break;

        case ';':
            tokens.emplace_back(TokenType::Semicolon, ";");
            break;

        case '(':
            tokens.emplace_back(TokenType::LeftParen, "(");
            break;

        case ')':
            tokens.emplace_back(TokenType::RightParen, ")");
            break;

        case '{':
            tokens.emplace_back(TokenType::LeftBrace, "{");
            break;

        case '}':
            tokens.emplace_back(TokenType::RightBrace, "}");
            break;

        default:
            tokens.emplace_back(
                TokenType::Unknown,
                std::string(1, c));
            break;
        }
    }

    tokens.emplace_back(
        TokenType::EndOfFile,
        "");

    return tokens;
}