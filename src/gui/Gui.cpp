#include "Gui.h"

Gui::Gui() {}

void Gui::setup() {
	setupPanels();
	setupScenes();
}

void Gui::setupPanels() {
	rightPanel.setup(RIGHT_PANEL_NAME, 0, titleBar.getHeight());
	leftPanel.setup(LEFT_PANEL_NAME, 0, titleBar.getHeight());
}

void Gui::setupScenes() {
	float scenesPosX = leftPanel.getPosition().x + leftPanel.getWidth() + SCENE_PADDING;
	float scenesWidth = ofGetWidth() - rightPanel.getWidth() - leftPanel.getWidth() - (2*SCENE_PADDING);
	float scenesHeight = (ofGetHeight() - TITLE_BAR_HEIGHT - TITLE_BAR_LINE_LIMIT_HEIGHT - (3*SCENE_PADDING)) / 2;

	float scene2dPosY = TITLE_BAR_HEIGHT + TITLE_BAR_LINE_LIMIT_HEIGHT + SCENE_PADDING;
	float scene3dPosY = scene2dPosY + scenesHeight + SCENE_PADDING;

	scene2d.setup(scenesPosX, scene2dPosY, scenesWidth, scenesHeight);
	scene3d.setup(scenesPosX, scene3dPosY, scenesWidth, scenesHeight);
}

void Gui::update() {
	rightPanel.setPosition(ofGetWidth() - rightPanel.getWidth(), rightPanel.getPosition().y);
}

void Gui::updateTitleBarWidth(int width) {
	titleBar.updateWidth(width);
}

void Gui::draw() {
	scene2d.draw();
	scene3d.draw();
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

Scene Gui::getScene2d() {
	return scene2d;
}

Scene Gui::getScene3d() {
	return scene3d;
}