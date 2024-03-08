#pragma once

#include "CustomPanel.h"
#include "../buttons/CustomButton.h"

class Gui; // Forward declaration

class PropertiesPanel : public CustomPanel
{
	public:
		PropertiesPanel();
		void setup(std::string panelName, float x, float y);
		void update();
		bool mouseMoved(ofMouseEventArgs& args);
		bool mousePressed(ofMouseEventArgs& args);
		bool mouseReleased(ofMouseEventArgs& args);
		bool* getBtnStates(void);
	private:
		void setupButtons(void);
		void updatePosition(void);

		CustomButton x_axis_button;
		CustomButton y_axis_button;
		CustomButton z_axis_button;

		bool btn_states[3];

		Gui* gui = nullptr;

		const ofColor SELECTED_BUTTON_COLOR = ofColor(90, 90, 90, 255);
};