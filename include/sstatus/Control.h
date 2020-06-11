#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <string>
#include <cstdlib>

#include <thread>
#include <chrono>

#include "sstatus/ConfigParser.h"

#include "sstatus/StreamWriter.h"

#include "sstatus/StatusItem.h"
#include "sstatus/StatusItemPadding.h"
#include "sstatus/StatusItemSeparator.h"

#define REFRESH_RATE 1 // Number of refreshes per second

class Control {
	public:
		void launch();

	private:
		void generateStatus();
		void initItems();
        std::string getConfigFilePath();

        ConfigParser mConfigParser;
		std::vector<StatusItem*> mItems;
		StreamWriter mStreamWriter;
};

#endif
