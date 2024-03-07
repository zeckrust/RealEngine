#pragma once
#include "ofMain.h"
#include "VecObject.h"
#include "../gui/Histogram.h"

class Gui;

class DessinVec
{
	public :
		DessinVec();
		void setup();
		void update();
		void draw();
		void draw_buffer();
		void redraw();
		void reset();
		void add_vector_shape();

		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);
		void mouseDragged(ofMouseEventArgs& args);

		void deleteObject(SceneObject* obj);

		ofFbo getFbo() const;
		~DessinVec();

	private :
		void draw_line(VecObject obj) const;
		void draw_rectangle(VecObject obj) const;
		void draw_square(VecObject obj) const;
		void draw_circle(VecObject obj) const;
		void draw_ellipse(VecObject obj) const;
		void draw_stage_1(VecObject obj) const;
		void draw_stage_2(VecObject obj) const;
		void dynamic_stage_1() const;
		void dynamic_stage_2() const;


		Primitype mode;
		std::vector<VecObject*> shapes;
		Gui* gui = nullptr;

		int mouse_press_x;
		int mouse_press_y;

		int mouse_current_x;
		int mouse_current_y;

		bool mouse_pressed;

		uint32_t compteur_square;
		uint32_t compteur_circle;
		uint32_t compteur_ellipse;
		uint32_t compteur_rectangle;
		uint32_t compteur_line;
		uint32_t compteur_image;
		uint32_t compteur_stage_1;
		uint32_t compteur_stage_2;


		ofPolyline ligne;

		ofFbo fbo;
		ofRectangle scene2DShape;
		ofRectangle oldScene2dShape;

		Histogram histogramOrthogonal;
		Histogram histogramPerspective;
};