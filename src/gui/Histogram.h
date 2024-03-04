#pragma once

#include "ofMain.h"
#include "GuiConst.h"

class Histogram {
public:
	void draw();
	void setup(int _grab_x, int _grab_y, int _grab_w, int _grab_h);
	void update(int _grab_x, int _grab_y, int _grab_w, int _grab_h);

private:
	int arrayMax(int* arr, int sizeArray);
	int convertNbPixels2HistoRect(int nbPixel, int maxPixelValue);
	void clearArray(int arr[], int sizeArray);
	void calculatePixelValues();
	void calculateLinesPos();
	void calculateLinePos(int colorArray[], int sizeArray, glm::vec2 linesStart[], glm::vec2 linesEnd[]);
	void drawColoredLines(ofColor color, int sizeArray, glm::vec2 linesStart[], glm::vec2 linesEnd[]);

	int grab_x;
	int grab_y;
	int grab_w;
	int grab_h;

	vector<ofColor> colors;
	vector<ofRectangle> rectangles;
	int red[NUMBER_OF_COLOR_VALUE];
	int green[NUMBER_OF_COLOR_VALUE];
	int blue[NUMBER_OF_COLOR_VALUE];
	glm::vec2 redLinesStart[NUMBER_OF_COLOR_VALUE];
	glm::vec2 redLinesEnd[NUMBER_OF_COLOR_VALUE];
	glm::vec2 greenLinesStart[NUMBER_OF_COLOR_VALUE];
	glm::vec2 greenLinesEnd[NUMBER_OF_COLOR_VALUE];
	glm::vec2 blueLinesStart[NUMBER_OF_COLOR_VALUE];
	glm::vec2 blueLinesEnd[NUMBER_OF_COLOR_VALUE];

	ofImage image1;
	const ofColor BACKGROUND_COLOR = ofColor(0, 0, 0, 64);
};
