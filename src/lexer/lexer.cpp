#include "lexer.h"

#include <cctype>
#include <cstdlib>
#include <iostream>

Lexer::Lexer(const std::string& source)
    : source(source),
      current(0),
      line(1),
      column(1)
{
}

bool Lexer::isAtEnd() const
{
    return current >= source.length();
}

char Lexer::advance()
{
    char c = source[current++];

    if (c == '\n')
    {
        line++;
        column = 1;
    }
    else
    {
        column++;
    }

    return c;
}

char Lexer::peek() const
{
    if (isAtEnd())
    {
        return '\0';
    }

    return source[current];
}

bool Lexer::isCommentStart() const
{
    if (isAtEnd())
        return false;

    if (peek() != '/')
        return false;

    if (current + 1 >= source.length())
        return false;

    char next = source[current + 1];

    return next == '/' || next == '*';
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

void Lexer::skipComment()
{
    if (!isCommentStart())
        return;

    char next = source[current + 1];

    // Single-line comment
    if (next == '/')
    {
        advance();
        advance();

        while (!isAtEnd() &&
               peek() != '\n')
        {
            advance();
        }

        if (!isAtEnd())
        {
            advance();
        }
    }
    // Multi-line comment
    else if (next == '*')
    {
        advance();
        advance();

        while (!isAtEnd())
        {
            if (peek() == '*' &&
                current + 1 < source.length() &&
                source[current + 1] == '/')
            {
                advance();
                advance();
                break;
            }

            advance();
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

Token Lexer::stringLiteral()
{
    advance();

    std::string value;

    while (!isAtEnd() &&
           peek() != '"')
    {
        value += advance();
    }

    if (isAtEnd())
    {
        std::cerr
            << "Lexer Error\n"
            << "Line "
            << line
            << ", Column "
            << column
            << "\n\n"
            << "Unterminated string literal\n";

        std::exit(1);
    }

    advance();

    return Token(
        TokenType::String,
        value);
}

Token Lexer::characterLiteral()
{
    advance();

    if (isAtEnd())
    {
        std::cerr
            << "Invalid character literal\n";

        std::exit(1);
    }

    char value = advance();

    if (isAtEnd() || peek() != '\'')
    {
        std::cerr
            << "Invalid character literal\n";

        std::exit(1);
    }

    advance();

    return Token(
        TokenType::Character,
        std::string(1, value));
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    while (!isAtEnd())
    {
        while (true)
        {
            skipWhitespace();

            if (isCommentStart())
            {
                skipComment();
                continue;
            }

            break;
        }

        if (isAtEnd())
            break;

        char c = peek();

        if (c == '"')
        {
            tokens.push_back(
                stringLiteral());

            continue;
        }

        if (c == '\'')
        {
            tokens.push_back(
                characterLiteral());

            continue;
        }

        if (std::isalpha(c) || c == '_')
        {
            tokens.push_back(
                identifier());

            continue;
        }

        if (std::isdigit(c))
        {
            tokens.push_back(
                number());

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
        {
            std::cerr
                << "Lexer Error\n"
                << "Line "
                << line
                << ", Column "
                << column
                << "\n\n"
                << "Unexpected character '"
                << c
                << "'\n";

            std::exit(1);
        }
        }
    }

    tokens.emplace_back(
        TokenType::EndOfFile,
        "");

    return tokens;
}