#include "TitleBarButton.h"

TitleBarButton::TitleBarButton() : CustomButton() {
	rectExtension = ofRectangle();
	subButtons = std::vector<CustomButton*>();
	showExtension = false;
}

void TitleBarButton::draw() {
	CustomButton::draw();
	handleShowExtension();
}

bool TitleBarButton::mousePressed(ofMouseEventArgs& args) {
	if (CustomButton::mousePressed(args)) {
		showExtension = true;
		return true;
	}
	return false;
}

void TitleBarButton::handleShowExtension() {
	float posX = getPosition().x;
	float posY = getPosition().y + getHeight();
	float width = getExtensionWidth();
	float height = getExtensionHeight();

	if (showExtension && isMouseInExtension(posX, posY, width, height)) {
		rectExtension = ofRectangle(posX, posY, width, height);
		ofSetColor(TITLE_BAR_COLOR);
		ofDrawRectangle(rectExtension);
	}
	else {
		showExtension = false;
	}
}

float TitleBarButton::getExtensionWidth() {
	float width = 0;
	for (int i = 0; i < std::size(subButtons); i++) {
		if (subButtons[i] != nullptr && subButtons[i]->getWidth() > width) {
			width = subButtons[i]->getWidth();
		}
	}
	return width;
}

float TitleBarButton::getExtensionHeight() {
	float height = 0;
	for (int i = 0; i < std::size(subButtons); i++) {
		if (subButtons[i] != nullptr) {
			height += subButtons[i]->getHeight();
		}
	}
	return height;

}

void TitleBarButton::setSubButtons(std::vector<CustomButton*> buttons) {
	subButtons = buttons;
}

void TitleBarButton::addSubButton(CustomButton* button) {
	subButtons.push_back(button);
}

bool TitleBarButton::isMouseInExtension(float x, float y, float width, float height) {
	bool isInExtension = rectExtension.inside(ofGetMouseX(), ofGetMouseY());
	bool isInTitleButton = getHitBox().inside(ofGetMouseX(), ofGetMouseY());
	return isInExtension || isInTitleButton;
}
