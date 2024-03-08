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
	updateScenes();
	selectedUserMode = DRAWING;
	isHistogramShowing = false;
	isImageImported = false;
}

void Gui::setupPanels() {
	sceneHierarchyPanel.setup("Scene Elements", 0, titleBar.getHeight());
	drawingPanel.setup("Drawing", 0, titleBar.getHeight());
	transformPanel.setup("Transform", 0, 0); // Dynamically positioned in update()
	propertiesPanel.setup("Axis", 0, 0); // Dynamically positioned in update()
	drawingPanel.minimize();
	transformPanel.minimize();
	propertiesPanel.minimize();
}

void Gui::update() {
	sceneHierarchyPanel.update();
	drawingPanel.update();
	transformPanel.update();
	propertiesPanel.update();

	updateScenes();
	sceneHierarchyPanel.setPosition(ofGetWidth() - sceneHierarchyPanel.getWidth(), sceneHierarchyPanel.getPosition().y);
}

void Gui::updateScenes() {
	float scenesPosX = drawingPanel.getPosition().x + drawingPanel.getWidth() + SCENE_PADDING;
	float scenesWidth = ofGetWidth() - sceneHierarchyPanel.getWidth() - drawingPanel.getWidth() - (2*SCENE_PADDING);
	float scenesHeight = (ofGetHeight() - TITLE_BAR_HEIGHT - TITLE_BAR_LINE_LIMIT_HEIGHT - (3*SCENE_PADDING)) / 2;

	float scene2dPosY = TITLE_BAR_HEIGHT + TITLE_BAR_LINE_LIMIT_HEIGHT + SCENE_PADDING;
	float scene3dPosY = scene2dPosY + scenesHeight + SCENE_PADDING;

	scene2d.setup(scenesPosX, scene2dPosY, scenesWidth, scenesHeight);
	scene3d.setup(scenesPosX, scene3dPosY, scenesWidth, scenesHeight);

	scene2d.update();
	scene3d.update();
}

void Gui::draw() {
	scene2d.draw();
	scene3d.draw();
	sceneHierarchyPanel.draw();
	drawingPanel.draw();
	transformPanel.draw();
	propertiesPanel.draw();
	titleBar.draw();
}

void Gui::mouseMoved(ofMouseEventArgs& args) {
	if (!titleBar.mouseMoved(args)) {
		sceneHierarchyPanel.mouseMoved(args);
		drawingPanel.mouseMoved(args);
		transformPanel.mouseMoved(args);
		propertiesPanel.mouseMoved(args);
	}
}

void Gui::mousePressed(ofMouseEventArgs& args) {
	if (!titleBar.mousePressed(args)) {
		sceneHierarchyPanel.mousePressed(args);
		drawingPanel.mousePressed(args);
		transformPanel.mousePressed(args);
		propertiesPanel.mousePressed(args);
	}
}

void Gui::mouseReleased(ofMouseEventArgs& args) {
	std::vector<CustomButton*> showSubButtons{  };
	if (!titleBar.mouseReleased(args)) {
		sceneHierarchyPanel.mouseReleased(args);
		drawingPanel.mouseReleased(args);
		transformPanel.mouseReleased(args);
		propertiesPanel.mouseReleased(args);
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
	imageScene.grabScreen(scene.getX(), scene.getY(), scene.getWidth(), scene.getHeight());
	imageScene.save(filePath);
}

void Gui::importFile() {
	ofFileDialogResult result = ofSystemLoadDialog("What file do you want to import", false, "");
	imageBuffer.load(result.getPath());
	isImageImported = true;
}

void Gui::showHistogram() {
	isHistogramShowing = !isHistogramShowing;
}

void Gui::createSceneElement(std::string name, SceneObject* obj_ptr) {
	sceneHierarchyPanel.createSceneElement(name, obj_ptr);
}

void Gui::setUserModeDrawing(void) {
	selectedUserMode = DRAWING;
}

void Gui::setUserModeTransform(void) {
	selectedUserMode = TRANSFORM;
}

ofColor Gui::getSceneBackgroundColor(void) {
	return drawingPanel.getSceneBackgroundColor();
}

int Gui::getLineWidth() {
	return drawingPanel.getLineWidth();
}

ofColor Gui::getLineColor() {
	return drawingPanel.getLineColor();
}

Primitype Gui::getTypePrimitive() {
	return drawingPanel.getDrawMode();
}

Geotype Gui::getTypeGeometrique() {
	return drawingPanel.getGeometricType();
}

ofColor Gui::getFillColor() {
	return drawingPanel.getFillColor();
}
ofRectangle Gui::getScene2DShape(void) {
	return scene2d;
}

ofRectangle Gui::getScene3DShape(void) {
	return scene3d;
}

UserMode Gui::getSelectedUserMode(void) {
	return selectedUserMode;
}

TransformTool Gui::getSelectedTransformTool(void) {
	return transformPanel.getSelectedTransformTool();
}

ofRectangle Gui::getDrawingPanelShape(void) {
	return drawingPanel.getShape();
}

ofRectangle Gui::getTransformPanelShape(void) {
	return transformPanel.getShape();
}

bool Gui::getIsImageImported(void) {
	return isImageImported;
}

ofImage Gui::getImportedImage(void) {
	return imageBuffer;
}

void Gui::setIsImageImported(bool _isImageImported) {
	isImageImported = _isImageImported;
}

bool Gui::getIsHistogramShowing(void) {
	return isHistogramShowing;
}

bool* Gui::getPropertiesPanelBtnStates(void) {
	return propertiesPanel.getBtnStates();
}

vector<SceneElement*> Gui::getSelectedElements(void) {
	return sceneHierarchyPanel.getSelectedSceneElements();
}