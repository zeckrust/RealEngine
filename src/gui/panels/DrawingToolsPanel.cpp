#include "DrawingToolsPanel.h"

DrawingToolsPanel::DrawingToolsPanel() : CustomPanel() {
	drawingButtons[0] = &drawCircleButton;
	drawingButtons[1] = &drawEllipseButton;
	drawingButtons[2] = &drawLineButton;
	drawingButtons[3] = &drawSquareButton;
	drawingButtons[4] = &drawRectButton;
}

void DrawingToolsPanel::setup(std::string panelName, float x, float y) {
	CustomPanel::setup(panelName, x, y);
	setupButtons();
	setupFields();
	setupColorPanels();
	typePrimitive = Primitype::none;
}

void DrawingToolsPanel::setupButtons(void) {
	drawCircleButton.setup("Circle", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	drawEllipseButton.setup("Ellipse", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	drawLineButton.setup("Line", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	drawSquareButton.setup("Square", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);
	drawRectButton.setup("Rectangle", REGULAR_FONT, 0, 0, DEFAULT_BUTTON_HEIGHT);

	add(&drawCircleButton);
	add(&drawEllipseButton);
	add(&drawLineButton);
	add(&drawSquareButton);
	add(&drawRectButton);
}	

void DrawingToolsPanel::setupFields(void) {
	lineWidthField.setup("Line width :", 5);
	add(&lineWidthField);
}

void DrawingToolsPanel::setupColorPanels(void) {
	lineColorPanel.setup("Line color", 0, 0, ofColor::blue);
	fillColorPanel.setup("Fill color", 0, 0, ofColor::blue);
	backgroundColorPanel.setup("Background color", 0, 0, SCENE_DEFAULT_BACKGROUND_COLOR);
	add(&lineColorPanel);
	add(&fillColorPanel);
	add(&backgroundColorPanel);
}

void DrawingToolsPanel::update(void) {
	CustomPanel::update();
	lineColorPanel.update();
	fillColorPanel.update();
	backgroundColorPanel.update();
}

void DrawingToolsPanel::draw(void) {
	CustomPanel::draw();
	lineColorPanel.draw();
	fillColorPanel.draw();
	backgroundColorPanel.draw();
}

bool DrawingToolsPanel::mouseMoved(ofMouseEventArgs& args) {
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			collection[i]->mouseMoved(args);
		}
	}
	return true;
}

bool DrawingToolsPanel::mousePressed(ofMouseEventArgs& args) {
	bool isPressed = CustomPanel::mousePressed(args);

	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			bool isInButton =  collection[i]->getShape().inside(args.x, args.y);
			if (isInButton && isDrawingButton(collection[i])) {
				if (collection[i] == selectedDrawingTool) {
					setSelectedDrawingTool(nullptr);
				}
				else {
					setSelectedDrawingTool((CustomButton*)collection[i]);
				}
			}
		}
	}
	return isPressed;
}

bool DrawingToolsPanel::mouseReleased(ofMouseEventArgs& args) {
	bool isReleased = false;
	for (int i = 0; i < std::size(collection); i++) {
		if (collection[i] != nullptr) {
			isReleased |= collection[i]->mouseReleased(args);
		}
	}
	return isReleased;
}

void DrawingToolsPanel::setSelectedDrawingTool(CustomButton* button) {
	selectedDrawingTool = button;
	if (button != nullptr) {
		button->setBackground(SELECTED_BUTTON_COLOR);
		if (button == &drawCircleButton){
			typePrimitive = Primitype::circle;
		}
		else if (button == &drawEllipseButton) {
			typePrimitive = Primitype::ellipse;
		}
		else if (button == &drawLineButton)
		{
			typePrimitive = Primitype::line;
		}
		else if (button == &drawSquareButton) {
			typePrimitive = Primitype::square;
		}
		else if (button == &drawRectButton) {
			typePrimitive = Primitype::rectangle;
		}
	}
	for (int i = 0; i < std::size(drawingButtons); i++) {
		if (drawingButtons[i] != nullptr && drawingButtons[i] != button) {
			drawingButtons[i]->setBackground(BUTTON_DEFAULT_COLOR);
		}
	}
}

bool DrawingToolsPanel::isDrawingButton(ofxBaseGui* element) {
	for (int i = 0; i < std::size(drawingButtons); i++) {
		if (drawingButtons[i] != nullptr && drawingButtons[i] == element) {
			return true;
		}
	}
	return false;
}

int DrawingToolsPanel::getLineWidth(void) {
	int lineWidth = lineWidthField;
	return lineWidth;
}

ofColor DrawingToolsPanel::getLineColor(void) {
	return lineColorPanel.getColor();
}

ofColor DrawingToolsPanel::getFillColor(void) {
	return fillColorPanel.getColor();
}

ofColor DrawingToolsPanel::getSceneBackgroundColor(void) {
	return backgroundColorPanel.getColor();
}

Primitype DrawingToolsPanel::getDrawMode(void) {
	return typePrimitive;
}
