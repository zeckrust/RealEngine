#pragma once

#include "ofMain.h"

enum FilterType {
	NO_FILTER = 0,
	GRAY,
	KELVIN,
	NASHVILLE
};

class Filter {
	public:
		static ofImage toGray(ofImage &texture);
		static ofImage toKelvin(ofImage &texture);
		static ofImage toNashville(ofImage &texture);
};
