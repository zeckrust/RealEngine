#include "Renderer.h"

Renderer::Renderer(Gui* _gui, Camera2d* _camera2d) : gui(_gui), camera2d(_camera2d) {

}

void Renderer::setup() {
	ofSetFrameRate(FRAME_RATE);
	gui->setup();
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
	gui->updateTitleBarWidth(width);
	gui->setup();
}

void Renderer::keyPressed(ofKeyEventArgs& args) {
	if (args.hasModifier(OF_KEY_CONTROL) && args.key == 19) { // 19 is CTRL+s key number
		ofFileDialogResult result = ofSystemLoadDialog("Where to save 2d and 3d scenes", true,  "C:\\Users\\Mathieu\\Downloads");
		saveScene(gui->getScene2d(), result.getPath() + "\\scene2d.png");
		saveScene(gui->getScene3d(), result.getPath() + "\\scene3d.png");
	}
}

void Renderer::saveScene(Scene& scene, std::string filePath) {
	ofImage imageScene2d;
	ofLog() << filePath;
	imageScene2d.grabScreen(scene.getLeft(), scene.getTop(), scene.getWidth(), scene.getHeight());
	imageScene2d.save(filePath);
}