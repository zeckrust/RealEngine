#include "Gui.h"

Gui::Gui() {}

void Gui::setup() {
	setupPanels();
}

void Gui::setupPanels() {
	rightPanel.setup(RIGHT_PANEL_NAME, 0, titleBar.getHeight());
	leftPanel.setup(LEFT_PANEL_NAME, 0, titleBar.getHeight());
}

void Gui::update() {
	rightPanel.setPosition(ofGetWidth() - rightPanel.getWidth(), rightPanel.getPosition().y);
}

void Gui::updateTitleBarWidth(int width) {
	titleBar.updateWidth(width);
}

void Gui::draw() {
	rightPanel.draw();
	leftPanel.draw();
	titleBar.draw();
}

void Gui::mouseMoved(ofMouseEventArgs& args) {
	if (!titleBar.mouseMoved(args)) {
		rightPanel.mouseMoved(args);
		leftPanel.mouseMoved(args);
	}
}

void Gui::mousePressed(ofMouseEventArgs& args) {
	if (!titleBar.mousePressed(args)) {
		rightPanel.mousePressed(args);
		leftPanel.mousePressed(args);
	}
}

void Gui::mouseReleased(ofMouseEventArgs& args) {
	if (!titleBar.mouseReleased(args)) {
		rightPanel.mouseReleased(args);
		leftPanel.mouseReleased(args);
	}
}
