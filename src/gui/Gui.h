#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "TitleBar.h"
#include "CustomPanel.h"
#include "SceneHierarchyPanel.h"
#include "scene/Scene.h"
#include "scene/SceneElement.h"

class Gui
{
	public:
		void setup();
		void update();
		void draw();

		void mouseMoved(ofMouseEventArgs& args);
		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);
		void windowResized(int width, int height);

		Scene getScene2d();
		Scene getScene3d();
		
		// Singleton
		static Gui* getInstance();
		Gui(const Gui& obj) = delete;

	private:
		Gui();
		void setupPanels();
		void updateScenesSize();

		static Gui* instancePtr;

		TitleBar titleBar;
		SceneHierarchyPanel sceneHierarchyPanel;
		CustomPanel leftPanel;
		Scene scene2d;
		Scene scene3d;
};

Gui* Gui::instancePtr = nullptr;
