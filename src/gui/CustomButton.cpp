#include "CustomButton.h"

CustomButton::CustomButton() : ofxLabel() {
	setDefaultHeight(TITLE_BAR_HEIGHT);
	setDefaultWidth(TITLE_BAR_BUTTON_WIDTH);
	setBackgroundColor(BUTTON_DEFAULT_COLOR);

	hitBox = ofRectangle();
	isPressed = false;
}

void CustomButton::setupButton(std::string label, int x, int y) {
	setupLabel(label);
	setPosition(x, y);
	setupHitBox(x, y);
}

void CustomButton::setupLabel(std::string label) {
	ofxLabel::setup("", label);
}

void CustomButton::setupHitBox(int x, int y) {
	hitBox = ofRectangle(x, y, TITLE_BAR_BUTTON_WIDTH, TITLE_BAR_HEIGHT);
}

void CustomButton::draw() {
	ofxBaseGui::draw();
	handlePressedState();
}

bool CustomButton::mousePressed(ofMouseEventArgs& args) {
	if (hitBox.inside(args.x, args.y)) {
		setBackgroundColor(BUTTON_PRESSED_COLOR);
		isPressed = true;
		pressedTimeStart = std::chrono::high_resolution_clock::now();
		return true;
	}
	return false;
}

void CustomButton::handlePressedState() {
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - pressedTimeStart);

	if (isPressed && duration.count() > BUTTON_PRESSED_DURATION_MS) {
		setBackgroundColor(BUTTON_DEFAULT_COLOR);
		isPressed = false;
	}
}
