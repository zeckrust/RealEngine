#pragma once

#include "ofxGui.h"
#include "CustomButton.h"

class TitleBarButton : public CustomButton
{
	public:
		TitleBarButton();
		void draw();
		bool mousePressed(ofMouseEventArgs& args) override;
		bool mouseMoved(ofMouseEventArgs& args) override;
		float getExtensionWidth();
		float getExtensionHeight();

		void setSubButtons(std::vector<CustomButton*> buttons);
		void addSubButton(CustomButton* button);

	private:
		void drawSubButtons();
		void drawExtension();
		void handleDrawExtension();
		bool isMouseInExtension();
		bool isInCloseThreshold();

		void update();
		void updateExtensionWidth();
		void updateExtensionHeight();
		void updateSubButtons();

		bool showExtension;
		float extensionWidth;
		float extensionHeight;
		ofRectangle rectExtension;
		std::vector<CustomButton*> subButtons;
		std::chrono::steady_clock::time_point closeExtensionTimeStart;
};
