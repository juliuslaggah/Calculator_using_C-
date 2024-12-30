#include "ArithmeticOperations.h"
#include "VariableManager.h"
#include "ConstantManager.h"
#include "BaseConversion.h"
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <regex>

double ArithmeticOperation::applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b != 0) return a / b;
            throw std::runtime_error("Division by zero");
        case '^': return std::pow(a, b);
        default: throw std::runtime_error("Unsupported operator");
    }
}

int ArithmeticOperation::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void ArithmeticOperation::processOperator(std::stack<double>& values, std::stack<char>& operators) {
    double b = values.top(); values.pop();
    double a = values.top(); values.pop();
    char op = operators.top(); operators.pop();
    values.push(applyOperator(a, b, op));
}

double ArithmeticOperation::evaluateExpression(const std::string& expression) {
    VariableManager varManager;
    ConstantManager constManager;
    BaseConversion baseConverter;

    // Replace variables and constants
    std::string parsedExpression = varManager.replaceVariables(expression);
    parsedExpression = constManager.replaceConstants(parsedExpression);

    // Handle hexadecimal numbers
    std::regex hexPattern("0x[0-9A-Fa-f]+");
    std::smatch match;
    while (std::regex_search(parsedExpression, match, hexPattern)) {
        std::string hexStr = match.str();
        double decimalValue = baseConverter.hexToDecimal(hexStr.substr(2));
        parsedExpression.replace(match.position(0), match.length(0), std::to_string(decimalValue));
    }

    // Handle binary numbers
    std::regex binaryPattern("([01]+)b");
    while (std::regex_search(parsedExpression, match, binaryPattern)) {
        std::string binaryStr = match.str(1);
        double decimalValue = baseConverter.binaryToDecimal(binaryStr);
        parsedExpression.replace(match.position(0), match.length(0), std::to_string(decimalValue));
    }

    // Handle trigonometric functions
    std::regex trigPattern("sin\\(([^)]+)\\)|cos\\(([^)]+)\\)");
    while (std::regex_search(parsedExpression, match, trigPattern)) {
        std::string func = match.str(0);
        std::string innerExpr = match.str(1).empty() ? match.str(2) : match.str(1);
        double angle = evaluateExpression(innerExpr);
        double trigResult = (func.find("sin") != std::string::npos) ? 
                            std::sin(angle) : std::cos(angle);
        parsedExpression.replace(match.position(0), match.length(0), std::to_string(trigResult));
    }

    // Evaluate the parsed expression using stacks
    std::stack<double> values;
    std::stack<char> operators;
    std::istringstream tokens(parsedExpression);
    char token;

    while (tokens >> token) {
        if (std::isdigit(token) || token == '.') {
            tokens.putback(token);
            double value;
            tokens >> value;
            values.push(value);
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                processOperator(values, operators);
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                processOperator(values, operators);
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        processOperator(values, operators);
    }

    return values.top();
}
