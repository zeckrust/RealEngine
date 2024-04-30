#pragma once

#include "ofMain.h"
#include "SceneObject.h"

enum class Geotype { none, rectangulaire, cylindre };

class GeObject : public SceneObject
{
	public:
		GeObject(Geotype gType, float sWidth, ofColor sColor, ofColor fColor);
		Geotype getType(void);
		float getStrokeWidth(void);
		ofColor getStrokeColor(void);
		ofColor getFillColor(void);

		void setType(Geotype gType);
		void setStrokeWidth(float width);
		void setStrokeColor(ofColor color);
		void setFillColor(ofColor color);

		void draw(void) override;

	private:
		ofMesh draw_prisme_rect(ofColor color);
		ofMesh draw_cylindre(ofColor color);

		Geotype type;
		float stroke_width;
		ofColor stroke_color;
		ofColor fill_color;
};