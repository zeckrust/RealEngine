#pragma once

#include "CustomPanel.h"
#include "scene/SceneElement.h"

class SceneHierarchyPanel : public CustomPanel
{
	public: 
		SceneHierarchyPanel();
		void update(void);
		void draw(void);
		void createSceneElement(std::string sceneElementName);
		void remove(ofxBaseGui *element);
		virtual bool mousePressed(ofMouseEventArgs &args) override;
		virtual bool mouseReleased(ofMouseEventArgs &args) override;
		virtual bool mouseMoved(ofMouseEventArgs &args) override;

	private:
		void add(ofxBaseGui *element) override;
		void removeElementChildren(ofxBaseGui *element);
		void handleMouseReleased(void);
		void handleDeleteRequest(void);
		void updateDisplay();

		SceneElement *pressedSceneElement = nullptr;
		SceneElement *releasedSceneElement = nullptr;
		SceneElement *deleteRequestedSceneElement = nullptr;
};