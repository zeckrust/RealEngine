#include "DrawingToolsPanel.h"

DrawingToolsPanel::DrawingToolsPanel() : CustomPanel() {

}

void DrawingToolsPanel::setup(std::string panelName, float x, float y) {
	CustomPanel::setup(panelName, x, y);
	setupButtons();
}

void DrawingToolsPanel::setupButtons(void) {
	drawCircleButton.setup("Circle", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	drawEllipseButton.setup("Ellipse", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	drawLineButton.setup("Line", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	drawSquareButton.setup("Square", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	drawRectButton.setup("Rectangle", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);

	add(&drawCircleButton);
	add(&drawEllipseButton);
	add(&drawLineButton);
	add(&drawSquareButton);
	add(&drawRectButton);

	drawingButtons[0] = &drawCircleButton;
	drawingButtons[1] = &drawEllipseButton;
	drawingButtons[2] = &drawLineButton;
	drawingButtons[3] = &drawSquareButton;
	drawingButtons[4] = &drawRectButton;
}	

bool DrawingToolsPanel::mouseMoved(ofMouseEventArgs& args) {
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			collection[i]->mouseMoved(args);
		}
	}
	return true;
}

bool DrawingToolsPanel::mousePressed(ofMouseEventArgs& args) {
	CustomPanel::mousePressed(args);
	bool isPressed = false;
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			bool isButtonPressed =  collection[i]->mousePressed(args);
			if (isButtonPressed && isDrawingButton(collection[i])) {
				setSelectedDrawingTool((CustomButton*)collection[i]);
			}
			isPressed |= isButtonPressed;
		}
	}
	return isPressed;
}

bool DrawingToolsPanel::mouseReleased(ofMouseEventArgs& args) {
	bool isReleased = false;
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			isReleased |= collection[i]->mouseReleased(args);
		}
	}
	return isReleased;
}

void DrawingToolsPanel::setSelectedDrawingTool(CustomButton* button) {
	if (button != nullptr) {
		selectedDrawingTool = button;
		button->setBackground(SELECTED_BUTTON_COLOR);
		for (int i = 0; i < std::size(drawingButtons); i++) {
			if (drawingButtons[i] != nullptr && drawingButtons[i] != button) {
				drawingButtons[i]->setBackground(BUTTON_DEFAULT_COLOR);
			}
		}
	}
}

bool DrawingToolsPanel::isDrawingButton(ofxBaseGui* element) {
	for (int i = 0; i < std::size(drawingButtons); i++) {
		if (drawingButtons[i] != nullptr && drawingButtons[i] == element) {
			return true;
		}
	}
	return false;
}
