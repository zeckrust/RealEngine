#pragma once

#include "ofxGui.h"
#include "GuiConst.h"
#include <chrono>

class CustomButton : public ofxLabel
{
	public:
		CustomButton();
		void setupLabel(std::string label);
		void setupHitBox(int x, int y);
		bool mousePressed(ofMouseEventArgs& args) override;
		void draw();

	private:
		ofRectangle hitBox;
		bool isPressed;
		std::chrono::steady_clock::time_point pressedTimeStart;
};
