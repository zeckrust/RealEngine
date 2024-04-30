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
	dessinateurOrthogonal.setup(&shapes);
	dessinateurPerspective.setup(&shapes);
}

void Renderer::update() {
	ofSetBackgroundColor(BACKGROUND_COLOR);
	gui->update();
	dessinateurOrthogonal.update();
	dessinateurPerspective.update();
	cursors.update();
}

void Renderer::draw() {
	gui->drawScenes();
	dessinateurOrthogonal.draw();
	dessinateurPerspective.draw();
	gui->draw();
	cursors.draw();
}

void Renderer::mousePressed(ofMouseEventArgs& args) {
	gui->mousePressed(args);
	dessinateurOrthogonal.mousePressed(args);
	dessinateurPerspective.mousePressed(args);
}

void Renderer::mouseReleased(ofMouseEventArgs& args) {
	gui->mouseReleased(args);
	dessinateurOrthogonal.mouseReleased(args);
	dessinateurPerspective.mouseReleased(args);
	dessinateurOrthogonal.redraw();
	dessinateurPerspective.redraw();
}

void Renderer::mouseMoved(ofMouseEventArgs& args) {
	gui->mouseMoved(args);
}

void Renderer::mouseDragged(ofMouseEventArgs& args) {
	dessinateurOrthogonal.mouseDragged(args);
	dessinateurPerspective.mouseDragged(args);
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
	switch (args.key) {
	case KEY_CONTROL_S:
		gui->saveScenes();
		break;
	case KEY_A:
		dessinateurPerspective.moveLeft();
		break;
	case KEY_S:
		dessinateurPerspective.moveDown();
		break;
	case KEY_D:
		dessinateurPerspective.moveRight();
		break;
	case KEY_Q:
		dessinateurPerspective.moveForward();
		break;
	case KEY_W:
		dessinateurPerspective.moveUp();
		break;
	case KEY_E:
		dessinateurPerspective.moveBackward();
		break;
	case KEY_H:
		dessinateurPerspective.panLeft();
		break;
	case KEY_J:
		dessinateurPerspective.tiltDown();
		break;
	case KEY_K:
		dessinateurPerspective.panRight();
		break;
	case KEY_Y:
		dessinateurPerspective.rollLeft();
		break;
	case KEY_U:
		dessinateurPerspective.tiltUp();
		break;
	case KEY_I:
		dessinateurPerspective.rollRight();
		break;

	}
	if (args.key == KEY_CONTROL_S) {
		gui->saveScenes();
	}
}

void Renderer::deleteSceneObject(SceneObject* obj) {
	dessinateurOrthogonal.deleteObject(obj);
	dessinateurPerspective.deleteObject(obj);
}