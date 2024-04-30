#pragma once

#include "ColorPanel.h"
#include "../buttons/CustomButton.h"
#include "../GuiConst.h"
#include "../apps/RealEngine/src/Image/DessinVec.h"
#include "../apps/RealEngine/src/Image/DessinGeo.h"

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

		int getLineWidth(void);
		ofColor getLineColor(void);
		ofColor getFillColor(void);
		ofColor getSceneBackgroundColor(void);
		Primitype getDrawMode(void);
		Geotype getGeometricType(void);
		bool getBezierMode(void);
		bool getPlaneMode(void);

	private:
		void setupButtons(void);
		void setupFields(void);
		void setupColorPanels(void);

		static const uint8_t NB_DRAWING_BUTTONS = 11;
		CustomButton* drawingButtons[NB_DRAWING_BUTTONS];

		CustomButton* selectedDrawingTool = nullptr;
		CustomButton drawCircleButton;
		CustomButton drawEllipseButton;
		CustomButton drawLineButton;
		CustomButton drawSquareButton;
		CustomButton drawRectButton;
		CustomButton drawStage1Button;
		CustomButton drawStage2Button;
		CustomButton drawCylinderButton;
		CustomButton drawPrismButton;
		CustomButton drawBezierButton;
		CustomButton drawPlaneButton;
		
		ofxInputField<int> lineWidthField;
		ColorPanel lineColorPanel;
		ColorPanel fillColorPanel;
		ColorPanel backgroundColorPanel;
		Primitype typePrimitive;
		Geotype typeGeo;
		bool bezierMode;
		bool planeMode;

		const ofColor SELECTED_BUTTON_COLOR = ofColor(90, 90, 90, 255);
};
