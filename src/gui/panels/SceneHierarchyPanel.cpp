#include "SceneHierarchyPanel.h"
#include "../../Renderer.h"

// ********************************************************************************************************************
// DISCLAMER : Cast from ofxBaseGui to SceneElement (only SceneElement objects can be added to a SceneHierarchyPanel)
// ********************************************************************************************************************

SceneHierarchyPanel::SceneHierarchyPanel() : CustomPanel() {

}

void SceneHierarchyPanel::setup(std::string panelName, float x, float y) {
	CustomPanel::setup(panelName, x, y);
	renderer = Renderer::getInstance();
}

void SceneHierarchyPanel::update(void) {
	CustomPanel::update();
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			SceneElement* sceneElement = (SceneElement*)collection[i];
			if (sceneElement->isDeleteRequested()) {
				deleteRequestedSceneElement = sceneElement;
			}
			else {
				sceneElement->update();
			}
		}
	}
}

void SceneHierarchyPanel::draw(void) {
	ofxGuiGroup::draw();
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			SceneElement* sceneElement = (SceneElement*)collection[i];
			sceneElement->draw();
		}
	}
}

void SceneHierarchyPanel::createSceneElement(std::string sceneElementName, SceneObject* obj_ptr) {
	SceneElement *newSceneElement = new SceneElement(sceneElementName, obj_ptr);
	add(newSceneElement);
}

void SceneHierarchyPanel::add(ofxBaseGui* element) {
	auto collection_it = std::find(collection.begin(), collection.end(), element);
	if (element != nullptr && collection_it == collection.end()) {
		CustomPanel::add(element);
		SceneElement* sceneElement = (SceneElement*) element;
		sceneElement->setupExtension();
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
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			SceneElement* sceneElement = (SceneElement*)collection[i];
			sceneElement->removeChildren((SceneElement*)element);
		}
	}
	removeElementChildren(element);
}

void SceneHierarchyPanel::removeElementChildren(ofxBaseGui *element) {
	SceneElement* sceneElement = (SceneElement*) element;
	std::vector<SceneElement*> sceneElementsChildren = sceneElement->getChildren();
	for (int i = 0; i < std::size(sceneElementsChildren); i++) {
		remove(sceneElementsChildren[i]);
	}
}

bool SceneHierarchyPanel::mousePressed(ofMouseEventArgs &args) {
	bool isPressed = ofxGuiGroup::mousePressed(args);
	if (!isMinimized()) {
		if (args.button == OF_MOUSE_BUTTON_RIGHT) {
			for (int i = 0; i < std::size(collection); i++) {
				if (collection[i] != nullptr) {
					collection[i]->mousePressed(args);
				}
			}
		}
		else {
			for (int i = 0; i < std::size(collection); i++) {
				if (collection[i] != nullptr && collection[i]->mousePressed(args)) {
					pressedSceneElement = (SceneElement*)collection[i];
				}
			}
		}
	}
	return isPressed;
}

bool SceneHierarchyPanel::mouseReleased(ofMouseEventArgs &args) {
	bool isReleased = ofxGuiGroup::mouseReleased(args);
	if (!isMinimized()) {
		if (args.button == OF_MOUSE_BUTTON_RIGHT) {
			for (int i = 0; i < std::size(collection); i++) {
				if (collection[i] != nullptr) {
					collection[i]->mouseReleased(args);
				}
			}
		}
		else if (pressedSceneElement != nullptr) {
			for (int i = 0; i < std::size(collection); i++) {
				if (collection[i] != nullptr && collection[i]->mouseReleased(args)) {
					releasedSceneElement = (SceneElement*)collection[i];
				}
			}
			handleMouseReleased();
			pressedSceneElement = nullptr;
			releasedSceneElement = nullptr;
		}
		handleDeleteRequest();
	}
	return isReleased;
}

bool SceneHierarchyPanel::mouseMoved(ofMouseEventArgs& args) {
	bool isMoved = false;
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			isMoved |= collection[i]->mouseMoved(args);
		}
	}
	return isMoved;
}

void SceneHierarchyPanel::handleMouseReleased(void) {
	SceneElement* releasedElement = (SceneElement*)releasedSceneElement;
	SceneElement* pressedElement = (SceneElement*)pressedSceneElement;

	bool isReleasedElementInvalid = releasedSceneElement != nullptr && pressedElement->isElementAlreadyChild(releasedElement);
	isReleasedElementInvalid |= releasedSceneElement == pressedSceneElement;

	if (isReleasedElementInvalid) {
		return;
	}
	else if (releasedSceneElement != nullptr) {
		remove(pressedSceneElement);
		releasedSceneElement->addChildren(pressedElement);
		updateDisplay();
	}
	else if (pressedSceneElement->getDepth() != 0) {
		remove(pressedSceneElement);
		add(pressedSceneElement);
		pressedSceneElement->updateElement(0);
	}
}

void SceneHierarchyPanel::handleDeleteRequest(void) {
	if (deleteRequestedSceneElement != nullptr) {
		deleteSceneObjects(deleteRequestedSceneElement);
		remove(deleteRequestedSceneElement);
		deleteRequestedSceneElement = nullptr;
	}
}

void SceneHierarchyPanel::deleteSceneObjects(SceneElement* sceneElement) {
	std::vector<SceneElement*> sceneElementsChildren = sceneElement->getChildren();
	renderer->deleteSceneObject(sceneElement->getSceneObjectPtr());

	for (int i = 0; i < std::size(sceneElementsChildren); i++) {
		deleteSceneObjects(sceneElementsChildren[i]);
	}
}

void SceneHierarchyPanel::updateDisplay() {
	std::vector<ofxBaseGui*> sceneElementsCopy = collection;
	collection = std::vector<ofxBaseGui*>();
	for (int i = 0; i < std::size(sceneElementsCopy); i++) {
		SceneElement* sceneElement = (SceneElement*)sceneElementsCopy[i];
		if (sceneElementsCopy[i] != nullptr && sceneElement->getDepth() == 0) {
			add(sceneElementsCopy[i]);
			sceneElement->updateElement(0);
		}
	}
}

// TODO add children to selected
vector<SceneElement*> SceneHierarchyPanel::getSelectedSceneElements(void) {
	std::vector<SceneElement*> selectedElements;
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			SceneElement* sceneElement = (SceneElement*)collection[i];
			if (sceneElement->isSelected()) {
				selectedElements.push_back(sceneElement);
			}
		}
	}
	return selectedElements;
}