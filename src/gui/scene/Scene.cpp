#include "Scene.h"

Scene::Scene() : ofRectangle() {

}

void Scene::setup(float x, float y, float width, float height) {
	setPosition(x, y);
	setSize(width, height);
}

void Scene::draw() {
	ofFill();
	ofSetColor(SCENE_BACKGROUND_COLOR);
	ofDrawRectRounded(*this, SCENE_CORNER_RADIUS);
}