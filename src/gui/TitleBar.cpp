#include "TitleBar.h"
#include "buttons/ButtonsDefinition.h"

TitleBar::TitleBar() {
	buttons[0] = &fileButton;
	buttons[1] = &viewButton;
	buttons[2] = &windowButton;
	buttonNames[0] = "File";
	buttonNames[1] = "View";
	buttonNames[2] = "Window";

	setup();

	// Only for test purposes
	testButton1.setup("import", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	testButton2.setup("export", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	testButton3.setup("test3", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	testButton1.setPressedFunction(&ButtonsDefinition::import);
	std::vector<CustomButton*> testSubButtons {&testButton1, &testButton2, &testButton3};
	fileButton.setSubButtons(testSubButtons);
}

void TitleBar::setup() {
	rect.setPosition(TITLE_BAR_POS_X, TITLE_BAR_POS_Y);
	rect.setSize(ofGetWindowWidth(), TITLE_BAR_HEIGHT);
	lineLimit.setPosition(rect.getPosition().x, rect.getPosition().y + rect.getHeight());
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
	ofDrawRectangle(rect);
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
	rect.setWidth(width);
	lineLimit.setWidth(width);
}

void TitleBar::mousePressed(int x, int y, int button) {
	ofMouseEventArgs mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Type::Pressed, x, y, button);
	for (int i = 0; i < std::size(buttons) ; i++) {
		if (buttons[i] != nullptr && buttons[i]->mousePressed(mouseEvent)) {
			break;
		}
	}
}

void TitleBar::mouseReleased(int x, int y, int button) {
	ofMouseEventArgs mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Type::Pressed, x, y, button);
	for (int i = 0; i < std::size(buttons) ; i++) {
		if (buttons[i] != nullptr && buttons[i]->mouseReleased(mouseEvent)) {
			break;
		}
	}
}

void TitleBar::mouseMoved(int x, int y) {
	ofMouseEventArgs mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Type::Moved, x, y);
	for (int i = 0; i < std::size(buttons) ; i++) {
		if (buttons[i] != nullptr && buttons[i]->mouseMoved(mouseEvent)) {
			break;
		}
	}
}

std::array<TitleBarButton*, TitleBar::MAX_NB_BUTTONS> TitleBar::getButtons() {
	return buttons;
}
