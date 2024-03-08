#pragma once

#include "ofxGui.h"
#include "../GuiConst.h"
#include "SceneElementExtension.h"
#include "../../Image/SceneObject.h"

class SceneElement : public ofxLabel
{
	public:
		SceneElement(std::string _labelName, SceneObject* obj_ptr);
		void setupExtension(void);
		void update(void);
		void updateElement(uint32_t newDepth);
		void draw(void);
		void addChildren(SceneElement *element);
		void removeChildren(SceneElement *element);
		virtual bool mousePressed(ofMouseEventArgs &args) override;
		virtual bool mouseReleased(ofMouseEventArgs &args) override;
		virtual bool mouseMoved(ofMouseEventArgs &args) override;
		std::vector<SceneElement*> getChildren();
		std::vector<SceneElement*> getDeepChildren();
		uint32_t getDepth();
		bool isElementAlreadyChild(SceneElement *element);
		bool isSelected(void);
		bool isDeleteRequested(void);

		SceneObject* getSceneObjectPtr(void);
		std::vector<SceneElement*> getSelectedChildren(void);

	private:
		void setupFont();
		void updateChildren();

		std::string labelName;
		std::string label;
		ofTrueTypeFont labelFont;
		std::vector<SceneElement*> children;
		uint32_t depth = 0;
		SceneElementExtension extension;
		SceneObject* object_ptr;
};

const ofColor DEFAULT_COLOR = ofColor(0, 0, 0, 0);
const ofColor SELECTED_COLOR = ofColor(0, 0, 0, 100);