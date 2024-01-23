#include "CustomButton.h"

CustomButton::CustomButton() : ofxLabel() {
	labelStr = "";
	labelWidth = 0;
	labelFont = ofTrueTypeFont();
	isPressed = false;
	pressedFunction = nullptr;
}

void CustomButton::setup(std::string label, std::string font, int x, int y, int height) {
	setupFont(label, font);
	setDefaultHeight(height);
	setDefaultWidth(labelWidth);
	setBackgroundColor(BUTTON_DEFAULT_COLOR);

	setupLabel(label);
	setPosition(x, y);
}

void CustomButton::setupLabel(std::string label) {
	ofxLabel::setup("", label);
	labelStr = label;
}

void CustomButton::setupFont(std::string label, std::string font) {
	std::string executablePath = ofFilePath::getCurrentExeDir();
	std::string fontPath = ofFilePath::join(executablePath, font);
	loadFont(fontPath, BUTTON_FONT_SIZE); // for the ofxLabel
	labelFont.load(fontPath, BUTTON_FONT_SIZE); // for the ofTrueTypeFont
	labelWidth = labelFont.stringWidth(label) + FONT_WIDTH_ERROR;
}

bool CustomButton::mousePressed(ofMouseEventArgs& args) {
	if (getShape().inside(args.x, args.y)) {
		setBackgroundColor(BUTTON_PRESSED_COLOR);
		isPressed = true;
		if (pressedFunction != nullptr) {
			pressedFunction();
		}
		return true;
	}
	return false;
}

bool CustomButton::mouseReleased(ofMouseEventArgs& args) {
	if (isPressed) {
		setBackgroundColor(BUTTON_DEFAULT_COLOR);
		isPressed = false;
		return true;
	}
	return false;
}

bool CustomButton::mouseMoved(ofMouseEventArgs& args) {
	if (getShape().inside(args.x, args.y)) {
		setBackgroundColor(BUTTON_HOVER_COLOR);
		return true;
	}
	setBackgroundColor(BUTTON_DEFAULT_COLOR);
	return false;
}

void CustomButton::setWidth(float width) {
	setDefaultWidth(width);
	ofxLabel::setup("", labelStr);
	labelWidth = width;
}

void CustomButton::setPressedFunction(void (*_pressedFunction)()) {
	pressedFunction = _pressedFunction;
}

float CustomButton::getWidth() const {
	return labelWidth;
}
