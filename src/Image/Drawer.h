#pragma once

#include "ofMain.h"
#include "VecObject.h"
#include "GeObject.h"

class Drawer
{
public:
	Drawer() {};
	virtual void add_shape() = 0 {};
	virtual ~Drawer() = 0 {};
	std::vector<SceneObject*>* shapes;
};