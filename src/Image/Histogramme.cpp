#include "Histogramme.h"

//--------------------------------------------------------------
void Histogramme::setup(string _sceneName, int _grab_x, int _grab_y, int _grab_w, int _grab_h) {
	grab_x = _grab_x;
	grab_y = _grab_y;
	grab_w = _grab_w;
	grab_h = _grab_h;

	calculatePixelValues();
	calculateLinesPos();
	sceneName = _sceneName;
	Y_OFFSET = 0;
	if (sceneName == "Vue perspective") {
		Y_OFFSET = ofGetHeight() * 0.46;
	}
}

void Histogramme::draw() {
	ofPushStyle();
	glm::vec2 topLeft = glm::vec2((ofGetWidth() * 0.5) - (NUMBER_OF_COLOR_VALUE * 0.5) - HISTOGRAM_PADDING, HISTOGRAM_UPPER_POS - HISTOGRAM_PADDING + Y_OFFSET);
	glm::vec2 bottomRight = glm::vec2((ofGetWidth() * 0.5) + (NUMBER_OF_COLOR_VALUE * 0.5) + HISTOGRAM_PADDING, HISTOGRAM_UPPER_POS + HISTOGRAM_HEIGHT + HISTOGRAM_PADDING + Y_OFFSET);

	ofRectangle background = ofRectangle(topLeft, bottomRight);
	ofSetColor(ofColor::black);
	ofDrawRectangle(background);
	ofPopStyle();

	calculateLinesPos();

	ofPushStyle();
	ofSetLineWidth(1);
	drawColoredLines(ofColor::red, sizeof(red) / sizeof(int), redLinesStart, redLinesEnd);
	drawColoredLines(ofColor::green, sizeof(green) / sizeof(int), greenLinesStart, greenLinesEnd);
	drawColoredLines(ofColor::blue, sizeof(blue) / sizeof(int), blueLinesStart, blueLinesEnd);
	ofPopStyle();
}

int Histogramme::arrayMax(int* arr, int sizeArray) {
	int max = 0;
	for (int i = 0; i < sizeArray; i++) {
		int value = *(arr + i);
		if (value > max) {
			max = value;
		}
	}
	return max;
}

int Histogramme::convertNbPixels2HistoRect(int nbPixel, int maxPixelValue) {
	return (nbPixel * HISTOGRAM_HEIGHT) / maxPixelValue;
}

void Histogramme::clearArray(int arr[], int sizeArray) {
	for (int i = 0; i < sizeArray; i++) {
		*(arr + i) = 0;
	}
}

void Histogramme::calculatePixelValues() {
	clearArray(red, NUMBER_OF_COLOR_VALUE);
	clearArray(green, NUMBER_OF_COLOR_VALUE);
	clearArray(blue, NUMBER_OF_COLOR_VALUE);
	ofImage image;
	image.grabScreen(grab_x, grab_y, grab_w, grab_h);
	ofPixels pixels = image.getPixels();
	for (int i = 0; i < pixels.getWidth() * pixels.getHeight(); i++) {
		ofColor pixelColor = pixels.getColor(4 * i);
		red[pixelColor.r]++;
		green[pixelColor.g]++;
		blue[pixelColor.b]++;
	}
}

void Histogramme::calculateLinesPos() {
	calculateLinePos(red, sizeof(red) / sizeof(int), redLinesStart, redLinesEnd);
	calculateLinePos(green, sizeof(green) / sizeof(int), greenLinesStart, greenLinesEnd);
	calculateLinePos(blue, sizeof(blue) / sizeof(int), blueLinesStart, blueLinesEnd);
}

void Histogramme::calculateLinePos(int colorArray[], int sizeArray, glm::vec2 linesStart[], glm::vec2 linesEnd[]) {
	int max = arrayMax(colorArray, sizeArray);
	for (int i = 0; i < sizeArray; i++) {
		*(linesStart + i) = glm::vec2((ofGetWidth() * 0.5) + i - (sizeArray * 0.5), HISTOGRAM_UPPER_POS + HISTOGRAM_HEIGHT + Y_OFFSET);
		*(linesEnd + i) = glm::vec2((ofGetWidth() * 0.5) + i - (sizeArray * 0.5), HISTOGRAM_UPPER_POS + HISTOGRAM_HEIGHT - convertNbPixels2HistoRect(*(colorArray + i), max) + Y_OFFSET);
	}
}

void Histogramme::drawColoredLines(ofColor color, int sizeArray, glm::vec2 linesStart[], glm::vec2 linesEnd[]) {
	ofSetColor(color);
	for (int i = 0; i < sizeArray; i++) {
		ofDrawLine(*(linesStart + i), *(linesEnd + i));
	}
}