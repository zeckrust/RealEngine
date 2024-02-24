#pragma once

#include "ofMain.h"
#include "../buttons/CustomButton.h"


class SceneElementExtension {
	public:
		SceneElementExtension();
		void setup(void);
		void draw(void);
		void show(void);
		void hide(void);
		bool mousePressed(ofMouseEventArgs& args);
		bool mouseReleased(ofMouseEventArgs& args);
		bool mouseMoved(ofMouseEventArgs& args);
		bool isSelected(void);
		bool isDeleteRequested(void);

	private:
		void updatePosition(float x, float y);
		void handleSelectPressed(void);
		void handleDeletePressed(void);

		bool isDisplayed = false;
		bool isElementSelected = false;
		bool isDeleteNeeded = false;

		ofRectangle extensionRect;
		CustomButton selectButton;
		CustomButton deleteButton;
};

const std::string SELECT_STR = "Select";
const std::string DESELECT_STR = "Deselect";
const std::string DELETE_STR = "Delete";
const int DEFAULT_BUTTON_HEIGHT = 30;
const int DEFAULT_EXTENSION_WIDTH = 80;
const ofColor EXTENSION_COLOR = ofColor(100, 100, 100, 255);