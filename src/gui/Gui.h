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
		SceneHierarchyPanel sceneHierarchyPanel;
		CustomPanel leftPanel;
		Scene scene2d;
		Scene scene3d;

		// Scene Elements tests
		SceneElement element1 = SceneElement("element1");
		SceneElement element11 = SceneElement("element11");
		SceneElement element12 = SceneElement("element12");
		SceneElement element121 = SceneElement("element121");
		SceneElement element2 = SceneElement("element2");
};

