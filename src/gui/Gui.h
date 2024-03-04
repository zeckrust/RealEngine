#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "TitleBar.h"
#include "panels/DrawingToolsPanel.h"
#include "panels/SceneHierarchyPanel.h"
#include "scene/Scene.h"
#include "scene/SceneElement.h"
#include "Histogram.h"

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
		void saveScenes();
		void importFile();
		void showHistogram();
		
		// Singleton
		static Gui* getInstance();
		Gui(const Gui& obj) = delete;

	private:
		Gui();
		void setupPanels();
		void updateScenesSize();
		void saveScene(Scene& scene, std::string filePath);

		static Gui* instancePtr;

		TitleBar titleBar;
		SceneHierarchyPanel sceneHierarchyPanel;
		DrawingToolsPanel drawingPanel;
		Scene scene2d;
		Scene scene3d;
		Histogram histogramOrthogonal;
		Histogram histogramPerspective;

		bool isHistogramShowing;
};

Gui* Gui::instancePtr = nullptr;
