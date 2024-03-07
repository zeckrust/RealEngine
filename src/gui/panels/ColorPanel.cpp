#include "ColorPanel.h"
#include <cmath>

ColorPanel::ColorPanel() : CustomPanel() {
	enableListeners();
}

void ColorPanel::setup(std::string panelName, float x, float y, ofColor defaultColor) {
	CustomPanel::setup(panelName, x, y);
	setupButton();
	setupSliders(defaultColor);
	currentColor = defaultColor;
	minimize();
}

void ColorPanel::setupButton(void) {
	colorModeButton.setup(RGB_STR, REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	add(&colorModeButton);
}

void ColorPanel::setupSliders(ofColor defaultColor) {
	slider1.setup(R_STR, defaultColor.r, 0, 255);
	slider2.setup(G_STR, defaultColor.g, 0, 255);
	slider3.setup(B_STR, defaultColor.b, 0, 255);

	add(&slider1);
	add(&slider2);
	add(&slider3);
}

void ColorPanel::update(void) {
	CustomPanel::update();

	if (!ofGetMousePressed()) {
		showColorSample = false;
	}
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
	if (showColorSample) {
		ofPushStyle();
		ofSetColor(currentColor);
		ofDrawRectangle(colorSampleRect);
		ofPopStyle();
	}
}

bool ColorPanel::mousePressed(ofMouseEventArgs& args) {
	if (!isMinimized() && colorModeButton.getShape().inside(args.x, args.y)) {
		changeColorMode();
	}
	return CustomPanel::mousePressed(args);
}

void ColorPanel::changeColorMode(void) {
	disableListeners();
	if (currentColorMode == RGB ? currentColorMode = HSB : currentColorMode = RGB);

	switch (currentColorMode) {
		case RGB: {
			slider1.setup(R_STR, currentColor.r, 0, 255);
			slider2.setup(G_STR, currentColor.g, 0, 255);
			slider3.setup(B_STR, currentColor.b, 0, 255);
			colorModeButton.setup(RGB_STR, REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
			break;
		}
		case HSB: {
			slider1.setup(H_STR, currentColor.getHueAngle(), 0, 360);
			slider2.setup(S_STR, TO_SLIDER_VALUE(currentColor.getSaturation()), 0, 100);
			slider3.setup(B_STR, TO_SLIDER_VALUE(currentColor.getBrightness()), 0, 100);
			colorModeButton.setup(HSB_STR, REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
			break;
		}
		default: {
			break;
		}
	}
	enableListeners();
}

ofColor ColorPanel::getColor(void) {
	return currentColor;
}

void ColorPanel::handleSliderChanged(int &_) {
	showColorSample = true;

	glm::vec3 pos = colorModeButton.getPosition();
	colorSampleRect = ofRectangle(pos.x, pos.y, getWidth(), DEFAULT_BUTTON_HEIGHT);

	switch (currentColorMode) {
		case RGB: {
			currentColor.set(slider1, slider2, slider3);
			break;
		}
		case HSB: {
			currentColor.setHueAngle(slider1);
			currentColor.setSaturation(TO_HSB_VALUE(slider2));
			currentColor.setBrightness(TO_HSB_VALUE(slider3));
			break;
		}
		default: {
			break;
		}
	}

	setBorderColor(currentColor);
}

void ColorPanel::enableListeners() {
	slider1.addListener(this, &ColorPanel::handleSliderChanged);
	slider2.addListener(this, &ColorPanel::handleSliderChanged);
	slider3.addListener(this, &ColorPanel::handleSliderChanged);
}

void ColorPanel::disableListeners() {
	slider1.removeListener(this, &ColorPanel::handleSliderChanged);
	slider2.removeListener(this, &ColorPanel::handleSliderChanged);
	slider3.removeListener(this, &ColorPanel::handleSliderChanged);
}
