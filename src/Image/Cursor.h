#pragma once

#include "ofxGui.h"
#include <map>
#include <string>

class Gui;

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
		void update();
		void draw();
		void mouseExited();
		void mouseEntered();
		void changeCurrentCursor(CursorType cursorChange);

	private:
		void setCursorPosition();
		void updateCursorType();
		void handleTransformCursorType();
		void loadCursors();

		bool isMouseExited = false;
		std::map<CursorType, std::string> cursorsMap;
		ofImage currentCursor;
		glm::vec2 cursorPosition;

		const ofColor CURSOR_DEFAULT_COLOR = ofColor(78, 59, 255, 255);

		Gui* gui = nullptr;
};