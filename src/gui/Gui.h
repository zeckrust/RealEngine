#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "TitleBar.h"
#include "panels/DrawingToolsPanel.h"
#include "panels/SceneHierarchyPanel.h"
#include "panels/PropertiesPanel.h"
#include "panels/TransformPanel.h"
#include "scene/Scene.h"
#include "scene/SceneElement.h"
#include "Histogram.h"
#include "../Image/DessinVec.h"

enum UserMode {
	DRAWING = 0,
	TRANSFORM
};

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
		int getLineWidth();
		ofColor getLineColor();
		ofColor getFillColor();
		Primitype getTypePrimitive();


		void setUserModeDrawing(void);
		void setUserModeTransform(void);
		
		ofColor getSceneBackgroundColor(void);
		ofRectangle getScene2DShape(void);
		ofRectangle getScene3DShape(void);
		UserMode getSelectedUserMode(void);
		TransformTool getSelectedTransformTool(void);

		ofRectangle getDrawingPanelShape(void);
		ofRectangle getTransformPanelShape(void);
		bool getIsImageImported(void);
		ofImage getImportedImage(void);
		void setIsImageImported(bool _isImageImported);

		void createSceneElement(std::string name, SceneObject* obj_ptr);

		// Singleton
		static Gui* getInstance();
		Gui(const Gui& obj) = delete;

	private:
		Gui();
		void setupPanels();
		void updateScenes();
		void saveScene(Scene& scene, std::string filePath);

		static Gui* instancePtr;

		TitleBar titleBar;
		SceneHierarchyPanel sceneHierarchyPanel;
		DrawingToolsPanel drawingPanel;
		TransformPanel transformPanel;
		PropertiesPanel propertiesPanel;

		Scene scene2d;
		Scene scene3d;
		Histogram histogramOrthogonal;
		Histogram histogramPerspective;

		UserMode selectedUserMode;
		bool isHistogramShowing;

		ofImage imageBuffer;
		bool isImageImported;
};

Gui* Gui::instancePtr = nullptr;
