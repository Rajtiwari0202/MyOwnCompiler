#include "parser.h"

Parser::Parser(
    const std::vector<Token>& tokens)
    : tokens(tokens),
      current(0)
{
}

bool Parser::isAtEnd() const
{
    return peek().type ==
           TokenType::EndOfFile;
}

const Token& Parser::peek() const
{
    return tokens[current];
}

const Token& Parser::advance()
{
    if (!isAtEnd())
    {
        current++;
    }

    return tokens[current - 1];
}

std::unique_ptr<PrintStatementNode>
Parser::parsePrintStatement()
{
    // print

    advance();

    // (

    advance();

    // string

    std::string value =
        advance().lexeme;

    // )

    advance();

    // ;

    advance();

    return std::make_unique<
        PrintStatementNode>(
        std::make_unique<
            StringLiteralNode>(
            value));
}