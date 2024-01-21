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

		void draw();
		void drawBar();
		void drawButtons();
		void updateWidth(int width);

		static const size_t MAX_NB_BUTTONS = 3;
		std::array<CustomButton*, MAX_NB_BUTTONS> getButtons();

	private:
		ofRectangle rect;

		std::array<CustomButton*, MAX_NB_BUTTONS> buttons;
		std::array<std::string, MAX_NB_BUTTONS> buttonNames;

		CustomButton fileButton;
		CustomButton viewButton;
		CustomButton windowButton;
};
