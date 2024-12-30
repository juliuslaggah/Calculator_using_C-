#include "BaseConversion.h"
#include <cmath>
#include <stdexcept>

int BaseConversion::hexToDecimal(const std::string& hex) {
    int result = 0;
    for (char c : hex) {
        result *= 16;
        if (c >= '0' && c <= '9') {
            result += c - '0';
        } else if (c >= 'A' && c <= 'F') {
            result += c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            result += c - 'a' + 10;
        } else {
            throw std::runtime_error("Invalid hexadecimal character: " + std::string(1, c));
        }
    }
    return result;
}

int BaseConversion::binaryToDecimal(const std::string& binary) {
    int result = 0;
    for (char c : binary) {
        if (c == '0' || c == '1') {
            result = result * 2 + (c - '0');
        } else {
            throw std::runtime_error("Invalid binary character: " + std::string(1, c));
        }
    }
    return result;
}
