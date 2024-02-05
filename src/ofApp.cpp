#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	renderer.setup();

	circle = Object2d();
	circle2 = Object2d(glm::vec2(100, 100), 100);
	camera2d = Camera2d();
	camera2d.addImage(&circle);
	camera2d.addImage(&circle2);
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
	renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(ofColor::aliceBlue, ofColor::blanchedAlmond);
	ofSetColor(ofColor::black);
	ofDrawCircle(circle.getPosition(), circle.getRadius());
	ofDrawCircle(circle2.getPosition(), circle2.getRadius());

	renderer.draw();
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
	renderer.mouseMoved(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Dragged, x, y);
	renderer.mouseDragged(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Pressed, x, y);
	renderer.mousePressed(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Released, x, y);
	renderer.mouseReleased(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	renderer.windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
