#include "CustomButton.h"

CustomButton::CustomButton() : ofxLabel() {
	hitBox = ofRectangle();
	labelStr = "";
	labelWidth = 0;
	labelFont = ofTrueTypeFont();
	isPressed = false;
	pressedFunction = nullptr;
	pressedTimeStart = std::chrono::high_resolution_clock::now();
}

void CustomButton::setup(std::string label, std::string font, int x, int y, int height) {
	setupFont(label, font);
	setDefaultHeight(height);
	setDefaultWidth(labelWidth);
	setBackgroundColor(BUTTON_DEFAULT_COLOR);

	setupLabel(label);
	setPosition(x, y);
	setupHitBox(x, y);
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

void CustomButton::setupHitBox(int x, int y) {
	hitBox = ofRectangle(x, y, labelWidth, TITLE_BAR_HEIGHT);
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
		if (pressedFunction != nullptr) {
			pressedFunction();
		}
		return true;
	}
	return false;
}

bool CustomButton::mouseMoved(ofMouseEventArgs& args) {
	if (hitBox.inside(args.x, args.y)) {
		setBackgroundColor(BUTTON_HOVER_COLOR);
		return true;
	}
	setBackgroundColor(BUTTON_DEFAULT_COLOR);
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

void CustomButton::setWidth(float width) {
	setDefaultWidth(width);
	ofxLabel::setup("", labelStr);
	labelWidth = width;
}

void CustomButton::setHitBox(ofRectangle rect) {
	hitBox = rect;
}

void CustomButton::setPressedFunction(void (*_pressedFunction)()) {
	pressedFunction = _pressedFunction;
}

float CustomButton::getWidth() const {
	return labelWidth;
}

ofRectangle CustomButton::getHitBox() const {
	return hitBox;
}
