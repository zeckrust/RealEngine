#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	int height = 768;
	int width = 1024;
	ofGLWindowSettings settings;
	settings.setSize(width, height);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();

}
