#include "Renderer.h"

Renderer::Renderer(Camera2d* _camera2d) : camera2d(_camera2d) {

}

void Renderer::setup() {
	gui = Gui::getInstance();
	gui->setup();
	ofSetFrameRate(FRAME_RATE);
	cursors.setup();
}

void Renderer::update() {
	gui->update();
	cursors.update();
}

void Renderer::draw() {
	ofSetBackgroundColor(BACKGROUND_COLOR);
	gui->draw();
	cursors.draw();
}

void Renderer::mousePressed(ofMouseEventArgs& args) {
	gui->mousePressed(args);
	camera2d->setLastMousePosition(glm::vec2(args.x, args.y));
}

void Renderer::mouseReleased(ofMouseEventArgs& args) {
	gui->mouseReleased(args);
}

void Renderer::mouseMoved(ofMouseEventArgs& args) {
	gui->mouseMoved(args);
}

void Renderer::mouseDragged(ofMouseEventArgs& args) {
	camera2d->moveCamera(args.x, args.y);
}

void Renderer::mouseExited() {
	cursors.mouseExited();
}

void Renderer::mouseEntered() {
	cursors.mouseEntered();
}

void Renderer::windowResized(int width, int height) {
	gui->windowResized(width, height);
}

void Renderer::keyPressed(ofKeyEventArgs& args) {
	if (args.key == KEY_CONTROL_S) {
		gui->saveScenes();
	}
}