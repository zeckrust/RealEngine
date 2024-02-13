#pragma once

#include "GuiConst.h"
#include "ofxGui.h"

class CustomPanel : public ofxGuiGroup
{
	public:
		CustomPanel();
		void setup(std::string panelName, float x, float y);
		void update();
		virtual void add(ofxBaseGui *element);

	private:
		void updateWidth();
};

