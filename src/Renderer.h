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
		DessinVec dessinateurOrthogonal;
		DessinGeo dessinateurPerspective;

		static Renderer* instancePtr;

		std::vector<SceneObject*> shapes;
};

const int FRAME_RATE = 60;
const ofColor BACKGROUND_COLOR = ofColor(40, 40, 40, 255);
const int KEY_CONTROL_S = 19;
const int KEY_A = 97;
const int KEY_D = 100;
const int KEY_E = 101;
const int KEY_H = 104;
const int KEY_I = 105;
const int KEY_J = 106;
const int KEY_K = 107;
const int KEY_Q = 113;
const int KEY_S = 115;
const int KEY_U = 117;
const int KEY_W = 119;
const int KEY_X = 120;
const int KEY_Y = 121;
const int KEY_Z = 122;

Renderer* Renderer::instancePtr = nullptr;

