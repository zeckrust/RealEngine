#include "TitleBarButton.h"

TitleBarButton::TitleBarButton() : CustomButton() {
	rectExtension = ofRectangle();
	subButtons = std::vector<CustomButton*>();
	showExtension = false;
	extensionWidth = 0;
	extensionHeight = 0;
	closeExtensionTimeStart = std::chrono::high_resolution_clock::now();
}

void TitleBarButton::draw() {
	CustomButton::draw();
	handleDrawExtension();
	drawSubButtons();
}

void TitleBarButton::drawSubButtons() {
	if (showExtension) {
		for (int i = 0; i < std::size(subButtons); i++) {
			if (subButtons[i] != nullptr) {
				subButtons[i]->draw();
			}
		}
	}
}

void TitleBarButton::drawExtension() {
	float posX = getPosition().x;
	float posY = getPosition().y + getHeight();

	rectExtension = ofRectangle(posX, posY, extensionWidth, extensionHeight);
	ofSetColor(TITLE_BAR_COLOR);
	ofDrawRectangle(rectExtension);
}

bool TitleBarButton::mousePressed(ofMouseEventArgs& args) {
	if (CustomButton::mousePressed(args)) {
		showExtension = true;
		return true;
	}
	else if(showExtension) {
		for (int i = 0; i < std::size(subButtons); i++) {
			if (subButtons[i] != nullptr && subButtons[i]->mousePressed(args)) {
				return true;
			}
		}
	}
	return false;
}

bool TitleBarButton::mouseMoved(ofMouseEventArgs& args) {
	bool isMouseOverButton = false;
	if (CustomButton::mouseMoved(args)) {
		isMouseOverButton = true;
	}
	else if(showExtension) {
		for (int i = 0; i < std::size(subButtons); i++) {
			if (subButtons[i] != nullptr && subButtons[i]->mouseMoved(args)) {
				isMouseOverButton = true;
			}
		}
	}
	return isMouseOverButton;
}

void TitleBarButton::handleDrawExtension() {
	if (showExtension && isMouseInExtension()) {
		drawExtension();
		closeExtensionTimeStart = std::chrono::high_resolution_clock::now();
	}
	else if (isInCloseThreshold()) {
		drawExtension();
	}
	else {
		showExtension = false;
	}
}

bool TitleBarButton::isMouseInExtension() {
	bool isInExtension = rectExtension.inside(ofGetMouseX(), ofGetMouseY());
	bool isInTitleButton = getHitBox().inside(ofGetMouseX(), ofGetMouseY());
	return isInExtension || isInTitleButton;
}

bool TitleBarButton::isInCloseThreshold() {
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - closeExtensionTimeStart);
	return duration.count() < BUTTON_CLOSE_EXTENSION_THRESHOLD_MS;
}

float TitleBarButton::getExtensionWidth() {
	return extensionWidth;
}

float TitleBarButton::getExtensionHeight() {
	return extensionHeight;
}

void TitleBarButton::setSubButtons(std::vector<CustomButton*> buttons) {
	subButtons = buttons;
	update();
}

void TitleBarButton::addSubButton(CustomButton* button) {
	subButtons.push_back(button);
	update();
}

void TitleBarButton::update() {
	updateExtensionWidth();
	updateExtensionHeight();
	updateSubButtons();
}

void TitleBarButton::updateExtensionWidth() {
	float width = 0;
	for (int i = 0; i < std::size(subButtons); i++) {
		if (subButtons[i] != nullptr && subButtons[i]->getWidth() > width) {
			width = subButtons[i]->getWidth();
		}
	}
	extensionWidth = width;
}

void TitleBarButton::updateExtensionHeight() {
	float height = 0;
	for (int i = 0; i < std::size(subButtons); i++) {
		if (subButtons[i] != nullptr) {
			height += subButtons[i]->getHeight();
		}
	}
	extensionHeight = height;
}

void TitleBarButton::updateSubButtons() {
	float nextPosY = getPosition().y + getHeight();
	float posX = getPosition().x;
	for (int i = 0; i < std::size(subButtons); i++) {
		if (subButtons[i] != nullptr) {
			if (i != 0) {
				nextPosY += subButtons[i - 1]->getHeight();
			}
			ofRectangle newHitBox = ofRectangle(posX, nextPosY, extensionWidth, subButtons[i]->getHeight());
			subButtons[i]->setHitBox(newHitBox);
			subButtons[i]->setWidth(extensionWidth);
			subButtons[i]->setPosition(posX, nextPosY);
		}
	}
}
