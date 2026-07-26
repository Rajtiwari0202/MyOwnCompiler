#pragma once

#include <string>

enum class TokenType
{
    // literals
    Identifier,
    Number,

    // operators
    Plus,
    Minus,
    Star,
    Slash,
    Equal,

    // punctuation
    Semicolon,
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,

    // keywords
    Let,
    If,
    While,
    Print,

    EndOfFile,
    Unknown
};

struct Token
{
    TokenType type;
    std::string lexeme;

    Token(TokenType type, std::string lexeme)
        : type(type),
          lexeme(std::move(lexeme))
    {
    }
};