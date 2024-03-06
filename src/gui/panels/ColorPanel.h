#pragma once

#include "CustomPanel.h"
#include "../buttons/CustomButton.h"

#define TO_SLIDER_VALUE(valueHSB) (int)ceil(valueHSB / 256. * 100.)
#define TO_HSB_VALUE(valueSlider) (float)valueSlider * 256. / 100.

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
		bool mousePressed(ofMouseEventArgs& args);

		void changeColorMode(void);
		ofColor getColor(void);

	private:
		void setupSliders(ofColor defaultColor);
		void setupButton(void);
		void handleSliderChanged(int &value);

		void enableListeners(void);
		void disableListeners(void);

		ofxIntSlider slider1;
		ofxIntSlider slider2;
		ofxIntSlider slider3;

		CustomButton colorModeButton;
		ColorMode currentColorMode = RGB;
		ofColor currentColor;

		ofRectangle colorSampleRect;
		bool showColorSample = false;

		const int BORDER_LINE_WIDTH = 2;
		const std::string RGB_STR = "\tRGB";
		const std::string HSB_STR = "\tHSB";

		const std::string R_STR = "\tR";
		const std::string G_STR = "\tG";
		const std::string B_STR = "\tB";

		const std::string H_STR = "\tH";
		const std::string S_STR = "\tS";
};