#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>

class ExpressionParser {
public:
    static double parseExpression(const std::string& expression);
};

#endif
