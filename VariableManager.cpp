#include "VariableManager.h"
#include <unordered_map>
#include <stdexcept>

static std::unordered_map<std::string, double> variables;

void VariableManager::setVariable(const std::string& name, double value) {
    variables[name] = value;
}

double VariableManager::getVariable(const std::string& name) {
    if (variables.find(name) != variables.end()) {
        return variables[name];
    }
    throw std::runtime_error("Undefined variable: " + name);
}

std::string VariableManager::replaceVariables(const std::string& expression) {
    std::string result = expression;
    for (const auto& var : variables) {
        size_t pos;
        while ((pos = result.find(var.first)) != std::string::npos) {
            result.replace(pos, var.first.length(), std::to_string(var.second));
        }
    }
    return result;
}
