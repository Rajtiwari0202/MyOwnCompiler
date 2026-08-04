#include "parser.h"

#include <cstdlib>

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

std::unique_ptr<ExpressionNode>
Parser::parseExpression()
{
    Token token = advance();

    if (token.type ==
        TokenType::String)
    {
        return std::make_unique<
            StringLiteralNode>(
            token.lexeme);
    }

    if (token.type ==
        TokenType::Number)
    {
        return std::make_unique<
            NumberLiteralNode>(
            std::stoi(token.lexeme));
    }

    std::exit(1);
}

std::unique_ptr<PrintStatementNode>
Parser::parsePrintStatement()
{
    advance(); // print

    advance(); // (

    auto expression =
        parseExpression();

    advance(); // )

    advance(); // ;

    return std::make_unique<
        PrintStatementNode>(
        std::move(expression));
}

std::unique_ptr<ProgramNode>
Parser::parse()
{
    auto program =
        std::make_unique<
            ProgramNode>();

    while (!isAtEnd())
    {
        program->statements.push_back(
            parsePrintStatement());
    }

    return program;
}