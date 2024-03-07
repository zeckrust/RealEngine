#pragma once
//#include "../apps/RealEngine/src/Renderer.h"
#include "ofMain.h"

enum class Primitype {none, square, line, rectangle, ellipse, circle, image};

struct PrimitiveVectorielle
{
	Primitype			type;
	float               position1[2];
	float               position2[2];
	float               stroke_width;
	ofColor				stroke_color;
	ofColor		        fill_color;
	ofImage				imported_image;
};

class Gui;

class DessinVec
{
	public :
		DessinVec();
		void setup();
		void draw();
		void reset();
		void add_vector_shape();
		void mousePressed();
		void draw_buffer();
		ofFbo getFbo() const;
		~DessinVec();

	private :
		void draw_line(PrimitiveVectorielle prim) const;
		void draw_rectangle(PrimitiveVectorielle prim) const;
		void draw_square(PrimitiveVectorielle prim) const;
		void draw_circle(PrimitiveVectorielle prim) const;
		void draw_ellipse(PrimitiveVectorielle prim) const;

		Primitype mode;
		std::vector<PrimitiveVectorielle*> shapes;
		Gui* gui = nullptr;

		int index;

		int buffer_count;
		int buffer_size;
		int buffer_head;

		int mouse_press_x;
		int mouse_press_y;

		int mouse_current_x;
		int mouse_current_y;

		bool mouse_pressed;

		ofPolyline ligne;

		ofFbo fbo;
		ofShader shader;

};