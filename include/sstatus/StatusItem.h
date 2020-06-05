#ifndef STATUSITEM_H
#define STATUSITEM_H

#include <string>

class StatusItem {
	public:
		std::string getJsonText();
		std::string getFullText();
	protected:
		std::string fullText = "";

		std::string foregroundColor = NULL;
		std::string backgroundColor = NULL;
		std::string borderColor = NULL;

		int borderWidthTop = 1;
		int borderWidthBottom = 1;
		int borderWidthLeft = 1;
		int borderWidthRight = 1;

		int minimumWidth = -1;

		std::string alignment = "left";

		std::string name = NULL;
		std::string instance = NULL;

		bool urgent = false;

		bool separatorAfter = true;
		int separatorBlockWidth = 9;
	private:
		class StatusItemJsonFormatter {
			public:
				static std::string statusItemToJson(StatusItem&);
		};
};
#endif
