#include "DessinVec.h"
#include "../apps/RealEngine/src/gui/Gui.h"

DessinVec::DessinVec(){

}

void DessinVec::setup()
{
	buffer_count = 100;
	buffer_head = 0;
	buffer_size = buffer_count * sizeof(PrimitiveVectorielle);

	mode = Primitype::none;

	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;
	mouse_pressed = false;

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
		fbo.begin();
		ofClear(0, 0, 0, 0);
		fbo.end();
	}

	oldScene2dShape = scene2DShape;
}

void DessinVec::reset()
{
	shapes.clear();
	buffer_head = 0;
}

void DessinVec::add_vector_shape() 
{
	shapes.push_back(new PrimitiveVectorielle);

	shapes.at(buffer_head)->type = mode;
	shapes.at(buffer_head)->position1[0] = mouse_press_x;
	shapes.at(buffer_head)->position1[1] = mouse_press_y;
	shapes.at(buffer_head)->position2[0] = mouse_current_x;
	shapes.at(buffer_head)->position2[1] = mouse_current_y;
	shapes.at(buffer_head)->stroke_color = gui->getLineColor();
	shapes.at(buffer_head)->fill_color = gui->getFillColor();
	shapes.at(buffer_head)->stroke_width = gui->getLineWidth();

	buffer_head++;

	if (buffer_head >= buffer_count)
	{
		buffer_head = 0;
	}
	mouse_pressed = false;
}

void DessinVec::mousePressed(ofMouseEventArgs& args)
{
	if (gui->getSelectedUserMode() == DRAWING && scene2DShape.inside(args.x, args.y)) {
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

void DessinVec::draw_buffer() {
	for (auto & shape : shapes)
	{
		switch (shape->type)
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

void DessinVec::draw_rectangle(PrimitiveVectorielle prim) const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(prim.stroke_width);
	ofSetColor(prim.fill_color);

	ofDrawRectangle(glm::vec2(prim.position1[0], prim.position1[1]), prim.position2[0] - prim.position1[0], prim.position2[1] - prim.position1[1]);

	ofNoFill();
	ofSetColor(prim.stroke_color);
	ofDrawRectangle(glm::vec2(prim.position1[0], prim.position1[1]), prim.position2[0] - prim.position1[0], prim.position2[1] - prim.position1[1]);

	ofPopStyle();
}

void DessinVec::draw_line(PrimitiveVectorielle prim) const {
	ofPolyline line;

	ofPushStyle();

	ofSetLineWidth(prim.stroke_width);
	ofSetColor(prim.stroke_color);

	line.addVertex(prim.position1[0], prim.position1[1]);
	line.addVertex(prim.position2[0], prim.position2[1]);
	line.draw();

	ofPopStyle();
}

void DessinVec::draw_square(PrimitiveVectorielle prim) const {
	int formatX = prim.position2[0] - prim.position1[0];
	int formatY = prim.position2[1] - prim.position1[1];

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

	ofSetLineWidth(prim.stroke_width);
	ofSetColor(prim.fill_color);

	ofDrawRectangle(glm::vec2(prim.position1[0], prim.position1[1]), formatX, formatY);

	ofNoFill();
	ofSetColor(prim.stroke_color);
	ofDrawRectangle(glm::vec2(prim.position1[0], prim.position1[1]), formatX, formatY);

	ofPopStyle();
}

void DessinVec::draw_circle(PrimitiveVectorielle prim) const {

	int radius = sqrt(pow(prim.position2[0] - prim.position1[0], 2) + pow(prim.position2[1] - prim.position1[1], 2));

	ofPushStyle();
	ofFill();

	ofSetCircleResolution(100);

	ofSetLineWidth(prim.stroke_width);
	ofSetColor(prim.fill_color);

	ofDrawCircle(glm::vec2(prim.position1[0], prim.position1[1]), radius);

	ofNoFill();
	ofSetColor(prim.stroke_color);
	ofDrawCircle(glm::vec2(prim.position1[0], prim.position1[1]), radius);

	ofPopStyle();
}

void DessinVec::draw_ellipse(PrimitiveVectorielle prim) const {
	ofPushStyle();

	ofFill();
	ofSetLineWidth(prim.stroke_width);
	ofSetColor(prim.fill_color);

	ofDrawEllipse(glm::vec2(prim.position1[0], prim.position1[1]), 2 * (prim.position2[0] - prim.position1[0]), 2 * (prim.position2[1] - prim.position1[1]));

	ofNoFill();
	ofSetColor(prim.stroke_color);
	ofDrawEllipse(glm::vec2(prim.position1[0], prim.position1[1]), 2 * (prim.position2[0] - prim.position1[0]), 2 * (prim.position2[1] - prim.position1[1]));

	ofPopStyle();
}

DessinVec::~DessinVec() {
	//std::free(shapes);
}
