#include "TransformPanel.h"
#include "../Gui.h"

TransformPanel::TransformPanel() : CustomPanel() {
	toolButtons[0] = &translationButton;
	toolButtons[1] = &rotationButton;
	toolButtons[2] = &scaleButton;
}

void TransformPanel::setup(std::string panelName, float x, float y) {
	CustomPanel::setup(panelName, x, y);
	gui = Gui::getInstance();

	setupButtons();

	add(&translationButton);
	add(&rotationButton);
	add(&scaleButton);
}

void TransformPanel::setupButtons(void) {
	translationButton.setup("Translate", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	rotationButton.setup("Rotate", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	scaleButton.setup("Scale", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
}

void TransformPanel::update(void) {
	CustomPanel::update();
	updatePosition();
}

void TransformPanel::updatePosition(void) {
	ofRectangle drawingPanel = gui->getDrawingPanelShape();
	float posX = drawingPanel.getPosition().x;
	float posY = drawingPanel.getPosition().y + drawingPanel.getHeight() + CUSTOM_PANEL_PADDING;
	setPosition(posX, posY);
}

bool TransformPanel::mouseMoved(ofMouseEventArgs& args) {
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			collection[i]->mouseMoved(args);
		}
	}
	return true;
}

bool TransformPanel::mousePressed(ofMouseEventArgs& args) {
	bool isPressed = CustomPanel::mousePressed(args);

	if (!isMinimized()) {
		for (int i = 0; i < std::size(collection); i++) {
			if (collection[i] != nullptr && collection[i]->getShape().inside(args.x, args.y)) {
				setSelectedTool(transformTools[i]);
			}
		}
	}
	return isPressed;

}

bool TransformPanel::mouseReleased(ofMouseEventArgs& args) {
	bool isReleased = false;
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			isReleased |= collection[i]->mouseReleased(args);
		}
	}
	return isReleased;
}

void TransformPanel::setSelectedTool(TransformTool selectedTool) {
	selectedTransformTool = selectedTool;
	for (int i = 0; i < std::size(toolButtons); i++) {
		if (toolButtons[i] != nullptr) {
			if (toolButtons[i] != nullptr && transformTools[i] == selectedTool) {
				toolButtons[i]->setBackground(SELECTED_BUTTON_COLOR);
			}
			else {
				toolButtons[i]->setBackground(BUTTON_DEFAULT_COLOR);
			}
		}
	}
}

TransformTool TransformPanel::getSelectedTransformTool(void) {
	return selectedTransformTool;
}
