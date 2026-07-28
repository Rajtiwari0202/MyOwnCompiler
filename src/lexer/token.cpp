#include "token.h"

std::string tokenTypeToString(TokenType type)
{
    switch (type)
    {
        case TokenType::Identifier:
            return "IDENTIFIER";

        case TokenType::Number:
            return "NUMBER";

        case TokenType::Plus:
            return "PLUS";

        case TokenType::Minus:
            return "MINUS";

        case TokenType::Star:
            return "STAR";

        case TokenType::Slash:
            return "SLASH";

        case TokenType::Equal:
            return "EQUAL";

        case TokenType::Semicolon:
            return "SEMICOLON";

        case TokenType::LeftParen:
            return "LEFT_PAREN";

        case TokenType::RightParen:
            return "RIGHT_PAREN";

        case TokenType::LeftBrace:
            return "LEFT_BRACE";

        case TokenType::RightBrace:
            return "RIGHT_BRACE";

        case TokenType::Let:
            return "LET";

        case TokenType::If:
            return "IF";

        case TokenType::While:
            return "WHILE";

        case TokenType::Print:
            return "PRINT";

        case TokenType::EndOfFile:
            return "EOF";

        default:
            return "UNKNOWN";
    }
}