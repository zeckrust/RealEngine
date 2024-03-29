#pragma once

#include "GeObject.h"

class Skybox : public SceneObject{
public:
	void draw() {};
	void setup();
	void set_texture(ofImage _image);
	static ofImage generate_texture();
	void draw_mesh();

private: 
	void calculate_vertex();
	void calculate_normal();
	void calculate_tex_coord(int w, int h);

	ofMesh mesh;
	ofImage image;
};
