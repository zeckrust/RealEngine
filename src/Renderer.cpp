#include "Renderer.h"

Renderer::Renderer() {

}

Renderer* Renderer::getInstance() {
	if (instancePtr == nullptr) {
		instancePtr = new Renderer();
		return instancePtr;
	}
	else {
		return instancePtr;
	}
}

void Renderer::setup() {
	gui = Gui::getInstance();
	gui->setup();
	ofSetFrameRate(FRAME_RATE);
	cursors.setup();
	dessinateurVectoriel.setup();
	dessinateurOrthogonal.setup();
}

void Renderer::update() {
	ofSetBackgroundColor(BACKGROUND_COLOR);
	gui->update();
	dessinateurVectoriel.update();
	dessinateurOrthogonal.update();
	cursors.update();
}

void Renderer::draw() {
	gui->draw();
	dessinateurVectoriel.draw();
	dessinateurOrthogonal.draw();
	cursors.draw();
}

void Renderer::mousePressed(ofMouseEventArgs& args) {
	gui->mousePressed(args);
	dessinateurVectoriel.mousePressed(args);
	dessinateurOrthogonal.mousePressed(args);
}

void Renderer::mouseReleased(ofMouseEventArgs& args) {
	gui->mouseReleased(args);
	dessinateurVectoriel.mouseReleased(args);
	dessinateurOrthogonal.mouseReleased(args);
}

void Renderer::mouseMoved(ofMouseEventArgs& args) {
	gui->mouseMoved(args);
}

void Renderer::mouseDragged(ofMouseEventArgs& args) {
	dessinateurVectoriel.mouseDragged(args);
	dessinateurOrthogonal.mouseDragged(args);
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

void Renderer::deleteSceneObject(SceneObject* obj) {
	dessinateurVectoriel.deleteObject(obj);
	dessinateurOrthogonal.deleteObject(obj);
}