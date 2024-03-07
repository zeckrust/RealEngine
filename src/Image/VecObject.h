#pragma once

#include "ofMain.h"
#include "SceneObject.h"

enum class Primitype { none, square, line, rectangle, ellipse, circle, image, stage1, stage2 };

class VecObject : public SceneObject
{
	public :
		VecObject(Primitype vType);
		Primitype getType(void);
		float getStrokeWidth(void);
		ofColor getStrokeColor(void);
		ofColor getFillColor(void);
		ofImage getImage(void);

		void setType(Primitype vType);
		void setStrokeWidth(float width);
		void setStrokeColor(ofColor color);
		void setFillColor(ofColor color);
		void setImage(ofImage img);

	private :
		Primitype type;
		float stroke_width;
		ofColor stroke_color;
		ofColor fill_color;
		ofImage	imported_image;
};