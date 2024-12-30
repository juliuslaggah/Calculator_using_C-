#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <string>

class VariableManager {
public:
    void setVariable(const std::string& name, double value);
    double getVariable(const std::string& name);
    std::string replaceVariables(const std::string& expression);
};

#endif // VARIABLEMANAGER_H
