#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
    public:
        Error(const std::string);
        std::string message;
};

#endif
