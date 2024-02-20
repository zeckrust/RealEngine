#include "CustomPanel.h"

CustomPanel::CustomPanel() : ofxGuiGroup() {

}

void CustomPanel::setup(std::string panelName, float x, float y) {
	ofxGuiGroup::setup(panelName, FILE_NAME_SETTINGS, x, y);
	unregisterMouseEvents();
	setDefaultWidth(CUSTOM_PANEL_DEFAULT_WIDTH);
}

void CustomPanel::add(ofxBaseGui *element) {
	collection.push_back(element);
}

void CustomPanel::update() {
	updateWidth();
}

void CustomPanel::updateWidth() {
	float width = 0;
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr && collection[i]->getWidth() > width) {
			width = collection[i]->getWidth();
		}
	}
	if (width > CUSTOM_PANEL_DEFAULT_WIDTH) {
		setWidthElements(width);
	}
	else {
		setWidthElements(CUSTOM_PANEL_DEFAULT_WIDTH);
	}
}
