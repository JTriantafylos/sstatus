#include "sstatus/StatusItem.h"

using namespace std;

string StatusItem::getJsonText() {
    return StatusItemJsonFormatter::statusItemToJson(*this);
}

string StatusItem::getFullText() {
	return fullText;
}

string StatusItem::StatusItemJsonFormatter::statusItemToJson(StatusItem& item) {
   string jsonString = "";

   jsonString.append("{");

   jsonString.append("\"full_text\": ");
   jsonString.append("\"");
   jsonString.append(item.fullText);
   jsonString.append("\"");

   jsonString.append("}");

   return jsonString;
}
