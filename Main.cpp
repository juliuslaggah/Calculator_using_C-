#include <iostream>
#include <fstream>
#include <sstream>
#include "Calculator.h"
#include "ExpressionParser.h"
#include <vector>
#include <string>
#include <iomanip>

int main() {
    Calculator calculator;
    std::cout << ".......... A SIMPLE CALCULATOR .........." << std::endl;

    while (true) {
        std::cout << "\nEnter an expression to calculate, or type a file name to process:" << std::endl;
        std::cout << "(Type 'exit' to quit, 'help' for instructions)" << std::endl;
        std::cout << ">>> ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        } else if (input == "exit") {
            break;
        } else if (input == "help") {
            std::cout << "Instructions:" << std::endl;
            std::cout << "1. Enter a mathematical expression to calculate." << std::endl;
            std::cout << "2. Enter a file name to process batch expressions." << std::endl;
            std::cout << "3. Type 'exit' to quit the calculator." << std::endl;
            continue;
        }

        // Check if input is a valid file
        std::ifstream testFile(input);
        if (testFile.good()) {
            testFile.close();
            try {
                std::vector<std::string> expressions = calculator.readExpressionsFromFile(input);
                if (!expressions.empty()) { // Only process if expressions were successfully read
                    std::vector<std::string> results = calculator.processExpressions(expressions);
                    for (const std::string& result : results) {
                        std::cout << result << std::endl;
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "File Error: " << e.what() << std::endl;
            }
            continue; // Prompt the user for input again after processing the file
        } else {
            std::cerr << "Error: The file '" << input << "' could not be opened. Please check the file name and try again." << std::endl;
            continue;
        }

        // Treat input as an expression if it is not a file
        try {
            std::ostringstream resultStream;
            resultStream << "Original Expression: " << input;
            double result = ExpressionParser::parseExpression(input);
            if (result == static_cast<int>(result)) {
                resultStream << "\nRESULT: " << input << " = " << static_cast<int>(result);
            } else {
                resultStream << "\nRESULT: " << input << " = " << std::fixed << std::setprecision(2) << result;
            }
            std::cout << resultStream.str() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Original Expression: " << input << " - Error: " << e.what() << std::endl;
        }
    }

    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
