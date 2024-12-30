#include "ConstantManager.h"
#include <regex>
#include <sstream>
#include <cmath>

ConstantManager::ConstantManager() {
    // Add predefined constants here
    constants["pi"] = 3.14;
    constants["e"] = 2.71;
}

double ConstantManager::getConstantValue(const std::string& name) const {
    auto it = constants.find(name);
    if (it != constants.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined constant: " + name);
}

std::string ConstantManager::replaceConstants(const std::string& expression) const {
    std::regex constantPattern(R"(\b[a-zA-Z_][a-zA-Z0-9_]*\b)");
    std::smatch match;
    std::string result = expression;

    auto searchStart = result.cbegin();
    while (std::regex_search(searchStart, result.cend(), match, constantPattern)) {
        std::string name = match.str();
        auto it = constants.find(name);
        if (it != constants.end()) {
            // Replace the constant with its value
            std::ostringstream valueStream;
            valueStream << it->second;
            result.replace(match.position(), match.length(), valueStream.str());
        }
        searchStart = result.cbegin() + match.position() + match.length();
    }

    return result;
}

double ConstantManager::calculateSin(double radians) const {
    return std::sin(radians);
}

double ConstantManager::calculateCos(double radians) const {
    return std::cos(radians);
}
