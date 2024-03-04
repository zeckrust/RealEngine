#pragma once

#include "ofxGui.h"
#include "../GuiConst.h"

class Gui; // Forward declaration

class CustomButton : public ofxLabel
{
	public:
		CustomButton();
		void setup(std::string label, std::string font, int x, int y, int height);
		bool mousePressed(ofMouseEventArgs& args) override;
		bool mouseReleased(ofMouseEventArgs& args) override;
		bool mouseMoved(ofMouseEventArgs& args) override;
		void setWidth(float width);
		void setPressedFunction(void (Gui::*_pressedFunction)());
		float getWidth() const;
		void setBackground(ofColor color);

	private:
		void setupLabel(std::string label);
		void setupFont(std::string label, std::string font);

		Gui* gui;

		bool isPressed;
		float labelWidth;
		void (Gui::*pressedFunction)();
		ofTrueTypeFont labelFont;
		std::string labelStr;
		ofColor backgroundColor;
};
