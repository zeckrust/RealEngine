#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Transformation/Camera2d.h"
#include "Image/SceneObject.h"
#include "gui/Gui.h"
#include "Renderer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void exit();

		void keyPressed(ofKeyEventArgs& key);
		void keyReleased(int key);
		void mouseMoved(ofMouseEventArgs& mouse);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		Camera2d camera2d;
		Renderer* renderer;
};
