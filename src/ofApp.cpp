#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Real Engine");
	renderer.setup();
}

//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::update() {
	renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	renderer.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs& key) {
	renderer.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(ofMouseEventArgs& mouse) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Moved, mouse.x, mouse.y);
	renderer.mouseMoved(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Dragged, x, y, button);
	renderer.mouseDragged(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Pressed, x, y, button);
	renderer.mousePressed(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	ofMouseEventArgs& mouseEvent = ofMouseEventArgs(ofMouseEventArgs::Released, x, y, button);
	renderer.mouseReleased(mouseEvent);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
	renderer.mouseEntered();
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
	renderer.mouseExited();
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
