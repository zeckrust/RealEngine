#pragma once

#include "ofxGui.h"
#include "GuiConst.h"
#include <chrono>

class CustomButton : public ofxLabel
{
	public:
		CustomButton();
		void setupButton(std::string label, int x, int y);
		void draw();
		bool mousePressed(ofMouseEventArgs& args) override;
		void handlePressedState();

	private:
		void setupLabel(std::string label);
		void setupHitBox(int x, int y);

		ofRectangle hitBox;
		bool isPressed;
		std::chrono::steady_clock::time_point pressedTimeStart;
};
