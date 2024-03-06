#include "PropertiesPanel.h"
#include "../Gui.h"

PropertiesPanel::PropertiesPanel() : CustomPanel() {

}

void PropertiesPanel::setup(std::string panelName, float x, float y) {
	CustomPanel::setup(panelName, x, y);
	gui = Gui::getInstance();

	setupFields();

	add(&posFieldX);
	add(&posFieldY);
	add(&posFieldZ);
	add(&rotationFieldZ);
	add(&scaleField);
}

void PropertiesPanel::setupFields(void) {
	posFieldX.setup("X :", 0);
	posFieldY.setup("Y :", 0);
	posFieldZ.setup("Z :", 0);

	rotationFieldZ.setup("Rotation Z :", 0);
	rotationFieldZ.setMax(360);
	rotationFieldZ.setMin(0);

	scaleField.setup("Scale :", 1);
	scaleField.setMin(1);

}

void PropertiesPanel::update(void) {
	CustomPanel::update();
	updatePosition();
}

void PropertiesPanel::updatePosition(void) {
	ofRectangle drawingPanel = gui->getDrawingPanelShape();
	float posX = drawingPanel.getPosition().x;
	float posY = drawingPanel.getPosition().y + drawingPanel.getHeight() + CUSTOM_PANEL_PADDING;
	setPosition(posX, posY);
}