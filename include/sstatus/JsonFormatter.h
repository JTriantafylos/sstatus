#ifndef JSONFORMATTER_H
#define JSONFORMATTER_H

#include <string>

#include "sstatus/StatusItem.h"

class JsonFormatter {
	public:
		static std::string statusItemToJson(StatusItem&);
};

#endif
