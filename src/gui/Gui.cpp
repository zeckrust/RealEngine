#include "Gui.h"

Gui::Gui() {}

void Gui::setup() {
	setupPanels();
	updateScenesSize();
}

void Gui::setupPanels() {
	sceneHierarchyPanel.setup(RIGHT_PANEL_NAME, 0, titleBar.getHeight());
	leftPanel.setup(LEFT_PANEL_NAME, 0, titleBar.getHeight());

	element12.addChildren(&element121);
	element1.addChildren(&element11);
	element1.addChildren(&element12);

	sceneHierarchyPanel.add(&element1);
	sceneHierarchyPanel.add(&element2);
}

void Gui::update() {
	updateScenesSize();
	sceneHierarchyPanel.setPosition(ofGetWidth() - sceneHierarchyPanel.getWidth(), sceneHierarchyPanel.getPosition().y);
}

void Gui::updateScenesSize() {
	float scenesPosX = leftPanel.getPosition().x + leftPanel.getWidth() + SCENE_PADDING;
	float scenesWidth = ofGetWidth() - sceneHierarchyPanel.getWidth() - leftPanel.getWidth() - (2*SCENE_PADDING);
	float scenesHeight = (ofGetHeight() - TITLE_BAR_HEIGHT - TITLE_BAR_LINE_LIMIT_HEIGHT - (3*SCENE_PADDING)) / 2;

	float scene2dPosY = TITLE_BAR_HEIGHT + TITLE_BAR_LINE_LIMIT_HEIGHT + SCENE_PADDING;
	float scene3dPosY = scene2dPosY + scenesHeight + SCENE_PADDING;

	scene2d.setup(scenesPosX, scene2dPosY, scenesWidth, scenesHeight);
	scene3d.setup(scenesPosX, scene3dPosY, scenesWidth, scenesHeight);
}

void Gui::draw() {
	scene2d.draw();
	scene3d.draw();
	sceneHierarchyPanel.draw();
	leftPanel.draw();
	titleBar.draw();
}

void Gui::mouseMoved(ofMouseEventArgs& args) {
	if (!titleBar.mouseMoved(args)) {
		sceneHierarchyPanel.mouseMoved(args);
		leftPanel.mouseMoved(args);
	}
}

void Gui::mousePressed(ofMouseEventArgs& args) {
	if (!titleBar.mousePressed(args)) {
		sceneHierarchyPanel.mousePressed(args);
		leftPanel.mousePressed(args);
	}
}

void Gui::mouseReleased(ofMouseEventArgs& args) {
	if (!titleBar.mouseReleased(args)) {
		sceneHierarchyPanel.mouseReleased(args);
		leftPanel.mouseReleased(args);
	}
}

void Gui::windowResized(int width, int height) {
	titleBar.updateWidth(ofGetScreenWidth());
}

Scene Gui::getScene2d() {
	return scene2d;
}

Scene Gui::getScene3d() {
	return scene3d;
}