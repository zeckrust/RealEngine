#pragma once

#include "ofMain.h"
#include "../GuiConst.h"

class Gui; // Forward declaration

class Scene : public ofRectangle
{
	public:
		Scene();
		void setup(float x, float y, float width, float height);
		void update(void);
		void draw(void);

	private:
		Gui* gui = nullptr;
		ofColor backgroundColor = SCENE_DEFAULT_BACKGROUND_COLOR;
};
