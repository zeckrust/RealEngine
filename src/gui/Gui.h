#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "TitleBar.h"
#include "CustomPanel.h"

class Gui
{
	public:
		Gui();
		void setup();
		void update();
		void updateTitleBarWidth(int width);
		void draw();

		void mouseMoved(ofMouseEventArgs& args);
		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);

	private:
		void setupPanels();

		TitleBar titleBar;
		CustomPanel rightPanel;
		CustomPanel leftPanel;
};

