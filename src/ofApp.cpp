#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	setupPanels();

	circle = Object2d();
	circle2 = Object2d(glm::vec2(100, 100), 100);
	camera2d = Camera2d();
	camera2d.addImage(&circle);
	camera2d.addImage(&circle2);
}

//--------------------------------------------------------------
void ofApp::setupPanels() {
	rightPanel.setup(RIGHT_PANEL_NAME, 0, titleBar.getHeight());
	leftPanel.setup(LEFT_PANEL_NAME, 0, titleBar.getHeight());
}

//--------------------------------------------------------------
void ofApp::exit() {
	ringButton.removeListener(this, &ofApp::ringButtonPressed);
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int& circleResolution) {
	ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed() {
	ring.play();
}

//--------------------------------------------------------------
void ofApp::update() {
	rightPanel.setPosition(ofGetWidth() - rightPanel.getWidth(), rightPanel.getPosition().y);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(ofColor::aliceBlue, ofColor::blanchedAlmond);
	ofSetColor(ofColor::black);
	ofDrawCircle(circle.getPosition(), circle.getRadius());
	ofDrawCircle(circle2.getPosition(), circle2.getRadius());

	drawGui();
}

void ofApp::drawGui() {
	rightPanel.draw();
	leftPanel.draw();
	titleBar.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Moved, x, y);
	handleMouseMovedGui(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	camera2d.moveCamera(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Pressed, x, y);
	handleMousePressedGui(mouseEvent);
	camera2d.setLastMousePosition(glm::vec2(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Released, x, y);
	handleMouseReleasedGui(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	titleBar.updateWidth(w);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::handleMousePressedGui(ofMouseEventArgs& args) {
	if (!titleBar.mousePressed(args)) {
		rightPanel.mousePressed(args);
		leftPanel.mousePressed(args);
	}
}

void ofApp::handleMouseReleasedGui(ofMouseEventArgs& args) {
	if (!titleBar.mouseReleased(args)) {
		rightPanel.mouseReleased(args);
		leftPanel.mouseReleased(args);
	}
}

void ofApp::handleMouseMovedGui(ofMouseEventArgs& args) {
	if (!titleBar.mouseMoved(args)) {
		rightPanel.mouseMoved(args);
		leftPanel.mouseMoved(args);
	}
}
