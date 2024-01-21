#include "CustomButton.h"

CustomButton::CustomButton() : ofxLabel() {
	setDefaultHeight(TITLE_BAR_HEIGHT);
	setDefaultWidth(TITLE_BAR_BUTTON_WIDTH);
	setBackgroundColor(ofColor(0, 0, 0, 0));
	hitBox = ofRectangle();
}

void CustomButton::setupLabel(std::string label) {
	ofxLabel::setup("", label);
}

void CustomButton::setupHitBox(int x, int y) {
	hitBox = ofRectangle(x, y, TITLE_BAR_BUTTON_WIDTH, TITLE_BAR_HEIGHT);
}

bool CustomButton::mousePressed(ofMouseEventArgs& args) {
	bool isPressed = false;
	if (hitBox.inside(args.x, args.y)) {
		std::cout << "YO big";
		isPressed = true;
	}
	return isPressed;
}
