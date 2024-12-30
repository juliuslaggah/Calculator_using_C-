#ifndef BASECONVERSION_H
#define BASECONVERSION_H

#include <string>

class BaseConversion {
public:
    int hexToDecimal(const std::string& hex);
    int binaryToDecimal(const std::string& binary);
};

#endif // BASECONVERSION_H
