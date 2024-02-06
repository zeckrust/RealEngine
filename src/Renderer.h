#pragma once

#include "ofMain.h"
#include "gui/Gui.h"

class Renderer
{
	public:
		Renderer(Gui* _gui, Camera2d* _camera2d);
		void setup();
		void update();
		void draw();
		void windowResized(int width, int height);

		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);
		void mouseMoved(ofMouseEventArgs& args);
		void mouseDragged(ofMouseEventArgs& args);
		void keyPressed(ofKeyEventArgs& args);

	private:
		void saveScene(Scene& scene, std::string filePath);

		Gui* gui;
		Camera2d* camera2d;

};

const int FRAME_RATE = 60;
const ofColor BACKGROUND_COLOR = ofColor(212, 212, 212, 255);
