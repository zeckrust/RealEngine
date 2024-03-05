#pragma once

#include "ColorPanel.h"
#include "../buttons/CustomButton.h"
#include "../GuiConst.h"

class DrawingToolsPanel : public CustomPanel 
{
	public:
		DrawingToolsPanel();
		void setup(std::string panelName, float x, float y);
		void update(void);
		void draw(void);
		bool mouseMoved(ofMouseEventArgs& args);
		bool mousePressed(ofMouseEventArgs& args);
		bool mouseReleased(ofMouseEventArgs& args);

		void setSelectedDrawingTool(CustomButton* button);
		bool isDrawingButton(ofxBaseGui* element);

	private:
		void setupButtons(void);
		void setupFields(void);
		void setupColorPanels(void);

		static const uint8_t NB_DRAWING_BUTTONS = 5;
		CustomButton* drawingButtons[NB_DRAWING_BUTTONS];

		CustomButton* selectedDrawingTool = nullptr;
		CustomButton drawCircleButton;
		CustomButton drawEllipseButton;
		CustomButton drawLineButton;
		CustomButton drawSquareButton;
		CustomButton drawRectButton;
		
		ofxInputField<int> lineWidthField;
		ColorPanel lineColorPanel;
		ColorPanel fillColorPanel;
		ColorPanel backgroundColorPanel;
};

const ofColor SELECTED_BUTTON_COLOR = ofColor(90, 90, 90, 255);
