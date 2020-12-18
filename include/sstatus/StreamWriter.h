#ifndef STREAMWRITER_H
#define STREAMWRITER_H

#include <string>
#include <iostream>
#include <regex>

#include "sstatus/StatusItem.h"

class StreamWriter {
	public:
        void writeError(std::string);
		void writeStatusItem(std::string, bool);
		void beginStatusItemArray();
		void endStatusItemArray();
		void initJSONStream();
};

#endif
