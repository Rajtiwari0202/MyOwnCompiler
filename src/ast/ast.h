#pragma once

#include <memory>
#include <string>

class ASTNode
{
public:
    virtual ~ASTNode() = default;
};

class StringLiteralNode : public ASTNode
{
public:
    std::string value;

    explicit StringLiteralNode(
        const std::string& value)
        : value(value)
    {
    }
};

class PrintStatementNode : public ASTNode
{
public:
    std::unique_ptr<StringLiteralNode> expression;

    explicit PrintStatementNode(
        std::unique_ptr<StringLiteralNode> expression)
        : expression(std::move(expression))
    {
    }
};