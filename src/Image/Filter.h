#pragma once

#include "ofMain.h"
#include "math.h"

enum FilterType {
	NO_FILTER = 0,
	GRAY,
	KELVIN,
	NASHVILLE,
	REINHARD,
	EXPOSITION2,
	EXPOSITION05,
};

class Filter {
	public:
		static ofImage toGray(ofImage &texture);
		static ofImage toKelvin(ofImage &texture);
		static ofImage toNashville(ofImage &texture);
		static ofImage toTonalMappingReinhard(ofImage& texture);
		static ofImage toTonalMappingExposition2(ofImage& texture);
		static ofImage toTonalMappingExposition05(ofImage& texture);
};
