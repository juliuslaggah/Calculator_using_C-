#include "ExpressionParser.h"
#include "VariableManager.h"
#include "ArithmeticOperations.h"
#include "ConstantManager.h"
#include "BaseConversion.h"
#include <regex>
#include <stdexcept>


double ExpressionParser::parseExpression(const std::string& expression) {
    if (expression.empty()) {
        throw std::runtime_error("Empty expression encountered");
    }

    VariableManager varManager;
    ArithmeticOperation arithmeticOperation;
    ConstantManager constantManager;
    BaseConversion baseConverter;

    std::string parsedExpression = expression;

    // Handle variable assignment
    
    size_t equalPos = parsedExpression.find('=');
    if (equalPos != std::string::npos) {
        std::string varName = parsedExpression.substr(0, equalPos);
        std::string valueExpr = parsedExpression.substr(equalPos + 1);
        if (varName.empty() || valueExpr.empty()) {
            throw std::runtime_error("Invalid variable assignment format");
        }
        double value = arithmeticOperation.evaluateExpression(varManager.replaceVariables(valueExpr));
        varManager.setVariable(varName, value);
        return value;
    }

    // Replace variables with their values
    parsedExpression = varManager.replaceVariables(parsedExpression);

    // Process trigonometric functions (e.g., sin, cos)
    std::regex trigPattern("sin\\(([^)]+)\\)|cos\\(([^)]+)\\)");
    std::smatch trigMatch;
    while (std::regex_search(parsedExpression, trigMatch, trigPattern)) {
        std::string function = trigMatch.str(0);
        std::string innerExpr = trigMatch.str(1).empty() ? trigMatch.str(2) : trigMatch.str(1);
        double angle = arithmeticOperation.evaluateExpression(innerExpr);

        double trigResult = (function.find("sin") != std::string::npos)
                            ? constantManager.calculateSin(angle)
                            : constantManager.calculateCos(angle);

        parsedExpression.replace(trigMatch.position(0), trigMatch.length(0), std::to_string(trigResult));
    }

    // Replace hexadecimal values
    std::regex hexPattern("0x([0-9A-Fa-f]+)");
    std::smatch match;
    while (std::regex_search(parsedExpression, match, hexPattern)) {
        std::string hexStr = match.str(1);
        std::string decimalStr = std::to_string(baseConverter.hexToDecimal(hexStr));
        parsedExpression.replace(match.position(0), match.length(0), decimalStr);
    }

    // Replace binary values
    std::regex binaryPattern("([01]+)b");
    while (std::regex_search(parsedExpression, match, binaryPattern)) {
        std::string binaryStr = match.str(1);
        std::string decimalStr = std::to_string(baseConverter.binaryToDecimal(binaryStr));
        parsedExpression.replace(match.position(0), match.length(0), decimalStr);
    }

    // Evaluate the final expression
    return arithmeticOperation.evaluateExpression(parsedExpression);
}
