#pragma once

#include "ofxGui.h"
#include "../GuiConst.h"

class SceneElement : public ofxLabel
{
	public:
		SceneElement(std::string _labelName);
		void update(uint32_t newDepth);
		void addChildren(SceneElement *element);
		void removeChildren(SceneElement *element);
		virtual bool mousePressed(ofMouseEventArgs &args) override;
		virtual bool mouseReleased(ofMouseEventArgs &args) override;
		std::vector<SceneElement*> getChildren();
		uint32_t getDepth();

	private:
		void setupFont();
		void updateChildren();

		std::string labelName;
		std::string label;
		ofTrueTypeFont labelFont;
		std::vector<SceneElement*> children;
		uint32_t depth = 0;
};