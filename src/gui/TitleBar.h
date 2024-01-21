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

		static const size_t MAX_NB_BUTTONS = 3;
		std::array<CustomButton*, MAX_NB_BUTTONS> getButtons();

	private:
		ofRectangle rect;

		std::array<CustomButton*, MAX_NB_BUTTONS> buttons;
		CustomButton fileButton;
		CustomButton viewButton;
		CustomButton windowButton;
};
