#include "TitleBar.h"
#include "Gui.h"

TitleBar::TitleBar() {
	buttons[0] = &fileButton;
	buttons[1] = &modeButton;
	buttons[2] = &showButton;
	buttons[3] = &filterButton;
	buttonNames[0] = "File";
	buttonNames[1] = "Mode";
	buttonNames[2] = "Show";
	buttonNames[3] = "Filter";
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
	drawingButton.setPressedFunction(&Gui::setUserModeDrawing);
	transformButton.setPressedFunction(&Gui::setUserModeTransform);
	std::vector<CustomButton*> modeSubButtons = {&drawingButton, &transformButton};
	modeButton.setSubButtons(modeSubButtons);

	histogramButton.setup("Histogram", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	histogramButton.setPressedFunction(&Gui::showHistogram);
	skybox1Button.setup("Skybox 1", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	skybox1Button.setPressedFunction(&Gui::setSkybox1);
	skybox2Button.setup("Skybox 2", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	skybox2Button.setPressedFunction(&Gui::setSkybox2);
	skyboxGenButton.setup("Generate skybox", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	skyboxGenButton.setPressedFunction(&Gui::setGeneratedSkybox);
	std::vector<CustomButton*> showSubButtons = { &histogramButton, &skybox1Button, &skybox2Button, &skyboxGenButton };
	showButton.setSubButtons(showSubButtons);

	noFilterButton.setup("None", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	noFilterButton.setPressedFunction(&Gui::setFilterNone);
	grayFilterButton.setup("Gray", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	grayFilterButton.setPressedFunction(&Gui::setFilterGray);
	kelvinFilterButton.setup("Kelvin", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	kelvinFilterButton.setPressedFunction(&Gui::setFilterKelvin);
	nashvilleFilterButton.setup("Nashville", REGULAR_FONT, 0, 0, TITLE_BAR_HEIGHT);
	nashvilleFilterButton.setPressedFunction(&Gui::setFilterNashville);
	std::vector<CustomButton*> filterSubButtons = { &noFilterButton, &grayFilterButton, &kelvinFilterButton, &nashvilleFilterButton };
	filterButton.setSubButtons(filterSubButtons);
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

