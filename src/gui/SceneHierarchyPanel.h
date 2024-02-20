#pragma once

#include "CustomPanel.h"
#include "scene/SceneElement.h"

class SceneHierarchyPanel : public CustomPanel
{
	public: 
		SceneHierarchyPanel();
		void draw();
		void add(ofxBaseGui *element) override;
		void remove(ofxBaseGui *element);
		virtual bool mousePressed(ofMouseEventArgs &args) override;
		virtual bool mouseReleased(ofMouseEventArgs &args) override;
		virtual bool mouseMoved(ofMouseEventArgs &args) override;

	private:
		void removeElementChildren(ofxBaseGui *element);
		void handleMouseReleased();
		void updateDisplay();

		SceneElement *pressedSceneElement = nullptr;
		SceneElement *releasedSceneElement = nullptr;
};