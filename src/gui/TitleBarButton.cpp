#include "TitleBarButton.h"

TitleBarButton::TitleBarButton() : CustomButton() {
	rectExtension = ofRectangle();
	subButtons = std::vector<CustomButton*>();
	showExtension = false;
	extensionWidth = 0;
	extensionHeight = 0;
}

void TitleBarButton::draw() {
	CustomButton::draw();
	handleShowExtension();
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

void TitleBarButton::handleShowExtension() {
	float posX = getPosition().x;
	float posY = getPosition().y + getHeight();

	if (showExtension && isMouseInExtension(posX, posY, extensionWidth, extensionHeight)) {
		rectExtension = ofRectangle(posX, posY, extensionWidth, extensionHeight);
		ofSetColor(TITLE_BAR_COLOR);
		ofDrawRectangle(rectExtension);
	}
	else {
		showExtension = false;
	}
}

bool TitleBarButton::isMouseInExtension(float x, float y, float width, float height) {
	bool isInExtension = rectExtension.inside(ofGetMouseX(), ofGetMouseY());
	bool isInTitleButton = getHitBox().inside(ofGetMouseX(), ofGetMouseY());
	return isInExtension || isInTitleButton;
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
