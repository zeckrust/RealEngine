#include "CustomButton.h"

CustomButton::CustomButton() : ofxLabel() {
	setDefaultHeight(TITLE_BAR_HEIGHT);
	setDefaultWidth(TITLE_BAR_BUTTON_WIDTH);
	setBackgroundColor(DEFAULT_BUTTON_COLOR);

	hitBox = ofRectangle();
	isPressed = false;
}

void CustomButton::setupLabel(std::string label) {
	ofxLabel::setup("", label);
}

void CustomButton::setupHitBox(int x, int y) {
	hitBox = ofRectangle(x, y, TITLE_BAR_BUTTON_WIDTH, TITLE_BAR_HEIGHT);
}

bool CustomButton::mousePressed(ofMouseEventArgs& args) {
	if (hitBox.inside(args.x, args.y)) {
		setBackgroundColor(PRESSED_BUTTON_COLOR);
		isPressed = true;
		pressedTimeStart = std::chrono::high_resolution_clock::now();
		return true;
	}
	return false;
}

void CustomButton::draw() {
	ofxBaseGui::draw();

	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - pressedTimeStart);

	if (isPressed && duration.count() < 1) {
		setBackgroundColor(DEFAULT_BUTTON_COLOR);
	}
}
