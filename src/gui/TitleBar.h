#pragma once

#include "ofxGui.h"
#include "buttons/TitleBarButton.h"
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
		void mouseReleased(int x, int y, int button);
		void mouseMoved(int x, int y);

		static const size_t MAX_NB_BUTTONS = 3;
		std::array<TitleBarButton*, MAX_NB_BUTTONS> getButtons();

	private:
		void drawBar();
		void drawButtons();

		ofRectangle rect;
		ofRectangle lineLimit;

		std::array<TitleBarButton*, MAX_NB_BUTTONS> buttons;
		std::array<std::string, MAX_NB_BUTTONS> buttonNames;

		TitleBarButton fileButton;
		TitleBarButton viewButton;
		TitleBarButton windowButton;

		// Only for test purposes
		CustomButton testButton1;
		CustomButton testButton2;
		CustomButton testButton3;
};
