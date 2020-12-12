#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <string>
#include <cstdlib>

#include <thread>
#include <chrono>

#include "toml++/toml.h"

#include "sstatus/ConfigParser.h"

#include "sstatus/StreamWriter.h"

#include "sstatus/StatusItem.h"

class Control {
	public:
		void launch();

	private:
		void generateStatus();
        std::string getConfigFilePath();

        int mRefreshTime;
		std::vector<StatusItem*> mItems;
        ConfigParser mConfigParser;
		StreamWriter mStreamWriter;
};

#endif
