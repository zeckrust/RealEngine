#pragma once

#include "ofxGui.h"
#include "CustomButton.h"
#include "GuiConst.h"

class TitleBar
{
	public:
		TitleBar();
		void setup();
		void setupButtons();
		void setupButtonsPosition();
		void draw();
		void drawBar();
		void drawButtons();
		void update(int width);

	private:
		ofRectangle rect;

		CustomButton* buttons[3];
		CustomButton fileButton;
		CustomButton viewButton;
		CustomButton windowButton;
};
