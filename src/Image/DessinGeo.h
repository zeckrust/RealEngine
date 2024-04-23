#pragma once
#include "ofMain.h"
#include "VecObject.h"
#include "../gui/Histogram.h"
#include "GeObject.h"
#include "../gui/scene/SceneElement.h"
#include "Drawer.h"
#include "Skybox.h"

class Gui;

class DessinGeo : public Drawer
{
	public :
		DessinGeo();
		void setup(std::vector<SceneObject*>* _shapes);
		void update();
		void draw();
		void draw_buffer();
		void redraw();
		void reset();
		void add_shape();

		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);
		void mouseDragged(ofMouseEventArgs& args);

		void moveLeft(void);
		void moveRight(void);
		void moveUp(void);
		void moveDown(void);
		void moveForward(void);
		void moveBackward(void);
		void tiltUp(void);
		void tiltDown(void);
		void panRight(void);
		void panLeft(void);
		void rollRight(void);
		void rollLeft(void);

		void deleteObject(SceneObject* obj);

		~DessinGeo();

	private:
		void setup_camera();
		void setup_skybox();
		void setup_matrix();
		Geotype mode;
		Gui* gui = nullptr;

		int mouse_press_x;
		int mouse_press_y;

		int mouse_current_x;
		int mouse_current_y;

		int mouse_last_x;
		int mouse_last_y;

		bool mouse_pressed;
		bool is_drawing_mode;
		bool is_transform_mode;


		int default_dim_z;
		int default_pos_z;

		uint32_t compteur_cylinder;
		uint32_t compteur_prism;

		ofFbo fbo;
		ofRectangle scene3DShape;
		ofRectangle oldScene3dShape;

		Histogram histogramPerspective;

		ofCamera camera;
		ofVec3f camera_position;
		ofVec3f camera_target;
		float camera_near;
		float camera_far;
		float camera_fov;
		float camera_x_offset;
		float camera_y_offset;
		float camera_z_offset;
		float target_x_offset;
		float target_y_offset;
		float target_z_offset;

		float move_step;

		Skybox skybox;

		ofImage filtered_image = ofImage();

		ofMatrix4x4 transformMatrix;
		ofMatrix4x4 lastTransformMatrixInversed;
		ofMatrix4x4 yaw;
		ofMatrix4x4 pitch;
		ofMatrix4x4 roll;
		ofMatrix4x4 originRotation;

		vector<SceneElement*> sceneElements;
};