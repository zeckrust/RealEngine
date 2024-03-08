#pragma once

#include "ofxGui.h"
#include <map>
#include <string>

class Gui;

enum CursorType {
	Normal = 0,
	Move,
	Hand,
	Draw,
	Rotate
};

class Cursor
{
	public:
		Cursor();
		void setup();
		void update();
		void draw();
		void mouseMoved(ofMouseEventArgs& args);
		void mouseExited();
		void mouseEntered();
		void changeCurrentCursor(CursorType cursorChange);

	private:
		void handleMouseExit();
		void updateCursorType();
		void handleTransformCursorType();
		void loadCursors();

		bool isMouseExited = false;
		std::map<CursorType, std::string> cursorsMap;
		ofImage currentCursor;
		glm::vec2 cursorPosition;

		const ofColor CURSOR_DEFAULT_COLOR = ofColor(255, 255, 255, 255);

		Gui* gui = nullptr;
};