#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "TitleBar.h"
#include "CustomPanel.h"
#include "Scene.h"

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

		Scene getScene2d();
		Scene getScene3d();

	private:
		void setupPanels();
		void setupScenes();

		TitleBar titleBar;
		CustomPanel rightPanel;
		CustomPanel leftPanel;
		Scene scene2d;
		Scene scene3d;
};

