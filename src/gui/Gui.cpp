#include "Gui.h"

Gui::Gui() {

}

Gui* Gui::getInstance() {
	if (instancePtr == nullptr) {
		instancePtr = new Gui();
		return instancePtr;
	}
	else {
		return instancePtr;
	}
}

void Gui::setup() {
	titleBar.setup();
	setupPanels();
	updateScenesSize();
}

void Gui::setupPanels() {
	sceneHierarchyPanel.setup(RIGHT_PANEL_NAME, 0, titleBar.getHeight());
	leftPanel.setup(LEFT_PANEL_NAME, 0, titleBar.getHeight());

	// Tests
	sceneHierarchyPanel.createSceneElement("element1");
	sceneHierarchyPanel.createSceneElement("element2");
	sceneHierarchyPanel.createSceneElement("element3");
}

void Gui::update() {
	sceneHierarchyPanel.update();
	leftPanel.update();
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