#pragma once

#include "GeObject.h"

class Skybox : public SceneObject{
public:
	void draw();
	void set_texture(ofImage _image);
	static ofImage generate_texture();
private: 
	void calculate_vertex();
	void calculate_normal();
	void calculate_tex_coord(int w, int h);
	void draw_mesh();

	ofMesh mesh;
	ofImage image;
};
