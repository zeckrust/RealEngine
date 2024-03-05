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

		ofxIntSlider slider1;
		ofxIntSlider slider2;
		ofxIntSlider slider3;

		ColorMode currentColorMode;
		ofColor currentColor;

		const int BORDER_LINE_WIDTH = 3;
};