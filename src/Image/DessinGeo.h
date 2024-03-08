#pragma once
#include "ofMain.h"
#include "VecObject.h"
#include "../gui/Histogram.h"
#include "GeObject.h"
#include "../gui/scene/SceneElement.h"

class Gui;

class DessinGeo
{
	public :
		DessinGeo();
		void setup();
		void update();
		void draw();
		void draw_buffer();
		void redraw();
		void reset();
		void add_geo_shape();

		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);
		void mouseDragged(ofMouseEventArgs& args);

		void deleteObject(SceneObject* obj);

		~DessinGeo();

	private:
		Geotype mode;
		std::vector<SceneObject*> shapes;
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

		ofMatrix4x4 transformMatrix;
		ofMatrix4x4 lastTransformMatrixInversed;
		ofMatrix4x4 yaw;
		ofMatrix4x4 pitch;
		ofMatrix4x4 roll;
		ofMatrix4x4 originRotation;

		vector<SceneElement*> sceneElements;
};