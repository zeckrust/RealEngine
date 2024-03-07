#pragma once

#include "CustomPanel.h"

class Gui; // Forward declaration

class PropertiesPanel : public CustomPanel
{
	public:
		PropertiesPanel();
		void setup(std::string panelName, float x, float y);
		void update();

	private:
		void setupFields(void);
		void updatePosition(void);

		ofxIntField posFieldX;
		ofxIntField posFieldY;
		ofxIntField posFieldZ;

		ofxFloatField rotationFieldZ;
		ofxFloatField scaleField;

		Gui* gui = nullptr;
};