#ifndef ARITHMETICOPERATIONS_H
#define ARITHMETICOPERATIONS_H

#include <string>
#include <stack>

class ArithmeticOperation {
public:
    double evaluateExpression(const std::string& expression);

private:
    double applyOperator(double a, double b, char op);
    int precedence(char op);
    void processOperator(std::stack<double>& values, std::stack<char>& operators);
};

#endif // ARITHMETICOPERATIONS_H
