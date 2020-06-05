#include "sstatus/Control.h"

using namespace std;

void Control::launch() {
    mStreamWriter.initJSONStream();
    initItems();

    while(true) {
        generateStatus();
        usleep(REFRESH_RATE);
    }
}

void Control::generateStatus() {
    mStreamWriter.beginStatusItemArray();
    for(std::vector<StatusItem*>::iterator it = mItems.begin(); it != mItems.end(); ++it) {
        bool lastItem = false;
        if(it + 1 == mItems.end())
            lastItem = true;
        StatusItem* item = *it;
        mStreamWriter.writeStatusItem(item->getJsonText(), lastItem);
    }
    mStreamWriter.endStatusItemArray();
}

void Control::initItems() {
    StatusItem* mItem0 = new StatusItemSeparator();
    StatusItem* mItem1 = new StatusItemPadding(4);
    StatusItem* mItem2 = new StatusItemSeparator();
    StatusItem* mItem3 = new StatusItemPadding(2);
    StatusItem* mItem4 = new StatusItemSeparator();
    StatusItem* mItem5 = new StatusItemPadding(8);

    mItems.push_back(mItem0);
    mItems.push_back(mItem1);
    mItems.push_back(mItem2);
    mItems.push_back(mItem3);
    mItems.push_back(mItem4);
    mItems.push_back(mItem5);
}
