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
    advance(); // print

    advance(); // (

    std::string value =
        advance().lexeme;

    advance(); // )

    advance(); // ;

    return std::make_unique<
        PrintStatementNode>(
        std::make_unique<
            StringLiteralNode>(
            value));
}

std::unique_ptr<ProgramNode>
Parser::parse()
{
    auto program =
        std::make_unique<ProgramNode>();

    while (!isAtEnd())
    {
        program->statements.push_back(
            parsePrintStatement());
    }

    return program;
}