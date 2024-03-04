#include "CustomButton.h"
#include "../Gui.h"


CustomButton::CustomButton() : ofxLabel() {
	gui = nullptr;
	labelStr = "";
	labelWidth = 0;
	labelFont = ofTrueTypeFont();
	isPressed = false;
	pressedFunction = nullptr;
	backgroundColor = BUTTON_DEFAULT_COLOR;
}

void CustomButton::setup(std::string label, std::string font, int x, int y, int height) {
	gui = Gui::getInstance();
	setupFont(label, font);
	setDefaultHeight(height);
	setDefaultWidth(labelWidth);
	setBackgroundColor(backgroundColor);

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
	loadFont(fontPath, FONT_SIZE); // for the ofxLabel
	labelFont.load(fontPath, FONT_SIZE); // for the ofTrueTypeFont
	labelWidth = labelFont.stringWidth(label) + FONT_WIDTH_ERROR;
}

bool CustomButton::mousePressed(ofMouseEventArgs& args) {
	if (getShape().inside(args.x, args.y)) {
		setBackgroundColor(BUTTON_PRESSED_COLOR);
		isPressed = true;
		if (pressedFunction != nullptr) {
			(gui->*pressedFunction)();
		}
		return true;
	}
	return false;
}

bool CustomButton::mouseReleased(ofMouseEventArgs& args) {
	if (isPressed) {
		setBackgroundColor(backgroundColor);
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
	setBackgroundColor(backgroundColor);
	return false;
}

void CustomButton::setWidth(float width) {
	setDefaultWidth(width);
	ofxLabel::setup("", labelStr);
	labelWidth = width;
}

void CustomButton::setPressedFunction(void (Gui::*_pressedFunction)()) {
	pressedFunction = _pressedFunction;
}

float CustomButton::getWidth() const {
	return labelWidth;
}

void CustomButton::setBackground(ofColor color) {
	backgroundColor = color;
	setBackgroundColor(color);
}
