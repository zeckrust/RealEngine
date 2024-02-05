#include "Renderer.h"

Renderer::Renderer(Gui* _gui, Camera2d* _camera2d) : gui(_gui), camera2d(_camera2d) {

}

void Renderer::setup() {
	gui->setup();
}

void Renderer::update() {
	gui->update();
}

void Renderer::draw() {
	gui->draw();
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

void Renderer::windowResized(int width, int height) {
	gui->updateTitleBarWidth(width);
	gui->setup();
}
