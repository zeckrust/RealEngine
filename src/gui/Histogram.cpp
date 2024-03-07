#include "Histogram.h"

//--------------------------------------------------------------
void Histogram::setup(ofFbo _fbo, int _y_position) {
	update(_fbo, _y_position);
}


void Histogram::update(ofFbo _fbo, int _y_position) {
		fbo = _fbo;
		y_position = _y_position;

		calculatePixelValues();
		calculateLinesPos();
}

void Histogram::draw() {
	ofPushStyle();
	glm::vec2 topLeft = glm::vec2((ofGetWidth() - NUMBER_OF_COLOR_VALUE) * 0.5 - HISTOGRAM_PADDING, y_position + HISTOGRAM_PADDING);
	glm::vec2 bottomRight = glm::vec2((ofGetWidth() + NUMBER_OF_COLOR_VALUE) * 0.5 + HISTOGRAM_PADDING, y_position + fbo.getHeight() - HISTOGRAM_PADDING);

	ofRectangle background = ofRectangle(topLeft, bottomRight);
	ofSetColor(BACKGROUND_COLOR);
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

int Histogram::arrayMax(int* arr, int sizeArray) {
	int max = 0;
	for (int i = 0; i < sizeArray; i++) {
		int value = *(arr + i);
		if (value > max) {
			max = value;
		}
	}
	return max;
}

int Histogram::convertNbPixels2HistoRect(int nbPixel, int maxPixelValue) {
	return (nbPixel * HISTOGRAM_HEIGHT) / maxPixelValue;
}

void Histogram::clearArray(int arr[], int sizeArray) {
	for (int i = 0; i < sizeArray; i++) {
		*(arr + i) = 0;
	}
}

void Histogram::calculatePixelValues() {
	clearArray(red, NUMBER_OF_COLOR_VALUE);
	clearArray(green, NUMBER_OF_COLOR_VALUE);
	clearArray(blue, NUMBER_OF_COLOR_VALUE);
	ofPixels pixels;
	pixels.allocate(fbo.getWidth(), fbo.getHeight(), GL_RGBA);
	fbo.readToPixels(pixels);
	for (int i = 0; i < pixels.getWidth() * pixels.getHeight(); i++) {
		ofColor pixelColor = pixels.getColor(4 * i);
		red[pixelColor.r]++;
		green[pixelColor.g]++;
		blue[pixelColor.b]++;
	}
}

void Histogram::calculateLinesPos() {
	calculateLinePos(red, sizeof(red) / sizeof(int), redLinesStart, redLinesEnd);
	calculateLinePos(green, sizeof(green) / sizeof(int), greenLinesStart, greenLinesEnd);
	calculateLinePos(blue, sizeof(blue) / sizeof(int), blueLinesStart, blueLinesEnd);
}

void Histogram::calculateLinePos(int colorArray[], int sizeArray, glm::vec2 linesStart[], glm::vec2 linesEnd[]) {
	int max = arrayMax(colorArray, sizeArray);
	for (int i = 0; i < sizeArray; i++) {
		*(linesStart + i) = glm::vec2((ofGetWidth() * 0.5) + i - (sizeArray * 0.5), y_position + HISTOGRAM_HEIGHT + 2*HISTOGRAM_PADDING);
		*(linesEnd + i) = glm::vec2((ofGetWidth() * 0.5) + i - (sizeArray * 0.5), y_position + HISTOGRAM_HEIGHT - convertNbPixels2HistoRect(*(colorArray + i), max) + 2*HISTOGRAM_PADDING);
	}
}

void Histogram::drawColoredLines(ofColor color, int sizeArray, glm::vec2 linesStart[], glm::vec2 linesEnd[]) {
	ofSetColor(color);
	for (int i = 0; i < sizeArray; i++) {
		ofDrawLine(*(linesStart + i), *(linesEnd + i));
	}
}