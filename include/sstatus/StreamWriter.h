#ifndef STREAMWRITER_H
#define STREAMWRITER_H

#include <string>
#include <iostream>

#include "sstatus/StatusItem.h"

class StreamWriter {
	public:
		void writeStatusItem(std::string, bool);
		void beginStatusItemArray();
		void endStatusItemArray();
		void initJSONStream();
};

#endif
