#pragma once
#include "ofMain.h"
#include "VecObject.h"
#include "../gui/Histogram.h"
#include "GeObject.h"
#include "../gui/scene/SceneElement.h"
#include "BezierObject.h"
#include "Drawer.h"
#include "Skybox.h"
#include "Maillage.h"

class Gui;

class DessinVec : public Drawer
{
	public :
		DessinVec();
		void setup(std::vector<SceneObject*>* _shapes);
		void update();
		void draw();
		void draw_buffer();
		void redraw();
		void reset();
		void add_shape();
		void add_topo();
		void add_maillage();

		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);
		void mouseDragged(ofMouseEventArgs& args);

		void deleteObject(SceneObject* obj);

		~DessinVec();

	private :
		void dynamic_stage_1() const;
		void dynamic_stage_2() const;
		void setup_camera();
		void setup_skybox();
		void setup_matrix();


		Primitype mode;
		Gui* gui = nullptr;
		
		bool bezier_mode;
		std::vector<ofVec3f> ctrl_pts;

		bool mesh_mode;
		Maillage maillage;

		int mouse_press_x;
		int mouse_press_y;

		int mouse_current_x;
		int mouse_current_y;

		int mouse_last_x;
		int mouse_last_y;

		bool mouse_pressed;
		bool is_drawing_mode;
		bool is_transform_mode;

		uint32_t compteur_square;
		uint32_t compteur_circle;
		uint32_t compteur_ellipse;
		uint32_t compteur_rectangle;
		uint32_t compteur_line;
		uint32_t compteur_image;
		uint32_t compteur_stage_1;
		uint32_t compteur_stage_2;
		uint32_t compteur_bezier;


		ofPolyline ligne;

		ofFbo fbo;
		ofRectangle scene2DShape;
		ofRectangle oldScene2dShape;

		Histogram histogramOrthogonal;

		ofCamera camera;
		ofVec3f camera_position;
		ofVec3f camera_target;
		float camera_offset;

		Skybox skybox;

		ofMatrix4x4 transformMatrix;
		ofMatrix4x4 lastTransformMatrixInversed;
		ofMatrix4x4 yaw;
		ofMatrix4x4 pitch;
		ofMatrix4x4 roll;
		ofMatrix4x4 originRotation;

		vector<SceneElement*> sceneElements;
};