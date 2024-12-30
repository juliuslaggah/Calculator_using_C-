#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

class Calculator {
public:
    std::vector<std::string> readExpressionsFromFile(const std::string& fileName);
    void writeResultsToFile(const std::string& fileName, const std::vector<std::string>& results); // Change to std::string
    std::vector<std::string> processExpressions(const std::vector<std::string>& expressions);
};

#endif // CALCULATOR_H
