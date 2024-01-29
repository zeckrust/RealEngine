#include "TitleBar.h"

TitleBar::TitleBar() {
	buttons[0] = &fileButton;
	buttons[1] = &viewButton;
	buttons[2] = &windowButton;
	buttonNames[0] = "File";
	buttonNames[1] = "View";
	buttonNames[2] = "Window";

	setup();

	// Only for test purposes
	testButton1.setup("_______test1_______", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	testButton2.setup("test2", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	testButton3.setup("test3", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	std::vector<CustomButton*> testSubButtons {&testButton1, &testButton2, &testButton3};
	fileButton.setSubButtons(testSubButtons);
}

void TitleBar::setup() {
	rectBackground.setPosition(TITLE_BAR_POS_X, TITLE_BAR_POS_Y);
	rectBackground.setSize(ofGetWindowWidth(), TITLE_BAR_HEIGHT);
	lineLimit.setPosition(rectBackground.getPosition().x, rectBackground.getPosition().y + rectBackground.getHeight());
	lineLimit.setSize(ofGetWindowWidth(), TITLE_BAR_LINE_LIMIT_HEIGHT);

	setupButtons();
}

void TitleBar::setupButtons() {
	float nextPosX = TITLE_BAR_BUTTON_PADDING;
	for (int i = 0; i < std::size(buttons); i++) {
		if (buttons[i] != nullptr) {
			if (i != 0) {
				nextPosX += buttons[i - 1]->getWidth() + TITLE_BAR_BUTTON_PADDING;
			}
			buttons[i]->setup(buttonNames[i], BOLD_FONT, nextPosX, TITLE_BAR_POS_Y, TITLE_BAR_HEIGHT);
		}
	}
}

void TitleBar::draw() {
	drawBar();
	drawButtons();
}

void TitleBar::drawBar() {
	ofSetColor(TITLE_BAR_COLOR);
	ofDrawRectangle(rectBackground);
	ofSetColor(TITLE_BAR_LINE_LIMIT_COLOR);
	ofDrawRectangle(lineLimit);
}

void TitleBar::drawButtons() {
	for (int i = 0; i < std::size(buttons); i++) {
		if (buttons[i] != nullptr) {
			buttons[i]->draw();
		}
	}
}

void TitleBar::updateWidth(int width) {
	rectBackground.setWidth(width);
	lineLimit.setWidth(width);
}

bool TitleBar::mousePressed(ofMouseEventArgs& args) {
	for (int i = 0; i < std::size(buttons) ; i++) {
		if (buttons[i] != nullptr && buttons[i]->mousePressed(args)) {
			return true;
		}
	}
	return false;
}

bool TitleBar::mouseReleased(ofMouseEventArgs& args) {
	for (int i = 0; i < std::size(buttons) ; i++) {
		if (buttons[i] != nullptr && buttons[i]->mouseReleased(args)) {
			return true;
		}
	}
	return false;
}

bool TitleBar::mouseMoved(ofMouseEventArgs& args) {
	for (int i = 0; i < std::size(buttons) ; i++) {
		if (buttons[i] != nullptr && buttons[i]->mouseMoved(args)) {
			return true;
		}
	}
	return false;
}

float TitleBar::getHeight() {
	return rectBackground.getHeight() + lineLimit.getHeight();
}

std::array<TitleBarButton*, TitleBar::MAX_NB_BUTTONS> TitleBar::getButtons() {
	return buttons;
}
