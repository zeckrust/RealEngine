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
	histogramOrthogonal.setup(scene3d.getX(), scene3d.getY(), scene3d.getWidth(), scene3d.getHeight());
	histogramPerspective.setup(scene2d.getX(), scene2d.getY(), scene2d.getWidth(), scene2d.getHeight());
	isHistogramShowing = false;
}

void Gui::setupPanels() {
	sceneHierarchyPanel.setup(RIGHT_PANEL_NAME, 0, titleBar.getHeight());
	drawingPanel.setup(LEFT_PANEL_NAME, 0, titleBar.getHeight());

	// Tests
	sceneHierarchyPanel.createSceneElement("element1");
	sceneHierarchyPanel.createSceneElement("element2");
	sceneHierarchyPanel.createSceneElement("element3");
}

void Gui::update() {
	sceneHierarchyPanel.update();
	drawingPanel.update();
	updateScenesSize();
	sceneHierarchyPanel.setPosition(ofGetWidth() - sceneHierarchyPanel.getWidth(), sceneHierarchyPanel.getPosition().y);
	histogramOrthogonal.update(scene3d.getX(), scene3d.getY(), scene3d.getWidth(), scene3d.getHeight());
	histogramPerspective.update(scene2d.getX(), scene2d.getY(), scene2d.getWidth(), scene2d.getHeight());
}

void Gui::updateScenesSize() {
	float scenesPosX = drawingPanel.getPosition().x + drawingPanel.getWidth() + SCENE_PADDING;
	float scenesWidth = ofGetWidth() - sceneHierarchyPanel.getWidth() - drawingPanel.getWidth() - (2*SCENE_PADDING);
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
	drawingPanel.draw();
	titleBar.draw();
	if (isHistogramShowing) {
		histogramOrthogonal.draw();
		histogramPerspective.draw();
	}
}

void Gui::mouseMoved(ofMouseEventArgs& args) {
	if (!titleBar.mouseMoved(args)) {
		sceneHierarchyPanel.mouseMoved(args);
		drawingPanel.mouseMoved(args);
	}
}

void Gui::mousePressed(ofMouseEventArgs& args) {
	if (!titleBar.mousePressed(args)) {
		sceneHierarchyPanel.mousePressed(args);
		drawingPanel.mousePressed(args);
	}
}

void Gui::mouseReleased(ofMouseEventArgs& args) {
	if (!titleBar.mouseReleased(args)) {
		sceneHierarchyPanel.mouseReleased(args);
		drawingPanel.mouseReleased(args);
	}
}

void Gui::windowResized(int width, int height) {
	titleBar.updateWidth(ofGetScreenWidth());
}

void Gui::saveScenes() {
	ofFileDialogResult result = ofSystemLoadDialog("Where to save 2d and 3d scenes", true, "");
	saveScene(scene2d, result.getPath() + "\\scene2d.png");
	saveScene(scene2d, result.getPath() + "\\scene3d.png");
}

void Gui::saveScene(Scene & scene, std::string filePath) {
	ofImage imageScene;
	ofLog() << filePath;
	imageScene.grabScreen(scene.getX(), scene.getY(), scene.getWidth(), scene.getHeight());
	imageScene.save(filePath);
}

void Gui::importFile() {
	ofLog() << "## NOT IMPLEMENTED ##";
}

void Gui::showHistogram() {
	// ofLog() << "## NOT IMPLEMENTED ##";
	isHistogramShowing = !isHistogramShowing;
}