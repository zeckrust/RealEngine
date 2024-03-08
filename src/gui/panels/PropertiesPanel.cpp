#include "PropertiesPanel.h"
#include "../Gui.h"

PropertiesPanel::PropertiesPanel() : CustomPanel() {

}

void PropertiesPanel::setup(std::string panelName, float x, float y) {
	CustomPanel::setup(panelName, x, y);
	gui = Gui::getInstance();

	setupButtons();

	add(&x_axis_button);
	add(&y_axis_button);
	add(&z_axis_button);

	btn_states[0] = true;
	btn_states[1] = false;
	btn_states[2] = false;

	x_axis_button.setBackground(SELECTED_BUTTON_COLOR);
}

void PropertiesPanel::setupButtons(void) {
	x_axis_button.setup("X", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	y_axis_button.setup("Y", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	z_axis_button.setup("Z", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
}

void PropertiesPanel::update(void) {
	CustomPanel::update();
	updatePosition();
}

void PropertiesPanel::updatePosition(void) {
	ofRectangle transformPanel = gui->getTransformPanelShape();
	float posX = transformPanel.getPosition().x;
	float posY = transformPanel.getPosition().y + transformPanel.getHeight() + CUSTOM_PANEL_PADDING;
	setPosition(posX, posY);
}

bool PropertiesPanel::mouseMoved(ofMouseEventArgs& args) {
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			collection[i]->mouseMoved(args);
		}
	}
	return true;
}

bool PropertiesPanel::mousePressed(ofMouseEventArgs& args) {
	bool isPressed = CustomPanel::mousePressed(args);

	if (!isMinimized()) {
		for (int i = 0; i < std::size(collection); i++) {
			if (collection[i] != nullptr && collection[i]->getShape().inside(args.x, args.y)) {
				CustomButton* button = (CustomButton*)collection[i];
				if (btn_states[i]) {
					button->setBackground(BUTTON_DEFAULT_COLOR);
				}
				else {
					button->setBackground(SELECTED_BUTTON_COLOR);
				}
				btn_states[i] = !btn_states[i];
			}
		}
	}
	return isPressed;

}

bool PropertiesPanel::mouseReleased(ofMouseEventArgs& args) {
	bool isReleased = false;
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			isReleased |= collection[i]->mouseReleased(args);
		}
	}
	return isReleased;
}

bool* PropertiesPanel::getBtnStates(void) {
	return btn_states;
}