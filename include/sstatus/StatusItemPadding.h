#ifndef STATUSITEMPADDING_H
#define STATUSITEMPADDING_H

#include "sstatus/StatusItem.h"

#define PADDING_CHAR ' '

class StatusItemPadding : public StatusItem {
	public:
		StatusItemPadding(int);
		int getWidth();
	private:
		int width;
};

#endif
