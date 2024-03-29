#pragma once

#include "ofMain.h"

// App
const std::string FILE_NAME_SETTINGS = "settings.xml";

// Title bar
const float TITLE_BAR_POS_X = 0.0f;
const float TITLE_BAR_POS_Y = 0.0f;
const float TITLE_BAR_BUTTON_PADDING = 10.0f;

const int TITLE_BAR_HEIGHT = 30;
const ofColor TITLE_BAR_COLOR = ofColor(20, 20, 20, 255);
const int TITLE_BAR_LINE_LIMIT_HEIGHT = 2;
const ofColor TITLE_BAR_LINE_LIMIT_COLOR = ofColor(78, 59, 255, 255);

// Custom button
const ofColor BUTTON_DEFAULT_COLOR = ofColor(50, 50, 50, 255);
const ofColor BUTTON_PRESSED_COLOR = ofColor(0, 0, 0, 255);
const ofColor BUTTON_HOVER_COLOR = ofColor(120, 120, 120, 255);
const ofColor BUTTON_LABEL_COLOR = ofColor(255, 255, 255, 255);
const int BUTTON_PRESSED_DURATION_MS = 100;
const int BUTTON_CLOSE_EXTENSION_THRESHOLD_MS = 1000;
const int DEFAULT_BUTTON_HEIGHT = 30;

// Custom panel
const int PANEL_TITLE_HEIGHT = 20;
const ofColor PANEL_TITLE_COLOR = TITLE_BAR_COLOR;
const ofColor PANEL_HEADER_BACKGROUND_COLOR = ofColor(100, 100, 100, 255);
const int CUSTOM_PANEL_DEFAULT_WIDTH = 150;
const int CUSTOM_PANEL_PADDING = 10;

// Fonts
const int FONT_SIZE = 11;
const std::string REGULAR_FONT = "../src/gui/fonts/OpenSans-Regular.ttf";
const std::string BOLD_FONT = "../src/gui/fonts/OpenSans-Bold.ttf";
const float FONT_WIDTH_ERROR = 8.0f;

// Scene
const float SCENE_PADDING = 10.0f;
const ofColor SCENE_DEFAULT_BACKGROUND_COLOR = ofColor(70, 70, 70, 255);

// Histogram
const int NUMBER_OF_COLOR_VALUE = 256;
const int HISTOGRAM_HEIGHT = 256;
const int HISTOGRAM_UPPER_POS = 100;
const int HISTOGRAM_PADDING = 20;
