#include "ColorPanel.h"

ColorPanel::ColorPanel() : CustomPanel() {

}

void ColorPanel::setup(std::string panelName, float x, float y, ofColor defaultColor) {
	CustomPanel::setup(panelName, x, y);
	setupSliders(defaultColor);
	currentColorMode = RGB;
	currentColor = defaultColor;
}

void ColorPanel::update(void) {
	CustomPanel::update();

	switch (currentColorMode) {
		case RGB: {
			currentColor.set(slider1, slider2, slider3);
			break;
		}
		case HSB: {
			currentColor.setHsb(slider1 / 360, slider2 / 100, slider3 / 100);
			break;
		}
		default: {
			break;
		}
	}

	setBorderColor(currentColor);
}

void ColorPanel::draw(void) {
	if (isGuiDrawing()) {
		ofPushStyle();
		ofSetColor(currentColor);
		ofNoFill();
		ofSetLineWidth(BORDER_LINE_WIDTH);
		ofDrawRectangle(getShape());
		ofPopStyle();
	}
}

void ColorPanel::setupSliders(ofColor defaultColor) {
	slider1.setup("R", defaultColor.r, 0, 255);
	slider2.setup("G", defaultColor.g, 0, 255);
	slider3.setup("B", defaultColor.b, 0, 255);

	add(&slider1);
	add(&slider2);
	add(&slider3);
}

void ColorPanel::setColorMode(ColorMode mode) {
	currentColorMode = mode;

	switch (mode) {
		case RGB: {
			slider1.setup("R", currentColor.r, 0, 255);
			slider2.setup("G", currentColor.g, 0, 255);
			slider3.setup("B", currentColor.b, 0, 255);
			break;
		}
		case HSB: {
			slider1.setup("H", currentColor.getHue() * 360, 0, 360);
			slider2.setup("S", currentColor.getSaturation() * 100, 0, 100);
			slider3.setup("B", currentColor.getBrightness() * 100, 0, 100);
			break;
		}
		default: {
			break;
		}
	}
}

ofColor ColorPanel::getColor(void) {
	return currentColor;
}