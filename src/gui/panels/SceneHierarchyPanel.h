#pragma once

#include "CustomPanel.h"
#include "../scene/SceneElement.h"

class Renderer;

class SceneHierarchyPanel : public CustomPanel
{
	public: 
		SceneHierarchyPanel();
		void setup(std::string panelName, float x, float y);
		void update(void);
		void draw(void);
		void createSceneElement(std::string sceneElementName, SceneObject* obj_ptr);
		void remove(ofxBaseGui *element);
		virtual bool mousePressed(ofMouseEventArgs &args) override;
		virtual bool mouseReleased(ofMouseEventArgs &args) override;
		virtual bool mouseMoved(ofMouseEventArgs &args) override;

		vector<SceneElement*> getSelectedSceneElements(void);

	private:
		void add(ofxBaseGui *element) override;
		void removeElementChildren(ofxBaseGui *element);
		void handleMouseReleased(void);
		void handleDeleteRequest(void);
		void deleteSceneObjects(SceneElement* sceneElement);
		void updateDisplay();

		SceneElement *pressedSceneElement = nullptr;
		SceneElement *releasedSceneElement = nullptr;
		SceneElement *deleteRequestedSceneElement = nullptr;

		Renderer* renderer = nullptr;
};