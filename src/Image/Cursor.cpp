#include "Cursor.h"

Cursor::Cursor() {

}

void Cursor::setup() {
	cursorPosition = glm::vec2(-100, -100);
	loadCursors();
	changeCurrentCursor(CursorType::Normal);
}

void Cursor::update() {
	setCursorPosition();
}

void Cursor::draw() {
	ofHideCursor();
	ofPushStyle();
	ofSetColor(CURSOR_DEFAULT_COLOR);
	currentCursor.draw(cursorPosition);
	ofPopStyle();
}

void Cursor::mouseExited() {
	isMouseExited = true;
}

void Cursor::mouseEntered() {
	isMouseExited = false;
}

// algorithm to switch between cursors
void Cursor::changeCurrentCursor(CursorType newCursor) {
	currentCursor.clear();
	currentCursor.load(cursorsMap[newCursor]);
}

void Cursor::setCursorPosition() {
	if (isMouseExited) {
		cursorPosition = glm::vec2(-100, -100);
	}
	else {
		cursorPosition = glm::vec2(ofGetMouseX(), ofGetMouseY());
	}
}

void Cursor::loadCursors() {
	cursorsMap = {
		{ CursorType::Normal,		"cursors/normal-select.png" },
		{ CursorType::Unavailable,	"cursors/unavailable.png" },
		{ CursorType::Resize,		"cursors/move.png" },
		{ CursorType::Hand,			"cursors/link-select.png" },
		{ CursorType::Draw,			"cursors/handwriting.png" },
		{ CursorType::CrossAir,		"cursors/precision-select.png" }
	};
}
