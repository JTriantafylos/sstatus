#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <string>

#include "sstatus/Error.h"

class ErrorHandler {
	public:
        static void throwError(std::string);
        static bool getErrorInterrupt();
        static Error getCurrentError();

    private:
        static bool errorInterrupt;
        static Error* currentError;
};

#endif
