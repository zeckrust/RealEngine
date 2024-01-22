#pragma once

#include "ofxGui.h"
#include "GuiConst.h"
#include "CustomButton.h"

class TitleBarButton : public CustomButton
{
	public:
		TitleBarButton();
		void draw();
		bool mousePressed(ofMouseEventArgs& args) override;
		float getExtensionWidth();
		float getExtensionHeight();

		void setSubButtons(std::vector<CustomButton*> buttons);
		void addSubButton(CustomButton* button);

	private:
		void drawSubButtons();
		void handleShowExtension();
		bool isMouseInExtension(float x, float y, float width, float height);

		void update();
		void updateExtensionWidth();
		void updateExtensionHeight();
		void updateSubButtons();

		ofRectangle rectExtension;
		std::vector<CustomButton*> subButtons;
		bool showExtension;
		float extensionWidth;
		float extensionHeight;
};
