#include "SceneHierarchyPanel.h"


SceneHierarchyPanel::SceneHierarchyPanel() : CustomPanel() {

}

// ********************************************************************************************************************
// DISCLAMER : Cast from ofxBaseGui to SceneElement (only SceneElement objects can be added to a SceneHierarchyPanel)
// ********************************************************************************************************************
void SceneHierarchyPanel::add(ofxBaseGui* element) {
	auto collection_it = std::find(collection.begin(), collection.end(), element);
	if (element != nullptr && collection_it == collection.end()) {
		CustomPanel::add(element);
		SceneElement* sceneElement = (SceneElement*) element;
		std::vector<SceneElement*> sceneElementsChildren = sceneElement->getChildren();

		for (int i = 0; i < std::size(sceneElementsChildren); i++) {
			add(sceneElementsChildren[i]);
		}
	}
}

void SceneHierarchyPanel::remove(ofxBaseGui *element) {
	auto collection_it = std::find(collection.begin(), collection.end(), element);
	if (collection_it != collection.end()) {
		collection.erase(collection_it);
	}
	else {
		for (int i = 0; i < std::size(collection); i++) {
			if (collection[i] != nullptr) {
				SceneElement* sceneElement = (SceneElement*)collection[i];
				sceneElement->removeChildren((SceneElement*)element);
			}
		}
	}
}

bool SceneHierarchyPanel::mousePressed(ofMouseEventArgs &args) {
	bool isPressed = ofxGuiGroup::mousePressed(args);
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr && collection[i]->mousePressed(args)) {
			pressedSceneElement = collection[i];
		}
	}
	return isPressed;
}

bool SceneHierarchyPanel::mouseReleased(ofMouseEventArgs &args) {
	bool isReleased = ofxGuiGroup::mouseReleased(args);
	
	if (pressedSceneElement != nullptr) {
		ofxBaseGui* releasedSceneElement = nullptr;
		for (int i = 0; i < std::size(collection); i++) {
			if (collection[i] != nullptr && collection[i]->mouseReleased(args)) {
				releasedSceneElement = collection[i];
			}
		}
		if (releasedSceneElement != nullptr) {
			remove(pressedSceneElement);
			SceneElement* sceneElement = (SceneElement*)releasedSceneElement;
			sceneElement->addChildren((SceneElement*)pressedSceneElement);
			updateDisplay();
		}
		else {
			remove(pressedSceneElement);
			add(pressedSceneElement);
			SceneElement* sceneElement = (SceneElement*)pressedSceneElement;
			sceneElement->update(0);
		}
		pressedSceneElement = nullptr;
	}
	return isReleased;
}

void SceneHierarchyPanel::updateDisplay() {
	std::vector<ofxBaseGui*> sceneElementsCopy = collection;
	collection = std::vector<ofxBaseGui*>();
	for (int i = 0; i < std::size(sceneElementsCopy); i++) {
		if (sceneElementsCopy[i] != nullptr) {
			add(sceneElementsCopy[i]);
			SceneElement* sceneElement = (SceneElement*)sceneElementsCopy[i];
			sceneElement->update(0);
		}
	}
}
