#include <fstream>
#include <iostream>
#include <sstream>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ast/ast.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr
            << "Usage: MyOwnCompiler <file.moc>\n";

        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file)
    {
        std::cerr
            << "Cannot open file\n";

        return 1;
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    Lexer lexer(buffer.str());

    auto tokens =
        lexer.tokenize();

    Parser parser(tokens);

    auto program =
        parser.parse();

    std::cout
        << "Program Parsed Successfully\n";

    std::cout
        << "Statement Count: "
        << program->statements.size()
        << "\n\n";

    for (size_t i = 0;
         i < program->statements.size();
         i++)
    {
        auto* printStmt =
            dynamic_cast<
                PrintStatementNode*>(
                    program->statements[i].get());

        if (printStmt)
        {
            std::cout
                << "Print Statement "
                << i + 1
                << ": "
                << printStmt
                       ->expression
                       ->value
                << '\n';
        }
    }

    return 0;
}