#include "Cursor.h"
#include "../gui/Gui.h"

Cursor::Cursor() {

}

void Cursor::setup() {
	gui = Gui::getInstance();
	cursorPosition = glm::vec2(-100, -100);
	loadCursors();
	changeCurrentCursor(CursorType::Normal);
}

void Cursor::update() {
	handleMouseExit();
	updateCursorType();
}

void Cursor::updateCursorType() {
	ofRectangle scene2DShape = gui->getScene2DShape();
	ofRectangle scene3DShape = gui->getScene3DShape();
	bool insideScene2D = scene2DShape.inside(cursorPosition.x, cursorPosition.y);
	bool insideScene3D = scene3DShape.inside(cursorPosition.x, cursorPosition.y);

	if (insideScene2D || insideScene3D) {
		switch (gui->getSelectedUserMode()) {
			case DRAWING: {
				changeCurrentCursor(CursorType::Draw);
				break;
			}
			case TRANSFORM: {
				handleTransformCursorType();
				break;
			}
			default: {
				changeCurrentCursor(CursorType::Normal);
				break;
			}
		}
	}
	else {
		changeCurrentCursor(CursorType::Normal);
	}
}

void Cursor::draw() {
	ofHideCursor();
	ofPushStyle();
	ofSetColor(CURSOR_DEFAULT_COLOR);
	currentCursor.draw(cursorPosition);
	ofPopStyle();
}

void Cursor::mouseMoved(ofMouseEventArgs& args) {
	cursorPosition.x = args.x;
	cursorPosition.y = args.y;
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

void Cursor::handleMouseExit() {
	if (isMouseExited) {
		cursorPosition = glm::vec2(-100, -100);
	}
}

void Cursor::handleTransformCursorType() {
	switch (gui->getSelectedTransformTool()) {
		case TRANSLATION: {
			changeCurrentCursor(CursorType::Move);
			break;
		}
		case ROTATION: {
			changeCurrentCursor(CursorType::Rotate);
			break;
		}
		case SCALE: {
			changeCurrentCursor(CursorType::Hand);
			break;
		}
		default: {
			changeCurrentCursor(CursorType::Normal);
			break;
		}
	}
}

void Cursor::loadCursors() {
	cursorsMap = {
		{ CursorType::Normal,		"cursors/cursor.png" },
		{ CursorType::Move,			"cursors/move.png" },
		{ CursorType::Hand,			"cursors/hand.png" },
		{ CursorType::Draw,			"cursors/pen.png" },
		{ CursorType::Rotate,		"cursors/rotate.png" }
	};
}
