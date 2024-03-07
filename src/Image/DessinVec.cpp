#include "DessinVec.h"
#include "../gui/Gui.h"

DessinVec::DessinVec(){

}

void DessinVec::setup()
{
	mode = Primitype::none;

	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;
	mouse_pressed = false;

	compteur_square = 0;
	compteur_circle = 0;
	compteur_ellipse = 0;
	compteur_rectangle = 0;
	compteur_line = 0;
	compteur_image = 0;

	gui = Gui::getInstance();

	scene2DShape = gui->getScene2DShape();
	fbo.allocate(scene2DShape.getHeight(), scene2DShape.getWidth(), GL_RGBA);
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();
}

void DessinVec::update()
{
	scene2DShape = gui->getScene2DShape();
	bool hasPositionChanged = scene2DShape.getPosition() != oldScene2dShape.getPosition();
	bool hasWidthChanged = scene2DShape.getWidth() != oldScene2dShape.getWidth();
	bool hasHeightChanged = scene2DShape.getHeight() != oldScene2dShape.getHeight();

	if (hasPositionChanged || hasWidthChanged || hasHeightChanged) {
		fbo.allocate(scene2DShape.getWidth(), scene2DShape.getHeight(), GL_RGBA);
		redraw();
	}

	oldScene2dShape = scene2DShape;
}

void DessinVec::reset()
{
	shapes.clear();
}

void DessinVec::add_vector_shape() 
{
	shapes.push_back(new VecObject(mode));

	shapes.back()->setPosition(glm::vec3(mouse_press_x, mouse_press_y, 0));
	shapes.back()->setDimensions(glm::vec3(mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y, 0));
	shapes.back()->setStrokeColor(gui->getLineColor());
	shapes.back()->setStrokeWidth(gui->getLineWidth());
	shapes.back()->setFillColor(gui->getFillColor());

	mouse_pressed = false;

	std::string name;

	switch (mode)
	{
	case Primitype::none:
		break;
	case Primitype::square:
		name = "Square";
		name += to_string(compteur_square);
		compteur_square++;
		break;
	case Primitype::line:
		name = "Line";
		name += to_string(compteur_line);
		compteur_line++;
		break;
	case Primitype::rectangle:
		name = "Rectangle";
		name += to_string(compteur_rectangle);
		compteur_rectangle++;
		break;
	case Primitype::ellipse:
		name = "Ellipse";
		name += to_string(compteur_ellipse);
		compteur_ellipse++;
		break;
	case Primitype::circle:
		name = "Circle";
		name += to_string(compteur_circle);
		compteur_circle++;
		break;
	case Primitype::image:
		name = "Image";
		name += to_string(compteur_image);
		compteur_image++;
		break;
	default:
		break;
	}

	gui->createSceneElement(name, shapes.back());

}

void DessinVec::deleteObject(SceneObject* obj) {
	auto shapes_it = std::find(shapes.begin(), shapes.end(), obj);
	if (shapes_it != shapes.end()) {
		shapes.erase(shapes_it);
		redraw();
	}	
}

void DessinVec::mousePressed(ofMouseEventArgs& args)
{
	bool isInDrawingMode = gui->getSelectedUserMode() == DRAWING;
	bool isInsideScene = scene2DShape.inside(args.x, args.y);
	bool isDrawingToolSelected = gui->getTypePrimitive() != Primitype::none;

	if (isInDrawingMode && isInsideScene && isDrawingToolSelected) {
		mouse_pressed = true;
		mouse_press_x = args.x - scene2DShape.getPosition().x;
		mouse_press_y = args.y - scene2DShape.getPosition().y;
		mouse_current_x = args.x - scene2DShape.getPosition().x;
		mouse_current_y = args.y - scene2DShape.getPosition().y;
		mode = gui->getTypePrimitive();
	}
}

void DessinVec::mouseReleased(ofMouseEventArgs& args)
{
	if (mouse_pressed) {
		add_vector_shape();
	}
}

void DessinVec::mouseDragged(ofMouseEventArgs& args)
{
	if (mouse_pressed) {
		mouse_current_x = args.x - scene2DShape.getPosition().x;
		mouse_current_y = args.y - scene2DShape.getPosition().y;
		int formatX = 0;
		int formatY = 0;
		int radius = 0;

		ofPushStyle();
		fbo.begin();
		ofClear(0, 0, 0, 0);
		draw_buffer();

		switch (mode)
		{
		case Primitype::none:
			break;
		case Primitype::square:

			ofSetLineWidth(gui->getLineWidth());
			ofSetColor(gui->getFillColor());

			formatX = mouse_current_x - mouse_press_x;
			formatY = mouse_current_y - mouse_press_y;

			if (formatX < 0 && formatY < 0) {
				if (abs(formatX) > abs(formatY)) {
					formatY = formatX;
				}
				else {
					formatX = formatY;
				}
			}
			else if ((formatX > 0 && formatY < 0) || (formatX < 0 && formatY > 0)) {
				if (abs(formatX) > abs(formatY)) {
					formatY = -formatX;
				}
				else {
					formatX = -formatY;
				}
			}
			else {
				if (formatX > formatY) {
					formatY = formatX;
				}
				else {
					formatX = formatY;
				}
			}
			
			ofDrawRectangle(glm::vec2(mouse_press_x, mouse_press_y), formatX, formatY);

			ofNoFill();
			ofSetColor(gui->getLineColor());
			ofDrawRectangle(glm::vec2(mouse_press_x, mouse_press_y), formatX, formatY);

			break;
		case Primitype::line:

			ofSetLineWidth(gui->getLineWidth());
			ofSetColor(gui->getLineColor());

			ligne.clear();
			ligne.addVertex(mouse_press_x, mouse_press_y);
			ligne.addVertex(mouse_current_x, mouse_current_y);
			ligne.draw();
			break;
		case Primitype::rectangle:

			ofSetLineWidth(gui->getLineWidth());
			ofSetColor(gui->getFillColor());
			ofDrawRectangle(glm::vec2(mouse_press_x, mouse_press_y), mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y);

			ofNoFill();
			ofSetColor(gui->getLineColor());
			ofDrawRectangle(glm::vec2(mouse_press_x, mouse_press_y), mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y);

			break;
		case Primitype::ellipse:

			ofSetLineWidth(gui->getLineWidth());
			ofSetColor(gui->getFillColor());

			ofDrawEllipse(glm::vec2(mouse_press_x, mouse_press_y), 2*(mouse_current_x - mouse_press_x), 2*(mouse_current_y - mouse_press_y));

			ofNoFill();
			ofSetColor(gui->getLineColor());
			ofDrawEllipse(glm::vec2(mouse_press_x, mouse_press_y), 2*(mouse_current_x - mouse_press_x), 2 * (mouse_current_y - mouse_press_y));

			break;
		case Primitype::circle:
			ofSetLineWidth(gui->getLineWidth());
			ofSetColor(gui->getFillColor());

			ofSetCircleResolution(100);

			radius = sqrt(pow(mouse_current_x - mouse_press_x, 2) + pow(mouse_current_y - mouse_press_y, 2));

			ofDrawCircle(glm::vec2(mouse_press_x, mouse_press_y), radius);

			ofNoFill();
			ofSetColor(gui->getLineColor());
			ofDrawCircle(glm::vec2(mouse_press_x, mouse_press_y), radius);

			break;
		default:
			break;
		}

		fbo.end();
		ofPopStyle();
	}
}

void DessinVec::draw()
{
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	fbo.draw(scene2DShape.getPosition().x, scene2DShape.getPosition().y);
	ofPopStyle();
}

void DessinVec::redraw() {
	fbo.begin();
	ofClear(0, 0, 0, 0);
	draw_buffer();
	fbo.end();
}

void DessinVec::draw_buffer() {
	for (auto & shape : shapes)
	{
		switch (shape->getType())
		{
		case Primitype::none:
			break;

		case Primitype::square:
			draw_square(*shape);
			break;

		case Primitype::line:
			draw_line(*shape);
			break;

		case Primitype::rectangle:
			draw_rectangle(*shape);
			break;

		case Primitype::ellipse:
			draw_ellipse(*shape);
			break;

		case Primitype::circle:
			draw_circle(*shape);
			break;

		default:
			break;
		}
	}
}

ofFbo DessinVec::getFbo() const {
	return fbo;
}

void DessinVec::draw_rectangle(VecObject obj) const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(obj.getStrokeWidth());
	ofSetColor(obj.getFillColor());

	ofDrawRectangle(obj.getPosition(), obj.getDimensions().x, obj.getDimensions().y);

	ofNoFill();
	ofSetColor(obj.getStrokeColor());
	ofDrawRectangle(obj.getPosition(), obj.getDimensions().x, obj.getDimensions().y);

	ofPopStyle();
}

void DessinVec::draw_line(VecObject obj) const {
	ofPolyline line;

	ofPushStyle();

	ofSetLineWidth(obj.getStrokeWidth());
	ofSetColor(obj.getStrokeColor());

	line.addVertex(obj.getPosition());
	line.addVertex(obj.getDimensions() + obj.getPosition());
	line.draw();

	ofPopStyle();
}

void DessinVec::draw_square(VecObject obj) const {
	int formatX = obj.getDimensions().x;
	int formatY = obj.getDimensions().y;

	if (formatX < 0 && formatY < 0) {
		if (abs(formatX) > abs(formatY)) {
			formatY = formatX;
		}
		else {
			formatX = formatY;
		}
	}
	else if ((formatX > 0 && formatY < 0) || (formatX < 0 && formatY > 0)) {
		if (abs(formatX) > abs(formatY)) {
			formatY = -formatX;
		}
		else {
			formatX = -formatY;
		}
	}
	else {
		if (formatX > formatY) {
			formatY = formatX;
		}
		else {
			formatX = formatY;
		}
	}

	ofPushStyle();

	ofSetLineWidth(obj.getStrokeWidth());
	ofSetColor(obj.getFillColor());

	ofDrawRectangle(obj.getPosition(), formatX, formatY);

	ofNoFill();
	ofSetColor(obj.getStrokeColor());
	ofDrawRectangle(obj.getPosition(), formatX, formatY);

	ofPopStyle();
}

void DessinVec::draw_circle(VecObject obj) const {

	int radius = sqrt(pow(obj.getDimensions().x, 2) + pow(obj.getDimensions().y, 2));

	ofPushStyle();
	ofFill();

	ofSetCircleResolution(100);

	ofSetLineWidth(obj.getStrokeWidth());
	ofSetColor(obj.getFillColor());

	ofDrawCircle(obj.getPosition(), radius);

	ofNoFill();
	ofSetColor(obj.getStrokeColor());
	ofDrawCircle(obj.getPosition(), radius);

	ofPopStyle();
}

void DessinVec::draw_ellipse(VecObject obj) const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(obj.getStrokeWidth());
	ofSetColor(obj.getFillColor());

	ofDrawEllipse(obj.getPosition(), 2 * obj.getDimensions().x, 2 * obj.getDimensions().y);

	ofNoFill();
	ofSetColor(obj.getStrokeColor());
	ofDrawEllipse(obj.getPosition(), 2 * obj.getDimensions().x, 2 * obj.getDimensions().y);

	ofPopStyle();
}

DessinVec::~DessinVec() {
	//std::free(shapes);
}
