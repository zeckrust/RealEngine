#pragma once

#include "ofMain.h"
#include "SceneObject.h"

enum class Primitype { none, square, line, rectangle, ellipse, circle, image, stage1, stage2 };

class VecObject : public SceneObject
{
	public :
		VecObject(Primitype vType);
		VecObject(Primitype vType, float sWidth, ofColor sColor, ofColor fColor, ofImage image);
		VecObject(Primitype vType, float sWidth, ofColor sColor, ofColor fColor);
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
		void draw(void) override;

	private :
		void draw_line() const;
		void draw_rectangle() const;
		void draw_rectangle_from_param(ofVec3f position, ofVec3f dimension) const;
		void draw_square() const;
		void draw_circle() const;
		void draw_ellipse() const;
		void draw_stage_1() const;
		void draw_stage_2() const;
		void draw_image() const;

		Primitype type;
		float stroke_width;
		ofColor stroke_color;
		ofColor fill_color;
		ofImage	imported_image;
};