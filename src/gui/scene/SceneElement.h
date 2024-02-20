#pragma once

#include "ofxGui.h"
#include "../GuiConst.h"
#include "SceneElementExtension.h"

class SceneElement : public ofxLabel
{
	public:
		SceneElement(std::string _labelName);
		void setupExtension(void);
		void update(uint32_t newDepth);
		void drawExtension(void);
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