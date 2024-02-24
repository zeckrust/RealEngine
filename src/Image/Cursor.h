#pragma once
#include "ofxGui.h"
#include <map>
#include <string>

enum CursorType {
	Normal = 1,
	Unavailable,
	Resize,
	Hand,
	Draw,
	CrossAir
};

class Cursor
{
	public:
		Cursor();
		void setup();
		void changeCurrentCursor(CursorType cursorChange);
		void draw();
		void setCursorPosition(int x, int y);
	private:
		void loadCursors();

		std::map<CursorType, std::string> cursorsMap;
		ofImage currentCursor;
		glm::vec2 cursorPosition;
};