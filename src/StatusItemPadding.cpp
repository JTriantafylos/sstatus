#include "sstatus/StatusItemPadding.h"

StatusItemPadding::StatusItemPadding(int mWidth) : width(mWidth) {
	for(int i = 0; i < mWidth; i++)
		fullText += PADDING_CHAR;
}

int StatusItemPadding::getWidth() {
	return width;
}
