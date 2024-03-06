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
	setCursorPosition();
	updateCursorType();
}

void Cursor::updateCursorType() {
	ofRectangle scene2DShape = gui->getScene2DShape();
	ofRectangle scene3DShape = gui->getScene3DShape();
	bool insideScene2D = scene2DShape.inside(ofGetMouseX(), ofGetMouseY());
	bool insideScene3D = scene3DShape.inside(ofGetMouseX(), ofGetMouseY());

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

void Cursor::handleTransformCursorType() {
	switch (gui->getSelectedTransformTool()) {
		case TRANSLATION: {
			changeCurrentCursor(CursorType::Resize);
			break;
		}
		case ROTATION: {
			changeCurrentCursor(CursorType::Hand);
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
		{ CursorType::Normal,		"cursors/normal-select.png" },
		{ CursorType::Unavailable,	"cursors/unavailable.png" },
		{ CursorType::Resize,		"cursors/move.png" },
		{ CursorType::Hand,			"cursors/link-select.png" },
		{ CursorType::Draw,			"cursors/handwriting.png" },
		{ CursorType::CrossAir,		"cursors/precision-select.png" }
	};
}
