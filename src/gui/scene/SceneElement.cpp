#include "SceneElement.h"

SceneElement::SceneElement(std::string _labelName) : ofxLabel(_labelName), labelName(_labelName), label(_labelName){
	setBackgroundColor(ofColor(0, 0, 0, 0));
	setupFont();
}

void SceneElement::setupFont() {
	std::string executablePath = ofFilePath::getCurrentExeDir();
	std::string fontPath = ofFilePath::join(executablePath, REGULAR_FONT);
	loadFont(fontPath, FONT_SIZE);
	labelFont.load(fontPath, FONT_SIZE);
}

void SceneElement::update(uint32_t newDepth) {
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

void SceneElement::addChildren(SceneElement *element) {
	auto child_it = std::find(children.begin(), children.end(), element);
	if (element != nullptr && element != this && child_it == children.end()) {
		children.push_back(element);
		element->update(depth + 1);
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
	return getShape().inside(args.x, args.y);
}

bool SceneElement::mouseReleased(ofMouseEventArgs &args) {
	return getShape().inside(args.x, args.y);
}

std::vector<SceneElement*> SceneElement::getChildren() {
	return children;
}

uint32_t SceneElement::getDepth() {
	return depth;
}

void SceneElement::updateChildren() {
	for (int i = 0; i < std::size(children); i++) {
		if (children[i] != nullptr) {
			children[i]->update(depth + 1);
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
