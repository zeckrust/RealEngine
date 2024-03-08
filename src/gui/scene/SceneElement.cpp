#include "SceneElement.h"

SceneElement::SceneElement(std::string _labelName, SceneObject* obj_ptr) : ofxLabel(_labelName), labelName(_labelName), label(_labelName), object_ptr(obj_ptr){
	setBackgroundColor(DEFAULT_COLOR);
	setupFont();
}

void SceneElement::setupExtension(void) {
	extension.setup();
}

void SceneElement::setupFont() {
	std::string executablePath = ofFilePath::getCurrentExeDir();
	std::string fontPath = ofFilePath::join(executablePath, REGULAR_FONT);
	loadFont(fontPath, FONT_SIZE);
	labelFont.load(fontPath, FONT_SIZE);
}

void SceneElement::update() {
	if (isSelected()) {
		setBackgroundColor(SELECTED_COLOR);
	}
	else {
		setBackgroundColor(DEFAULT_COLOR);
	}
}

void SceneElement::updateElement(uint32_t newDepth) {
	depth = newDepth;
	std::string newLabel;
	for (uint32_t i = 0; i < depth; ++i) {
		newLabel += "|   "; // Creates identation
	}
	newLabel += labelName;

	setup(newLabel);
	label = newLabel;
	setSize(labelFont.stringWidth(newLabel) + FONT_WIDTH_ERROR, getHeight());
	updateChildren();
}

void SceneElement::draw(void) {
	extension.draw();
}

void SceneElement::addChildren(SceneElement *element) {
	auto child_it = std::find(children.begin(), children.end(), element);
	if (element != nullptr && element != this && child_it == children.end()) {
		children.push_back(element);
		element->updateElement(depth + 1);
	}
}

void SceneElement::removeChildren(SceneElement *element) {
	auto child_it = std::find(children.begin(), children.end(), element);
	if (child_it != children.end()) {
		children.erase(child_it);
	}
	for (int i = 0; i < std::size(children); i++) {			
		if (children[i] != nullptr) {
			children[i]->removeChildren(element);
		}
	}
}


bool SceneElement::mousePressed(ofMouseEventArgs& args) {
	bool isClickInside = getShape().inside(args.x, args.y);
	extension.mousePressed(args);

	if (isClickInside && args.button == OF_MOUSE_BUTTON_RIGHT) {
		extension.show();
	}
	else {
		extension.hide();
	}

	return isClickInside && args.button == OF_MOUSE_BUTTON_LEFT;
}

bool SceneElement::mouseReleased(ofMouseEventArgs &args) {
	extension.mouseReleased(args);
	return getShape().inside(args.x, args.y);
}

bool SceneElement::mouseMoved(ofMouseEventArgs &args) {
	return extension.mouseMoved(args);
}

std::vector<SceneElement*> SceneElement::getChildren() {
	return children;
}

std::vector<SceneElement*> SceneElement::getDeepChildren() {
	std::vector<SceneElement*> deepChildren = children;
	for (int i = 0; i < std::size(children); i++) {
		if (children[i] != nullptr) {
			std::vector<SceneElement*> subDeepChildren = children[i]->getDeepChildren();
			deepChildren.insert(deepChildren.end(), subDeepChildren.begin(), subDeepChildren.end());
		}
	}
	return deepChildren;
}

uint32_t SceneElement::getDepth() {
	return depth;
}

void SceneElement::updateChildren() {
	for (int i = 0; i < std::size(children); i++) {
		if (children[i] != nullptr) {
			children[i]->updateElement(depth + 1);
		}
	}
}

bool SceneElement::isElementAlreadyChild(SceneElement *element) {
	auto child_it = std::find(children.begin(), children.end(), element);
	if (child_it != children.end()) {
		return true;
	}
	for (int i = 0; i < std::size(children); i++) {
		if (children[i] != nullptr && children[i]->isElementAlreadyChild(element)) {
			return true;
		}
	}
	return false;
}

bool SceneElement::isSelected(void) {
	return extension.isSelected();
}

bool SceneElement::isDeleteRequested(void) {
	return extension.isDeleteRequested();
}

SceneObject* SceneElement::getSceneObjectPtr(void) {
	return object_ptr;
}

std::vector<SceneElement*> SceneElement::getSelectedChildren(void) {
	std::vector<SceneElement*> selectedElements;
	for (int i = 0; i < std::size(children); i++) {
		if (children[i] != nullptr) {
			std::vector<SceneElement*> subChildren = children[i]->getChildren();
			if (children[i]->isSelected()) {
				selectedElements.push_back(children[i]);
				std::vector<SceneElement*> deepChildren = children[i]->getDeepChildren();
				selectedElements.insert(selectedElements.end(), deepChildren.begin(), deepChildren.end());
			}
			else {
				std::vector<SceneElement*> selectedChildren = children[i]->getSelectedChildren();
				if (std::size(selectedChildren) > 0) {
					selectedElements.insert(selectedElements.end(), selectedChildren.begin(), selectedChildren.end());
				}
			}
		}
	}
	return selectedElements;
}
