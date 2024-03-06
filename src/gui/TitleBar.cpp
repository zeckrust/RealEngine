#include "TitleBar.h"
#include "Gui.h"

TitleBar::TitleBar() {
	buttons[0] = &fileButton;
	buttons[1] = &modeButton;
	buttons[2] = &showButton;
	buttonNames[0] = "File";
	buttonNames[1] = "Mode";
	buttonNames[2] = "Show";
}

void TitleBar::setup() {
	rectBackground.setPosition(TITLE_BAR_POS_X, TITLE_BAR_POS_Y);
	rectBackground.setSize(ofGetWindowWidth(), TITLE_BAR_HEIGHT);
	lineLimit.setPosition(rectBackground.getPosition().x, rectBackground.getPosition().y + rectBackground.getHeight());
	lineLimit.setSize(ofGetWindowWidth(), TITLE_BAR_LINE_LIMIT_HEIGHT);

	setupButtons();

	importButton.setup("Import", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	exportButton.setup("Export", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	importButton.setPressedFunction(&Gui::importFile);
	exportButton.setPressedFunction(&Gui::saveScenes);
	std::vector<CustomButton*> fileSubButtons {&importButton, &exportButton};
	fileButton.setSubButtons(fileSubButtons);

	drawingButton.setup("Drawing", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	transformButton.setup("Transform", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	std::vector<CustomButton*> modeSubButtons = {&drawingButton, &transformButton};
	modeButton.setSubButtons(modeSubButtons);

	histogramButton.setup("Histogram", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	histogramButton.setPressedFunction(&Gui::showHistogram);
	std::vector<CustomButton*> showSubButtons{ &histogramButton };
	showButton.setSubButtons(showSubButtons);
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
	ofPushStyle();
	ofSetColor(TITLE_BAR_COLOR);
	ofDrawRectangle(rectBackground);
	ofSetColor(TITLE_BAR_LINE_LIMIT_COLOR);
	ofDrawRectangle(lineLimit);
	ofPopStyle();
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
	bool isOnTitleBar = false;
	for (int i = 0; i < std::size(buttons) ; i++) {
		if (buttons[i] != nullptr && buttons[i]->mouseMoved(args)) {
			isOnTitleBar = true;
		}
	}
	return isOnTitleBar;
}

float TitleBar::getHeight() {
	return rectBackground.getHeight() + lineLimit.getHeight();
}

std::array<TitleBarButton*, TitleBar::MAX_NB_BUTTONS> TitleBar::getButtons() {
	return buttons;
}

