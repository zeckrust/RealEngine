#include "DessinVec.h"
#include "../gui/Gui.h"

DessinVec::DessinVec(){

}

void DessinVec::setup()
{
	mode = Primitype::none;

	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = mouse_last_x = mouse_last_y = 0;
	mouse_pressed = false;

	compteur_square = 0;
	compteur_circle = 0;
	compteur_ellipse = 0;
	compteur_rectangle = 0;
	compteur_line = 0;
	compteur_image = 0;

	compteur_stage_1 = 0;
	compteur_stage_2 = 0;

	gui = Gui::getInstance();

	scene2DShape = gui->getScene2DShape();
	fbo.allocate(scene2DShape.getHeight(), scene2DShape.getWidth(), GL_RGBA);
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();


	camera.enableOrtho();
	camera_offset = 20.0f;
	camera_position = { 0.0f, 0.0f, camera_offset};
	camera_target =   { 0.0f, 0.0f, 0.0f };
	camera.setPosition(camera_position);
	camera.lookAt(camera_target);

	histogramOrthogonal.setup(fbo, scene2DShape.getY());


	transformMatrix.makeIdentityMatrix();
	lastTransformMatrixInversed.makeIdentityMatrix();
	yaw.makeIdentityMatrix();
	pitch.makeIdentityMatrix();
	roll.makeIdentityMatrix();
	originRotation.makeIdentityMatrix();
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
	histogramOrthogonal.update(fbo, scene2DShape.getY());
}

void DessinVec::reset()
{
	shapes.clear();
}

void DessinVec::add_vector_shape() 
{
	if (mode == Primitype::image) {
		shapes.push_back(new VecObject(mode, gui->getLineWidth(), gui->getLineColor(), gui->getFillColor(), gui->getImportedImage()));
	}
	else {
		shapes.push_back(new VecObject(mode, gui->getLineWidth(), gui->getLineColor(), gui->getFillColor()));
	}

	shapes.back()->setPosition(glm::vec3(mouse_press_x, mouse_press_y, 0));
	shapes.back()->setDimensions(glm::vec3(mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y, 0));

	mouse_pressed = false;
	histogramOrthogonal.update(fbo, scene2DShape.getY());

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
		//shapes.back()->setImage(gui->getImportedImage());
		gui->setIsImageImported(false);
		name = "Image";
		name += to_string(compteur_image);
		compteur_image++;
		break;
	case Primitype::stage1:
		name = "Stage1_";
		name += to_string(compteur_stage_1);
		compteur_stage_1++;
		break;
	case Primitype::stage2:
		name = "Stage2_";
		name += to_string(compteur_stage_2);
		compteur_stage_2++;
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
	is_drawing_mode = gui->getSelectedUserMode() == DRAWING;
	is_transform_mode = gui->getSelectedUserMode() == TRANSFORM;
	is_scroll_clicked = args.button == OF_MOUSE_BUTTON_MIDDLE;
	bool isInsideScene = scene2DShape.inside(args.x, args.y);
	bool isDrawingToolSelected = gui->getTypePrimitive() != Primitype::none;

	mode = Primitype::none;

	mouse_press_x = args.x - scene2DShape.getPosition().x - scene2DShape.getWidth() / 2;
	mouse_press_y = -(args.y - scene2DShape.getPosition().y - scene2DShape.getHeight() / 2);
	mouse_current_x = args.x - scene2DShape.getPosition().x - scene2DShape.getWidth() / 2;
	mouse_current_y = -(args.y - scene2DShape.getPosition().y - scene2DShape.getHeight() / 2);

	if (isInsideScene) {
		mouse_pressed = true;
		mouse_last_x = mouse_current_x;
		mouse_last_y = mouse_current_y;
		if (is_drawing_mode) {
			if (gui->getIsImageImported()) {
				mode = Primitype::image;
			}
			else if (isDrawingToolSelected) {
				mode = gui->getTypePrimitive();
			}
		}
	}
}

void DessinVec::mouseReleased(ofMouseEventArgs& args)
{
	if (mouse_pressed && !is_scroll_clicked) {
		if (is_drawing_mode && mode != Primitype::none) {
			add_vector_shape();
		}
	}
	is_scroll_clicked = false;
}

void DessinVec::mouseDragged(ofMouseEventArgs& args)
{
	if (mouse_pressed && !is_scroll_clicked) {
		mouse_current_x = args.x - scene2DShape.getPosition().x - scene2DShape.getWidth() / 2;
		mouse_current_y = -(args.y - scene2DShape.getPosition().y - scene2DShape.getHeight() / 2);
		if (is_drawing_mode) {
			int formatX = 0;
			int formatY = 0;
			int radius = 0;

			ofPushStyle();
			fbo.begin();
			ofClear(0, 0, 0, 0);
			draw_buffer();
			camera.begin();
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

				ofDrawEllipse(glm::vec2(mouse_press_x, mouse_press_y), 2 * (mouse_current_x - mouse_press_x), 2 * (mouse_current_y - mouse_press_y));

				ofNoFill();
				ofSetColor(gui->getLineColor());
				ofDrawEllipse(glm::vec2(mouse_press_x, mouse_press_y), 2 * (mouse_current_x - mouse_press_x), 2 * (mouse_current_y - mouse_press_y));

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

			case Primitype::stage1:
				dynamic_stage_1();
				break;
			case Primitype::stage2:
				dynamic_stage_2();
				break;
			case Primitype::image:
				ofSetColor(255, 255, 255, 255);
				gui->getImportedImage().draw(glm::vec2(mouse_press_x, mouse_press_y), mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y);
				break;
			default:
				break;
			}
			camera.end();
			fbo.end();
			ofPopStyle();
		}
		else if (is_transform_mode) {
			bool x_cond = *(gui->getPropertiesPanelBtnStates());
			bool y_cond = *(gui->getPropertiesPanelBtnStates() + 1);
			bool z_cond = *(gui->getPropertiesPanelBtnStates() + 2);

			float x = x_cond ? mouse_current_x - mouse_last_x : 0;
			float y = y_cond ? mouse_current_y - mouse_last_y : 0;
			float z = z_cond ? mouse_current_x - mouse_last_x : 0;


			switch (gui->getSelectedTransformTool()) {
				case TRANSLATION:
					transformMatrix.set(
						1, 0, 0, x,
						0, 1, 0, y,
						0, 0, 1, z,
						0, 0, 0, 1
					);
					break;
				case ROTATION:
					if (*(gui->getPropertiesPanelBtnStates())) {
						roll.set(
							cos(y * PI / 180), 0, sin(y * PI / 180), 0,
							0, 1, 0, 0,
							-sin(y * PI / 180), 0, cos(y * PI / 180), 0,
							0, 0, 0, 1
						);
					}
					if (*(gui->getPropertiesPanelBtnStates() + 1)) {
						pitch.set(
							1, 0, 0, 0,
							0, cos(x * PI / 180), -sin(x * PI / 180), 0,
							0, sin(x * PI / 180), cos(x * PI / 180), 0,
							0, 0, 0, 1
						);
					}
					if (*(gui->getPropertiesPanelBtnStates() + 2)) {
						roll.set(
							cos(z * PI / 180), -sin(z * PI / 180), 0, 0,
							sin(z * PI / 180), cos(z * PI / 180), 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1
						);
					}
					transformMatrix = roll * pitch * yaw;
					break;
				case SCALE:
					transformMatrix.set(
						exp(x/100), 0, 0, 0,
						0, exp(y/100), 0, 0,
						0, 0, exp(z/100), 0,
						0, 0, 0, 1
					);
					break;
				default:
					break;
			}
			mouse_last_x = mouse_current_x;
			mouse_last_y = mouse_current_y;
			lastTransformMatrixInversed = transformMatrix.getInverse();

			sceneElements = gui->getSelectedElements();
			SceneObject* obj;
			ofVec3f pos;
			ofVec3f dim;
			ofMatrix4x4 mat;
			for (int i = 0; i < size(sceneElements); i++) {
				obj = sceneElements.at(i)->getSceneObjectPtr();
				mat = obj->getTransformMatrix();

				if (gui->getSelectedTransformTool() == ROTATION) {
					pos = mat * obj->getPosition();
					originRotation.set(
						1, 0, 0, -(pos.x),
						0, 1, 0, -(pos.y),
						0, 0, 1, -(pos.z),
						0, 0, 0, 1
					);
					transformMatrix = originRotation.getInverse() * transformMatrix * originRotation;
				}

				ofMatrix4x4 newMatrix = transformMatrix * mat;

				obj->setTransformMatrix(newMatrix);
			}
			redraw();
		}
	}
	if (is_scroll_clicked) {
		mouse_current_y = -(args.y - scene2DShape.getPosition().y - scene2DShape.getHeight() / 2);
		camera_offset = camera_offset + (mouse_current_y - mouse_last_y);
		camera_offset = camera_offset < 5.0f ? 5.0f : camera_offset;

		camera.setPosition(0.0f, 0.0f, camera_offset);

		mouse_last_y = mouse_current_y;
		redraw();
	}
}

void DessinVec::draw()
{
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	fbo.draw(scene2DShape.getPosition().x, scene2DShape.getPosition().y);
	ofPopStyle();
	if (gui->getIsHistogramShowing()) {
		histogramOrthogonal.draw();
	}
}

void DessinVec::redraw() {
	fbo.begin();
	ofClear(0, 0, 0, 0);
	draw_buffer();
	fbo.end();
}

void DessinVec::draw_buffer() {
	camera.begin();
	for (auto & shape : shapes)
	{
		shape->draw();
	}
	camera.end();
}

void DessinVec::dynamic_stage_1() const {
	ofFill();
	ofSetLineWidth(gui->getLineWidth());
	ofSetColor(gui->getFillColor());

	glm::vec3 v0 = glm::vec3(mouse_press_x, mouse_press_y, 0);
	glm::vec3 v1 = glm::vec3(mouse_current_x, mouse_press_y, 0);
	glm::vec3 v2 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.9), mouse_press_y + ((mouse_current_y - mouse_press_y) * 0.5), 0);
	glm::vec3 v3 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.95), mouse_current_y, 0);
	glm::vec3 v4 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.5), mouse_press_y + ((mouse_current_y - mouse_press_y) * 0.9), 0);
	glm::vec3 v5 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.05), mouse_current_y, 0);
	glm::vec3 v6 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.1), mouse_press_y + ((mouse_current_y - mouse_press_y) * 0.5), 0);
	glm::vec3 v7 = glm::vec3(mouse_press_x, mouse_press_y, 0);

	ofBeginShape();

	ofVertex(v0);
	ofVertex(v1);
	ofVertex(v2);
	ofVertex(v3);
	ofVertex(v4);
	ofVertex(v5);
	ofVertex(v6);
	ofVertex(v7);

	ofEndShape(true);

	ofNoFill();
	ofSetColor(gui->getLineColor());
	ofBeginShape();

	ofVertex(v0);
	ofVertex(v1);
	ofVertex(v2);
	ofVertex(v3);
	ofVertex(v4);
	ofVertex(v5);
	ofVertex(v6);
	ofVertex(v7);

	ofEndShape(true);
}

void DessinVec::dynamic_stage_2() const {
	ofFill();
	ofSetLineWidth(gui->getLineWidth());
	ofSetColor(gui->getFillColor());

	glm::vec3 v0 = glm::vec3(mouse_press_x, mouse_press_y, 0);
	glm::vec3 v1 = glm::vec3(mouse_current_x, mouse_press_y, 0);

	glm::vec3 v2 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.9), mouse_press_y + ((mouse_current_y - mouse_press_y) * 0.65), 0);
	glm::vec3 v3 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.65), mouse_press_y + ((mouse_current_y - mouse_press_y) * 0.65), 0);

	glm::vec3 v4 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.65), mouse_current_y, 0);
	glm::vec3 v5 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.35), mouse_current_y, 0);

	glm::vec3 v6 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.35), mouse_press_y + ((mouse_current_y - mouse_press_y) * 0.65), 0);
	glm::vec3 v7 = glm::vec3(mouse_press_x + ((mouse_current_x - mouse_press_x) * 0.1), mouse_press_y + ((mouse_current_y - mouse_press_y) * 0.65), 0);

	glm::vec3 v8 = glm::vec3(mouse_press_x, mouse_press_y, 0);

	ofBeginShape();

	ofVertex(v0);
	ofVertex(v1);
	ofVertex(v2);
	ofVertex(v3);
	ofVertex(v4);
	ofVertex(v5);
	ofVertex(v6);
	ofVertex(v7);
	ofVertex(v8);

	ofEndShape(true);

	ofNoFill();
	ofSetColor(gui->getLineColor());
	ofBeginShape();

	ofVertex(v0);
	ofVertex(v1);
	ofVertex(v2);
	ofVertex(v3);
	ofVertex(v4);
	ofVertex(v5);
	ofVertex(v6);
	ofVertex(v7);
	ofVertex(v8);

	ofEndShape(true);

}

DessinVec::~DessinVec() {
	//std::free(shapes);
}
