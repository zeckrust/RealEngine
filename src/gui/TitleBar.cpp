#include "TitleBar.h"

TitleBar::TitleBar() {
	buttons[0] = &fileButton;
	buttons[1] = &viewButton;
	buttons[2] = &windowButton;
	buttonNames[0] = "File";
	buttonNames[1] = "View";
	buttonNames[2] = "Window";

	setup();
}

void TitleBar::setup() {
	rect.setPosition(TITLE_BAR_POS_X, TITLE_BAR_POS_Y);
	rect.setSize(ofGetWindowWidth(), TITLE_BAR_HEIGHT);

	setupButtons();
}

void TitleBar::setupButtons() {
	float nextPosX = TITLE_BAR_BUTTON_PADDING;
	for (int i = 0; i < std::size(buttons); i++) {
		if (buttons[i] != nullptr) {
			if (i != 0) {
				nextPosX += buttons[i - 1]->getWidth() + TITLE_BAR_BUTTON_PADDING;
			}
			buttons[i]->setupLabel(buttonNames[i]);
			buttons[i]->setPosition(nextPosX, TITLE_BAR_POS_Y);
			buttons[i]->setupHitBox(nextPosX, TITLE_BAR_POS_Y);
		}
	}
}

void TitleBar::draw() {
	drawBar();
	drawButtons();
}

void TitleBar::drawBar() {
	ofSetColor(TITLE_BAR_COLOR_R, TITLE_BAR_COLOR_G, TITLE_BAR_COLOR_B);
	ofDrawRectangle(rect);
}

void TitleBar::drawButtons() {
	for (int i = 0; i < std::size(buttons); i++) {
		if (buttons[i] != nullptr) {
			buttons[i]->draw();
		}
	}
}

void TitleBar::updateWidth(int width) {
	rect.setWidth(width);
}

void TitleBar::mousePressed(int x, int y, int button) {
	ofMouseEventArgs mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Type::Pressed, x, y, button);

	for (int i = 0; i < std::size(buttons) ; i++) {
		if (buttons[i] != nullptr && buttons[i]->mousePressed(mouseEvent)) {
			break;
		}
	}
}

std::array<CustomButton*, TitleBar::MAX_NB_BUTTONS> TitleBar::getButtons() {
	return buttons;
}
