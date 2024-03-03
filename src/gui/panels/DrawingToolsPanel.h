#pragma once

#include "CustomPanel.h"
#include "../buttons/CustomButton.h"
#include "../GuiConst.h"

class DrawingToolsPanel : public CustomPanel 
{
	public:
		DrawingToolsPanel();
		void setup(std::string panelName, float x, float y);
		bool mouseMoved(ofMouseEventArgs& args);
		bool mousePressed(ofMouseEventArgs& args);
		bool mouseReleased(ofMouseEventArgs& args);

		void setSelectedDrawingTool(CustomButton* button);
		bool isDrawingButton(ofxBaseGui* element);

	private:
		void setupButtons(void);

		static const uint8_t NB_DRAWING_BUTTONS = 5;
		CustomButton* drawingButtons[NB_DRAWING_BUTTONS];

		CustomButton drawCircleButton;
		CustomButton drawEllipseButton;
		CustomButton drawLineButton;
		CustomButton drawSquareButton;
		CustomButton drawRectButton;
		
		CustomButton* selectedDrawingTool = nullptr;
};

const ofColor SELECTED_BUTTON_COLOR = ofColor(90, 90, 90, 255);
