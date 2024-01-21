#pragma once

#include "ofxGui.h"
#include "GuiConst.h"
#include <chrono>

class CustomButton : public ofxLabel
{
	public:
		CustomButton();
		void setupButton(std::string label, std::string font, int x, int y);

		void draw();
		bool mousePressed(ofMouseEventArgs& args) override;
		void handlePressedState();
		float getWidth() const;

	private:
		void setupLabel(std::string label);
		void setupFont(std::string label, std::string font);
		void setupHitBox(int x, int y);

		ofRectangle hitBox;
		bool isPressed;
		ofTrueTypeFont labelFont;
		std::string labelStr;
		float labelWidth;
		std::chrono::steady_clock::time_point pressedTimeStart;
};
