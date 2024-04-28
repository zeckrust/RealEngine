#pragma once

#include "ofxGui.h"
#include "buttons/TitleBarButton.h"
#include "GuiConst.h"

class TitleBar
{
	public:
		TitleBar();
		void setup();
		void draw();
		void updateWidth(int width);
		bool mousePressed(ofMouseEventArgs& args);
		bool mouseReleased(ofMouseEventArgs& args);
		bool mouseMoved(ofMouseEventArgs& args);
		float getHeight();

		static const size_t MAX_NB_BUTTONS = 4;
		std::array<TitleBarButton*, MAX_NB_BUTTONS> getButtons();

	private:
		void setupButtons();
		void drawBar();
		void drawButtons();

		ofRectangle rectBackground;
		ofRectangle lineLimit;

		std::array<TitleBarButton*, MAX_NB_BUTTONS> buttons;
		std::array<std::string, MAX_NB_BUTTONS> buttonNames;

		TitleBarButton fileButton;
		TitleBarButton modeButton;
		TitleBarButton showButton;
		TitleBarButton filterButton;

		CustomButton importButton;
		CustomButton exportButton;
		CustomButton transformButton;
		CustomButton drawingButton;
		CustomButton histogramButton;
		CustomButton skybox1Button;
		CustomButton skybox2Button;
		CustomButton skyboxGenButton;
		CustomButton noFilterButton;
		CustomButton grayFilterButton;
		CustomButton kelvinFilterButton;
		CustomButton nashvilleFilterButton;
		CustomButton reinhardFilterButton;
		CustomButton exposition2FilterButton;
		CustomButton exposition05FilterButton;
};
