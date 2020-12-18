#ifndef STATUSITEM_H
#define STATUSITEM_H

#include <string>

#include "sstatus/ShellInterpreter.h"

class StatusItem {
	public:
		std::string getJsonText();

        std::string getFullText();
        std::string getForegroundColor();
        std::string getBackgroundColor();
        std::string getBorderColor();

        bool getSeparatorAfter();

        std::string getScript();

        void setForegroundColor(const std::string);
        void setBackgroundColor(const std::string);
        void setBorderColor(const std::string);
        void setScript(const std::string);
        void setInterval(const int);
	protected:
		std::string fullText = "";

		std::string foregroundColor = "";
		std::string backgroundColor = "";
		std::string borderColor = "";

		int borderWidthTop = 1;
		int borderWidthBottom = 1;
		int borderWidthLeft = 1;
		int borderWidthRight = 1;

		int minimumWidth = -1;

		std::string alignment = "left";

		std::string name = "";
		std::string instance = "";

		bool urgent = false;

		bool separatorAfter = true;
		int separatorBlockWidth = 9;

        std::string script;

        int interval; // Number of refresh cycles between refreshing this StatusItem
        int currentInterval = 0; // Number of refresh cycles before the next script refresh
        bool persistent = false; // Whether or not the script has been run for the first time when interval is set to -1
	private:
		class StatusItemJsonFormatter {
			public:
				static std::string statusItemToJson(StatusItem&);
		};

        ShellInterpreter mShellInterpreter;
};
#endif
