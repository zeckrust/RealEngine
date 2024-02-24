#include "Cursor.h"

Cursor::Cursor() {

}

void Cursor::setup() {
	cursorPosition = glm::vec2(-100, -100);
	loadCursors();
	changeCurrentCursor(CursorType::Normal);
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

// algorithm to switch between cursors
void Cursor::changeCurrentCursor(CursorType newCursor) {
	currentCursor.clear();
	currentCursor.load(cursorsMap[newCursor]);
}

void Cursor::draw() {
	ofHideCursor();
	currentCursor.draw(cursorPosition);
}

void Cursor::setCursorPosition(int x, int y) {
	cursorPosition = glm::vec2(x, y);
}