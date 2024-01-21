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
		void updateWidth(int width);
		void mousePressed(int x, int y, int button);

		static const size_t MAX_NB_BUTTONS = 3;
		std::array<CustomButton*, MAX_NB_BUTTONS> getButtons();

	private:
		void drawBar();
		void drawButtons();

		ofRectangle rect;

		std::array<CustomButton*, MAX_NB_BUTTONS> buttons;
		std::array<std::string, MAX_NB_BUTTONS> buttonNames;

		CustomButton fileButton;
		CustomButton viewButton;
		CustomButton windowButton;
};
