#pragma once
#include "ofMain.h"
#include "../gui/scene/SceneElement.h"
#include "SceneObject.h"

class Gui;

class DessinTopologique
{
public:
	DessinTopologique();
	void setup();
	void update();
	void draw();
	void draw_buffer();
	void redraw();
	void reset();

	void mousePressed(ofMouseEventArgs& args);
	void mouseReleased(ofMouseEventArgs& args);
	void mouseDragged(ofMouseEventArgs& args);

	void deleteObject();

	~DessinTopologique();


private:
	void dynamic_stage_1() const;
	void dynamic_stage_2() const;

	std::vector<SceneObject*> lines;

	Gui* gui = nullptr;

	int mouse_current_x;
	int mouse_current_y;

	uint32_t compteur_line;

	ofFbo fbo;

	vector<SceneElement*> sceneElements;

};
