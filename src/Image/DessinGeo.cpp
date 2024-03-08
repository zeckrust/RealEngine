#include "DessinGeo.h"
#include "../gui/Gui.h"

DessinGeo::DessinGeo() {

}

void DessinGeo::setup() {
	mode = Geotype::none;

	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = mouse_last_x = mouse_last_y = 0;
	mouse_pressed = false;

	compteur_prism = 0;
	compteur_cylinder = 0;

	default_pos_z = 15;
	default_dim_z = 40;


	gui = Gui::getInstance();

	scene3DShape = gui->getScene3DShape();
	fbo.allocate(scene3DShape.getWidth(), scene3DShape.getHeight(), GL_RGBA);
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();

	camera_x_offset = 0.0f;
	camera_y_offset = 0.0f;
	camera_z_offset = 200.0f;
	target_x_offset = 0.0f;
	target_y_offset = 0.0f;
	target_z_offset = 0.0f;

	move_step = 2;

	camera_position = { camera_x_offset, camera_y_offset, camera_z_offset };
	camera_target = { target_x_offset, target_y_offset, target_z_offset };

	camera_near = 50.0f;
	camera_far = 1750.0f;

	camera_fov = 60.0f;

	camera.setupPerspective(false, camera_fov, camera_near, camera_far, ofVec2f(0, 0));

	camera.setPosition(camera_position);
	camera.lookAt(camera_target);

	histogramPerspective.setup(fbo, scene3DShape.getY());

	transformMatrix.makeIdentityMatrix();
	lastTransformMatrixInversed.makeIdentityMatrix();
	yaw.makeIdentityMatrix();
	pitch.makeIdentityMatrix();
	roll.makeIdentityMatrix();
	originRotation.makeIdentityMatrix();
}

void DessinGeo::update()
{
	scene3DShape = gui->getScene3DShape();
	bool hasPositionChanged = scene3DShape.getPosition() != oldScene3dShape.getPosition();
	bool hasWidthChanged = scene3DShape.getWidth() != oldScene3dShape.getWidth();
	bool hasHeightChanged = scene3DShape.getHeight() != oldScene3dShape.getHeight();

	if (hasPositionChanged || hasWidthChanged || hasHeightChanged) {
		fbo.allocate(scene3DShape.getWidth(), scene3DShape.getHeight(), GL_RGBA);
		redraw();
	}

	oldScene3dShape = scene3DShape;
	histogramPerspective.update(fbo, scene3DShape.getY());
}

void DessinGeo::reset()
{
	shapes.clear();
}

void DessinGeo::draw()
{
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	fbo.draw(scene3DShape.getPosition().x, scene3DShape.getPosition().y);
	ofPopStyle();
	if (gui->getIsHistogramShowing()) {
		histogramPerspective.draw();
	}
}

void DessinGeo::redraw() {
	fbo.begin();
	ofClear(0, 0, 0, 0);
	draw_buffer();
	fbo.end();
}

void DessinGeo::draw_buffer() {
	camera.begin();
	ofNode node;
	node.setPosition(0, 0, 0);
	node.draw();
	for (auto& shape : shapes)
	{
		shape->draw();
	}
	camera.end();
}

void DessinGeo::mousePressed(ofMouseEventArgs& args)
{
	is_drawing_mode = gui->getSelectedUserMode() == DRAWING;
	is_transform_mode = gui->getSelectedUserMode() == TRANSFORM;
	bool isInsideScene = scene3DShape.inside(args.x, args.y);
	bool isDrawingToolSelected = gui->getTypeGeometrique() != Geotype::none;

	mode = Geotype::none;

	if (isInsideScene) {
		mouse_pressed = true;

		mouse_press_x = args.x - scene3DShape.getPosition().x;
		mouse_press_y = -(args.y - (scene3DShape.getPosition().y + scene3DShape.getHeight()/2));
		mouse_current_x = mouse_press_x;
		mouse_current_y = mouse_press_y;
		mouse_last_x = mouse_current_x;
		mouse_last_y = mouse_current_y;
    
		if (is_drawing_mode) {
			if (isDrawingToolSelected) {
				mode = gui->getTypeGeometrique();
			}
		}
	}
}

void DessinGeo::mouseReleased(ofMouseEventArgs& args)
{
	if (mouse_pressed) {
		if (is_drawing_mode && mode != Geotype::none) {
			add_geo_shape();
		}
	}
}

void DessinGeo::mouseDragged(ofMouseEventArgs& args) {
	if (mouse_pressed) {

		mouse_current_x = args.x - scene3DShape.getPosition().x;
		mouse_current_y = -(args.y - (scene3DShape.getPosition().y + scene3DShape.getHeight()/2));

		if (is_drawing_mode) {

			ofPushStyle();
			fbo.begin();
			ofClear(0, 0, 0, 0);
			draw_buffer();

			GeObject obj = GeObject(mode, gui->getLineWidth(), gui->getLineColor(), gui->getFillColor());

			obj.setPosition(glm::vec3(mouse_press_x, mouse_press_y, default_pos_z));
			obj.setDimensions(glm::vec3(mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y, default_dim_z));

			obj.draw();

			fbo.end();
			ofPopStyle();
		}
	}
}

void DessinGeo::add_geo_shape() {
	shapes.push_back(new GeObject(mode, gui->getLineWidth(), gui->getLineColor(), gui->getFillColor()));

	shapes.back()->setPosition(glm::vec3(mouse_press_x, mouse_press_y, default_pos_z));
	shapes.back()->setDimensions(glm::vec3(mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y, default_dim_z));

	mouse_pressed = false;
	histogramPerspective.update(fbo, scene3DShape.getY());

	std::string name;

	switch (mode)
	{
		case Geotype::none:
			break;
		case Geotype::cylindre:
			name = "Cylinder";
			name += to_string(compteur_cylinder);
			compteur_cylinder++;
			break;
		case Geotype::rectangulaire:
			name = "RecPrism";
			name += to_string(compteur_prism);
			compteur_prism++;
			break;
		default:
			break;
	}

	gui->createSceneElement(name, shapes.back());
}

void DessinGeo::deleteObject(SceneObject* obj) {
	auto shapes_it = std::find(shapes.begin(), shapes.end(), obj);
	if (shapes_it != shapes.end()) {
		shapes.erase(shapes_it);
		redraw();
	}
}

void DessinGeo::moveLeft(void) {
	camera_x_offset = camera_x_offset - move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	redraw();
}

void DessinGeo::moveRight(void) {
	camera_x_offset = camera_x_offset + move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	redraw();
}

void DessinGeo::moveUp(void) {
	camera_y_offset = camera_y_offset + move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	redraw();
}

void DessinGeo::moveDown(void) {
	camera_y_offset = camera_y_offset - move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	redraw();
}

void DessinGeo::moveForward(void) {
	camera_z_offset = camera_z_offset - move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	redraw();
}

void DessinGeo::moveBackward(void) {
	camera_z_offset = camera_z_offset + move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	redraw();
}

void DessinGeo::tiltUp(void) {
	target_y_offset = target_y_offset + move_step;
	camera_target = { target_x_offset, target_y_offset, target_z_offset };
	camera.lookAt(camera_target);
	redraw();
}

void DessinGeo::tiltDown(void) {
	target_y_offset = target_y_offset - move_step;
	camera_target = { target_x_offset, target_y_offset, target_z_offset };
	camera.lookAt(camera_target);
	redraw();
}

void DessinGeo::panLeft(void) {
	target_x_offset = target_x_offset - move_step;
	camera_target = { target_x_offset, target_y_offset, target_z_offset };
	camera.lookAt(camera_target);
	redraw();
}

void DessinGeo::panRight(void) {
	target_x_offset = target_x_offset + move_step;
	camera_target = { target_x_offset, target_y_offset, target_z_offset };
	camera.lookAt(camera_target);
	redraw();
}

void DessinGeo::rollLeft(void) {
	target_z_offset = target_z_offset + move_step;
	camera_target = { target_x_offset, target_y_offset, target_z_offset };
	camera.lookAt(camera_target);
	redraw();
}

void DessinGeo::rollRight(void) {
	target_z_offset = target_z_offset - move_step;
	camera_target = { target_x_offset, target_y_offset, target_z_offset };
	camera.lookAt(camera_target);
	redraw();
}

DessinGeo::~DessinGeo() {

}