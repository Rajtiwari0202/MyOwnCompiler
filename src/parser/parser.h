#pragma once

#include <memory>
#include <vector>

#include "../ast/ast.h"
#include "../lexer/token.h"

class Parser
{
private:
    std::vector<Token> tokens;

    size_t current;

public:
    explicit Parser(
        const std::vector<Token>& tokens);

    std::unique_ptr<ProgramNode>
    parse();

private:
    std::unique_ptr<PrintStatementNode>
    parsePrintStatement();

    bool isAtEnd() const;

    const Token& peek() const;

    const Token& advance();
};