#pragma once

#include "ofxGui.h"
#include "../GuiConst.h"
#include "SceneElementExtension.h"

class SceneElement : public ofxLabel
{
	public:
		SceneElement(std::string _labelName);
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
		uint32_t getDepth();
		bool isElementAlreadyChild(SceneElement *element);

	private:
		void setupFont();
		void updateChildren();

		std::string labelName;
		std::string label;
		ofTrueTypeFont labelFont;
		std::vector<SceneElement*> children;
		uint32_t depth = 0;
		SceneElementExtension extension;
};

const ofColor DEFAULT_COLOR = ofColor(0, 0, 0, 0);
const ofColor SELECTED_COLOR = ofColor(0, 0, 0, 100);