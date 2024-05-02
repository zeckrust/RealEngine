#pragma once

#include "ofMain.h"
#include "SceneObject.h"
#include "Filter.h"

enum class Geotype { none, rectangulaire, cylindre, relief_effect};

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
		void setTexture(ofImage texture);
		void setFilter(Filter *filter);

		void draw(void) override;

	private:
		ofMesh draw_prisme_rect(ofColor color);
		ofMesh draw_cylindre(ofColor color);
		void draw_relief_effect(void);
		void create_relief_effect_mesh(void);

		Geotype type;
		float stroke_width;
		ofColor stroke_color;
		ofColor fill_color;
		ofImage imported_texture;
		Filter* texture_filter;

		ofMesh relief_effect_mesh = ofMesh();
		bool is_relief_mesh_created = false;

		bool is_texture_loaded;
};