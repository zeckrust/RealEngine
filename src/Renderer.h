#pragma once

#include "ofMain.h"
#include "gui/Gui.h"
#include "Transformation/Camera2d.h"
#include "Image/Cursor.h"

class Renderer
{
	public:
		Renderer(Camera2d* _camera2d);
		void setup();
		void update();
		void draw();
		void windowResized(int width, int height);

		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);
		void mouseMoved(ofMouseEventArgs& args);
		void mouseDragged(ofMouseEventArgs& args);
		void mouseExited();
		void keyPressed(ofKeyEventArgs& args);

	private:
		void saveScene(Scene& scene, std::string filePath);

		Gui* gui;
		Camera2d* camera2d;
		Cursor cursors;
};

const int FRAME_RATE = 60;
const ofColor BACKGROUND_COLOR = ofColor(212, 212, 212, 255);
const int KEY_CONTROL_S = 19;
