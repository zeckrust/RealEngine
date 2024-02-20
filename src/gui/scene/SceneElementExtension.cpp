#include "SceneElementExtension.h"

SceneElementExtension::SceneElementExtension() {

}

void SceneElementExtension::setup(void) {
	selectButton.setup(SELECT_STR, REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	selectButton.setWidth(DEFAULT_EXTENSION_WIDTH);
	deleteButton.setup(DELETE_STR, REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	deleteButton.setWidth(DEFAULT_EXTENSION_WIDTH);
	extensionRect.setSize(DEFAULT_EXTENSION_WIDTH, 2*DEFAULT_BUTTON_HEIGHT);
}

void SceneElementExtension::draw(void) {
	if (isDisplayed) {
		ofPushStyle();
		ofSetColor(EXTENSION_COLOR);
		ofDrawRectangle(extensionRect);
		ofPopStyle();

		selectButton.draw();
		deleteButton.draw();
	}
}

void SceneElementExtension::show(void) {
	isDisplayed = true;
}

void SceneElementExtension::hide(void) {
	isDisplayed = false;
}

void SceneElementExtension::updatePosition(float x, float y) {
	extensionRect.setPosition(x, y);
	selectButton.setPosition(x, y);
	deleteButton.setPosition(x, selectButton.getPosition().y + selectButton.getHeight());
}

bool SceneElementExtension::mousePressed(ofMouseEventArgs& args) {
	bool isClickInside = extensionRect.inside(args.x, args.y);
	if (args.button == OF_MOUSE_BUTTON_RIGHT) {
		updatePosition(args.x, args.y);
		return false;
	}
	else if (isClickInside && args.button == OF_MOUSE_BUTTON_LEFT) {
		bool isClickInSelect = selectButton.mousePressed(args);
		bool isClickInDelete = deleteButton.mousePressed(args);
		return isClickInSelect || isClickInDelete;
	}
	return false;
}

bool SceneElementExtension::mouseReleased(ofMouseEventArgs& args) {
	bool isMouseInside = false;
	if (extensionRect.inside(args.x, args.y)) {
		isMouseInside |= selectButton.mouseReleased(args);
		isMouseInside |= deleteButton.mouseReleased(args);
	}
	return isMouseInside;
}

bool SceneElementExtension::mouseMoved(ofMouseEventArgs& args) {
	bool isMouseInside = false;
	if (extensionRect.inside(args.x, args.y)) {
		isMouseInside |= selectButton.mouseMoved(args);
		isMouseInside |= deleteButton.mouseMoved(args);
	}
	return isMouseInside;
}
