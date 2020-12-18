#include "sstatus/ErrorHandler.h"

using namespace std;

bool ErrorHandler::errorInterrupt = false;
Error* ErrorHandler::currentError = nullptr;

void ErrorHandler::throwError(string errorMessage) {
    if(currentError != nullptr)
        delete currentError;
    Error* err = new Error(errorMessage);
    currentError = err;
    errorInterrupt = true;
}

bool ErrorHandler::getErrorInterrupt() {
    return errorInterrupt;
}

Error ErrorHandler::getCurrentError() {
    return *currentError;
}
