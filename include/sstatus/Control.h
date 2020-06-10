#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <string>
#include <unistd.h>

#include "sstatus/StreamWriter.h"

#include "sstatus/StatusItem.h"
#include "sstatus/StatusItemPadding.h"
#include "sstatus/StatusItemSeparator.h"

#define REFRESH_RATE 10 // Number of refreshes per second

class Control {
	public:
		void launch();

	private:
		void generateStatus();
		void initItems();

		std::vector<StatusItem*> mItems;
		StreamWriter mStreamWriter;
};

#endif
