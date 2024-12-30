#include "Calculator.h"
#include "ExpressionParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

std::vector<std::string> Calculator::readExpressionsFromFile(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        std::cerr << "Error: Could not open file " << fileName << ". Please check the file name and try again." << std::endl;
        return {}; // Return an empty vector to signify failure
    }

    std::cout << "File opened successfully: " << fileName << std::endl;

    std::vector<std::string> expressions;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            expressions.push_back(line);
        }
    }

    inputFile.close();
    return expressions;
}

void Calculator::writeResultsToFile(const std::string& fileName, const std::vector<std::string>& results) {
    std::ofstream outputFile(fileName);
    if (!outputFile) {
        throw std::runtime_error("Error: Could not open file " + fileName);
    }

    for (const std::string& result : results) {
        outputFile << result << std::endl;
    }

    outputFile.close();
}

std::vector<std::string> Calculator::processExpressions(const std::vector<std::string>& expressions) {
    std::vector<std::string> results;
    ExpressionParser parser;

    for (const std::string& expression : expressions) {
        std::string trimmedExpression = expression;
        trimmedExpression.erase(
            std::remove_if(trimmedExpression.begin(), trimmedExpression.end(), ::isspace),
            trimmedExpression.end()
        );

        if (trimmedExpression.empty() || 
            std::all_of(trimmedExpression.begin(), trimmedExpression.end(), [](char c) { return c == '-' || c == '.'; })) {
            continue;
        }

        std::ostringstream resultStream;
        resultStream << "Original Expression: " << expression;

        try {
            if (expression.find('=') != std::string::npos) {
                parser.parseExpression(expression);
            } else {
                double result = parser.parseExpression(expression);
                if (result == static_cast<int>(result)) {
                    resultStream << "\nRESULT: " << expression << " = " << static_cast<int>(result);
                } else {
                    resultStream << "\nRESULT: " << expression << " = " << std::fixed << std::setprecision(2) << result;
                }
            }
        } catch (const std::runtime_error& e) {
            resultStream << "\nError processing expression \"" << expression << "\": " << e.what();
        } catch (const std::exception& e) {
            resultStream << "\nError processing expression \"" << expression << "\": " << e.what();
        }

        results.push_back(resultStream.str());
    }

    return results;
}
