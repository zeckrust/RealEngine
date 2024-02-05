#pragma once

#include "ofMain.h"
#include "../Transformation/Camera2d.h"
#include "GuiConst.h"

class Scene : public ofRectangle
{
	public:
		Scene();
		void setup(float x, float y, float width, float height);
		void draw();
};
