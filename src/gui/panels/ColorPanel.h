#pragma once

#include "CustomPanel.h"

enum ColorMode {
	RGB = 0,
	HSB
};

class ColorPanel : public CustomPanel
{
	public:
		ColorPanel();
		void setup(std::string panelName, float x, float y, ofColor defaultColor);
		void update(void);
		void draw(void);

		void setColorMode(ColorMode mode);
		ofColor getColor(void);

	private:
		void setupSliders(ofColor defaultColor);
		void handleSliderChanged(int &value);

		ofxIntSlider slider1;
		ofxIntSlider slider2;
		ofxIntSlider slider3;

		ColorMode currentColorMode;
		ofColor currentColor;

		ofRectangle colorSampleRect;
		bool showColorSample = false;

		const int BORDER_LINE_WIDTH = 2;
};