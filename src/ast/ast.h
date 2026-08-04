#pragma once

#include <memory>
#include <string>
#include <vector>

class ASTNode
{
public:
    virtual ~ASTNode() = default;
};

class ExpressionNode : public ASTNode
{
public:
    virtual ~ExpressionNode() = default;
};

class StatementNode : public ASTNode
{
public:
    virtual ~StatementNode() = default;
};

class StringLiteralNode : public ExpressionNode
{
public:
    std::string value;

    explicit StringLiteralNode(
        const std::string& value)
        : value(value)
    {
    }
};

class NumberLiteralNode : public ExpressionNode
{
public:
    int value;

    explicit NumberLiteralNode(int value)
        : value(value)
    {
    }
};

class PrintStatementNode : public StatementNode
{
public:
    std::unique_ptr<ExpressionNode> expression;

    explicit PrintStatementNode(
        std::unique_ptr<ExpressionNode> expression)
        : expression(std::move(expression))
    {
    }
};

class ProgramNode : public ASTNode
{
public:
    std::vector<
        std::unique_ptr<StatementNode>
    > statements;
};