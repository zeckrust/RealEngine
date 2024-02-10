#pragma once

#include "CustomPanel.h"
#include "scene/SceneElement.h"

class SceneHierarchyPanel : public CustomPanel
{
	public: 
		SceneHierarchyPanel();
		void add(ofxBaseGui *element) override;
		void remove(ofxBaseGui *element);
		virtual bool mousePressed(ofMouseEventArgs &args) override;
		virtual bool mouseReleased(ofMouseEventArgs &args) override;

	private:
		void updateDisplay();
		void removeElementChildren(ofxBaseGui *element);

		SceneElement *pressedSceneElement = nullptr;
		SceneElement *releasedSceneElement = nullptr;
};