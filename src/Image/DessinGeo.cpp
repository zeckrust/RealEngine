#include "DessinGeo.h"
#include "../gui/Gui.h"

DessinGeo::DessinGeo() {

}

void DessinGeo::setup(std::vector<SceneObject*>* _shapes) {
	shapes = _shapes;
	mode = Geotype::none;

	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = mouse_last_x = mouse_last_y = 0;
	mouse_pressed = false;
	planeMode = false;

	compteur_prism = 0;
	compteur_cylinder = 0;
	compteur_releif_effect = 0;

	default_pos_z = 15;
	default_dim_z = 40;

	compteur_plane = 0;

	gui = Gui::getInstance();

	scene3DShape = gui->getScene3DShape();
	fbo.allocate(scene3DShape.getWidth(), scene3DShape.getHeight(), GL_RGBA);
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();

	setup_camera(); // sets up skybox too

	histogramPerspective.setup(fbo, scene3DShape.getY());

	setup_matrix();
}

void DessinGeo::setup_camera() {
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

	setup_skybox();
}

void DessinGeo::setup_skybox() {
	ofImage skybox_image;
	skybox_image.load("skybox\\skybox1.png");
	skybox.set_texture(skybox_image);
	skybox_image.clear();
	skybox.setPosition(camera.getPosition());
	skybox.setup();
}

void DessinGeo::setup_matrix() {
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
		histogramPerspective.allocatePixelsFBO(&fbo);
		redraw();
	}

	oldScene3dShape = scene3DShape;
}

void DessinGeo::reset()
{
	shapes->clear();
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
	if (gui->getIsSkyboxPerspectiveChanged()) {
		skybox.set_texture(gui->getSkyboxImage());
		gui->setIsSkyboxPerspectiveChanged(false);
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
	skybox.draw_mesh();
	for (auto& shape : *shapes)
	{
		shape->draw();
	}
	if (ctrl_pts.size() > 0) {
		ofPushStyle();
		ofFill();
		ofSetColor(255, 0, 0);
		ofSpherePrimitive sphere;
		sphere.set(8.0f, 100);
		for (ofVec3f pts : ctrl_pts) {
			sphere.setPosition(pts);
			sphere.draw();
		}
		ofPopStyle();
	}
	camera.end();
}

void DessinGeo::mousePressed(ofMouseEventArgs& args)
{
	is_drawing_mode = gui->getSelectedUserMode() == DRAWING;
	is_transform_mode = gui->getSelectedUserMode() == TRANSFORM;
	bool isInsideScene = scene3DShape.inside(args.x, args.y);
	bool isDrawingToolSelected = (gui->getTypeGeometrique() != Geotype::none) || (gui->getPlaneMode());

	mode = Geotype::none;
	planeMode = false;

	if (isInsideScene) {
		mouse_pressed = true;

		mouse_press_x = args.x - scene3DShape.getPosition().x;
		mouse_press_y = -(args.y - (scene3DShape.getPosition().y + scene3DShape.getHeight()/2));
		mouse_current_x = mouse_press_x;
		mouse_current_y = mouse_press_y;
		mouse_last_x = mouse_current_x;
		mouse_last_y = mouse_current_y;
		sceneElements = gui->getSelectedElements();
    
		if (is_drawing_mode) {
			if (isDrawingToolSelected) {
				mode = gui->getTypeGeometrique();
				planeMode = gui->getPlaneMode();
			}
			if (gui->getIsImageImported()) {
				switch (gui->getCurrentFilter()) {
				case GRAY:
					filtered_image = Filter::toGray(gui->getImportedImage());
					break;
				case KELVIN:
					filtered_image = Filter::toKelvin(gui->getImportedImage());
					break;
				case NASHVILLE:
					filtered_image = Filter::toNashville(gui->getImportedImage());
					break;
				case REINHARD:
					filtered_image = Filter::toTonalMappingReinhard(gui->getImportedImage());
					break;
				case EXPOSITION2:
					filtered_image = Filter::toTonalMappingExposition2(gui->getImportedImage());
					break;
				case EXPOSITION05:
					filtered_image = Filter::toTonalMappingExposition05(gui->getImportedImage());
					break;
				default:
					filtered_image = gui->getImportedImage();
					break;
				}
			}
		}
	}
}

void DessinGeo::mouseReleased(ofMouseEventArgs& args)
{
	if (mouse_pressed) {
		if (is_drawing_mode) {
			if (mode != Geotype::none) {
				add_shape();
			}
			else if (planeMode) {
				add_plane();
			}
		}
		sceneElements.clear();
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

			if (mode == Geotype::relief_effect) {
				ofSetColor(255, 255, 255, 255);
				gui->getImportedImage().draw(glm::vec2(mouse_press_x, -mouse_press_y), mouse_current_x - mouse_press_x, -(mouse_current_y - mouse_press_y));
			}
			else {
				GeObject obj = GeObject(mode, gui->getLineWidth(), gui->getLineColor(), gui->getFillColor());
				if (gui->getIsImageImported()) {
					obj.setTexture(filtered_image);
				}

				obj.setPosition(glm::vec3(mouse_press_x, mouse_press_y, -1 * gui->getDepth()));
				obj.setDimensions(glm::vec3(mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y, default_dim_z));

				obj.draw();
			}

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
				if (y_cond) {
					roll.set(
						cos(y * PI / 180), 0, sin(y * PI / 180), 0,
						0, 1, 0, 0,
						-sin(y * PI / 180), 0, cos(y * PI / 180), 0,
						0, 0, 0, 1
					);
				}
				if (x_cond) {
					pitch.set(
						1, 0, 0, 0,
						0, cos(x * PI / 180), -sin(x * PI / 180), 0,
						0, sin(x * PI / 180), cos(x * PI / 180), 0,
						0, 0, 0, 1
					);
				}
				if (z_cond) {
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
					exp(x / 100), 0, 0, 0,
					0, exp(y / 100), 0, 0,
					0, 0, exp(z / 100), 0,
					0, 0, 0, 1
				);
				break;
			default:
				break;
			}
			mouse_last_x = mouse_current_x;
			mouse_last_y = mouse_current_y;
			lastTransformMatrixInversed = transformMatrix.getInverse();

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
}

void DessinGeo::add_shape() {
	GeObject *new_shape = new GeObject(mode, gui->getLineWidth(), gui->getLineColor(), gui->getFillColor());

	if (gui->getIsImageImported()) {
		new_shape->setTexture(filtered_image);
	}

	shapes->push_back(new_shape);

	shapes->back()->setPosition(glm::vec3(mouse_press_x, mouse_press_y, -1 * gui->getDepth()));
	shapes->back()->setDimensions(glm::vec3(mouse_current_x - mouse_press_x, mouse_current_y - mouse_press_y, default_dim_z));

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

			if (gui->getIsImageImported()) {
				gui->setIsImageImported(false);
			}
			break;
		case Geotype::relief_effect:
			name = "ReliefEffect";
			name += to_string(compteur_releif_effect);
			compteur_releif_effect++;

			if (gui->getIsImageImported()) {
				gui->setIsImageImported(false);
			}
		default:
			break;
	}

	gui->createSceneElement(name, shapes->back());
}

void DessinGeo::add_plane() {
	ctrl_pts.push_back(ofVec3f(mouse_press_x, mouse_press_y, -1 * gui->getDepth()));
	mouse_pressed = false;
	if (ctrl_pts.size() > 3) {
		shapes->push_back(new BezierPlane(ctrl_pts.at(0), ctrl_pts.at(1), ctrl_pts.at(2), ctrl_pts.at(3), gui->getLineWidth(), gui->getLineColor(), gui->getFillColor()));
		histogramPerspective.update(fbo, scene3DShape.getY());
		std::string name = "Bezier plane";
		name += to_string(compteur_plane);
		compteur_plane++;
		gui->createSceneElement(name, shapes->back());
		ctrl_pts.clear();
	}
}

void DessinGeo::deleteObject(SceneObject* obj) {
	auto shapes_it = std::find(shapes->begin(), shapes->end(), obj);
	if (shapes_it != shapes->end()) {
		shapes->erase(shapes_it);
		redraw();
	}
}

void DessinGeo::moveLeft(void) {
	camera_x_offset = camera_x_offset - move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	skybox.setPosition(glm::vec3(camera_x_offset, camera_y_offset, camera_z_offset));
	redraw();
}

void DessinGeo::moveRight(void) {
	camera_x_offset = camera_x_offset + move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	skybox.setPosition(glm::vec3(camera_x_offset, camera_y_offset, camera_z_offset));
	redraw();
}

void DessinGeo::moveUp(void) {
	camera_y_offset = camera_y_offset + move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	skybox.setPosition(glm::vec3(camera_x_offset, camera_y_offset, camera_z_offset));
	redraw();
}

void DessinGeo::moveDown(void) {
	camera_y_offset = camera_y_offset - move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	skybox.setPosition(glm::vec3(camera_x_offset, camera_y_offset, camera_z_offset));
	redraw();
}

void DessinGeo::moveForward(void) {
	camera_z_offset = camera_z_offset - move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	skybox.setPosition(glm::vec3(camera_x_offset, camera_y_offset, camera_z_offset));
	redraw();
}

void DessinGeo::moveBackward(void) {
	camera_z_offset = camera_z_offset + move_step;
	camera.setPosition(camera_x_offset, camera_y_offset, camera_z_offset);
	skybox.setPosition(glm::vec3(camera_x_offset, camera_y_offset, camera_z_offset));
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