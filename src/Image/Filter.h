#pragma once

#include "ofMain.h"

enum FilterType {
	GRAY = 0,
	KELVIN,
	NASHVILLE,
	NO_FILTER
};

class Filter {
	public:
		Filter();
		void setup(FilterType type);
		void begin(void);
		void end(void);
		void setTexture(ofImage &texture);

	private:
		ofShader shader;
};
