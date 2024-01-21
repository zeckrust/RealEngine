#pragma once

#include "ofxGui.h"
#include "GuiConst.h"

class CustomButton : public ofxLabel
{
	public:
		CustomButton();
		void setupLabel(std::string label);
		void setupHitBox(int x, int y);
		bool mousePressed(ofMouseEventArgs& args) override;

	private:
		ofRectangle hitBox;
};
