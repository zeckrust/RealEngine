#include "Scene.h"
#include "../Gui.h"


Scene::Scene() : ofRectangle() {

}

void Scene::setup(float x, float y, float width, float height) {
	gui = Gui::getInstance();
	setPosition(x, y);
	setSize(width, height);
}

void Scene::update(void) {
	backgroundColor = gui->getSceneBackgroundColor();
}

void Scene::draw(void) {
	ofFill();
	ofSetColor(backgroundColor);
	ofDrawRectangle(*this);
}