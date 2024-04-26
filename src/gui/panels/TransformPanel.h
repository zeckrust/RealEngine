#pragma once

#include "CustomPanel.h"
#include "../buttons/CustomButton.h"

class Gui; // Forward declaration

enum TransformTool {
	TRANSLATION = 0,
	ROTATION,
	SCALE, 

	NONE // **Do not add fields after this**
};

class TransformPanel : public CustomPanel
{
	public:
		TransformPanel();
		void setup(std::string panelName, float x, float y);
		void update();
		bool mouseMoved(ofMouseEventArgs& args);
		bool mousePressed(ofMouseEventArgs& args);
		bool mouseReleased(ofMouseEventArgs& args);

		TransformTool getSelectedTransformTool(void);

	private:
		void setupButtons(void);
		void updatePosition(void);
		void setSelectedTool(TransformTool selectedTool);

		static const uint8_t NB_TOOL_BUTTONS = 3;
		CustomButton* toolButtons[NB_TOOL_BUTTONS];

		CustomButton translationButton;
		CustomButton rotationButton;
		CustomButton scaleButton;

		TransformTool selectedTransformTool = TransformTool::NONE;
		TransformTool transformTools[3] = { TRANSLATION, ROTATION, SCALE };

		Gui* gui = nullptr;

		const ofColor SELECTED_BUTTON_COLOR = ofColor(90, 90, 90, 255);
};
