#pragma once

#include "ofMain.h"
#include "gui/Gui.h"
#include "Transformation/Camera2d.h"
#include "Image/Cursor.h"
#include "Image/DessinVec.h"

class Renderer
{
	public:
		Renderer();
		void setup();
		void update();
		void draw();
		void windowResized(int width, int height);

		void mousePressed(ofMouseEventArgs& args);
		void mouseReleased(ofMouseEventArgs& args);
		void mouseMoved(ofMouseEventArgs& args);
		void mouseDragged(ofMouseEventArgs& args);
		void mouseExited();
		void mouseEntered();
		void keyPressed(ofKeyEventArgs& args);
		void deleteSceneObject(SceneObject* obj);

		// Singleton
		static Renderer* getInstance();
		Renderer(const Renderer& obj) = delete;

	private:

		Gui* gui;
		Cursor cursors;
		DessinVec dessinateur;

		static Renderer* instancePtr;
};

const int FRAME_RATE = 60;
const ofColor BACKGROUND_COLOR = ofColor(40, 40, 40, 255);
const int KEY_CONTROL_S = 19;

Renderer* Renderer::instancePtr = nullptr;

