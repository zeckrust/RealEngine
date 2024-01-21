#include "TitleBar.h"

TitleBar::TitleBar() {
	setup();
}

void TitleBar::setup() {
	rect.setPosition(TITLE_BAR_POS_X, TITLE_BAR_POS_Y);
	rect.setSize(ofGetWindowWidth(), TITLE_BAR_HEIGHT);

	setupButtons();
}

void TitleBar::setupButtons() {
	buttons[0] = &fileButton;
	buttons[1] = &viewButton;
	buttons[2] = &windowButton;
	
	fileButton.setupLabel("File");
	viewButton.setupLabel("View");
	windowButton.setupLabel("Window");
	setupButtonsPosition();
}

void TitleBar::setupButtonsPosition() {
	float nextPosX = TITLE_BAR_BUTTON_PADDING;
	for (int i = 0; i < std::size(buttons); i++) {
		if (buttons[i] != nullptr) {
			if (i != 0) {
				nextPosX += buttons[i - 1]->getWidth() + TITLE_BAR_BUTTON_PADDING;
			}
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

void TitleBar::update(int width) {
	rect.setWidth(width);
}

std::array<CustomButton*, TitleBar::MAX_NB_BUTTONS> TitleBar::getButtons() {
	return buttons;
}
