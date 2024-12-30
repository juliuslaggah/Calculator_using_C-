#ifndef CONSTANT_MANAGER_H
#define CONSTANT_MANAGER_H

#include <string>
#include <unordered_map>

class ConstantManager {
public:
    ConstantManager();
    double getConstantValue(const std::string& name) const;
    std::string replaceConstants(const std::string& expression) const; // Add this declaration

    double calculateSin(double radians) const;
    double calculateCos(double radians) const;

private:
    std::unordered_map<std::string, double> constants;
};

#endif // CONSTANT_MANAGER_H
