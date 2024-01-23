#pragma once

#include "ofxGui.h"
#include "../GuiConst.h"

class CustomButton : public ofxLabel
{
	public:
		CustomButton();
		void setup(std::string label, std::string font, int x, int y, int height);
		bool mousePressed(ofMouseEventArgs& args) override;
		bool mouseReleased(ofMouseEventArgs& args) override;
		bool mouseMoved(ofMouseEventArgs& args) override;
		void setWidth(float width);
		void setPressedFunction(void (*_pressedFunction)());
		float getWidth() const;

	private:
		void setupLabel(std::string label);
		void setupFont(std::string label, std::string font);

		bool isPressed;
		float labelWidth;
		void (*pressedFunction)();
		ofTrueTypeFont labelFont;
		std::string labelStr;
};
