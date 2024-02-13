#include "Renderer.h"

Renderer::Renderer(Camera2d* _camera2d) : camera2d(_camera2d) {

}

void Renderer::setup() {
	gui = Gui::getInstance();
	gui->setup();
	ofSetFrameRate(FRAME_RATE);
}

void Renderer::update() {
	gui->update();
}

void Renderer::draw() {
	ofSetBackgroundColor(BACKGROUND_COLOR);
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
	gui->windowResized(width, height);
}

void Renderer::keyPressed(ofKeyEventArgs& args) {
	if (args.key == KEY_CONTROL_S) {
		ofFileDialogResult result = ofSystemLoadDialog("Where to save 2d and 3d scenes", true,  "");
		saveScene(gui->getScene2d(), result.getPath() + "\\scene2d.png");
		saveScene(gui->getScene3d(), result.getPath() + "\\scene3d.png");
	}
}

void Renderer::saveScene(Scene& scene, std::string filePath) {
	ofImage imageScene2d;
	ofLog() << filePath;
	imageScene2d.grabScreen(scene.getX(), scene.getY(), scene.getWidth(), scene.getHeight());
	imageScene2d.save(filePath);
}