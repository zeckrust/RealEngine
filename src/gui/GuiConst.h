#pragma once

// App


// Title bar
const float TITLE_BAR_POS_X = 0.0f;
const float TITLE_BAR_POS_Y = 0.0f;
const float TITLE_BAR_BUTTON_PADDING = 10.0f;

const int TITLE_BAR_HEIGHT = 30;
const ofColor TITLE_BAR_COLOR = ofColor(66, 66, 66);

// Custom button
const ofColor BUTTON_DEFAULT_COLOR = ofColor(0, 0, 0, 0);
const ofColor BUTTON_PRESSED_COLOR = ofColor(0, 0, 0, 255);
const ofColor BUTTON_HOVER_COLOR = ofColor(120, 120, 120, 255);
const ofColor BUTTON_LABEL_COLOR = ofColor(255, 255, 255, 255);
const int BUTTON_PRESSED_DURATION_MS = 100;
const int BUTTON_CLOSE_EXTENSION_THRESHOLD_MS = 1000;
const int BUTTON_FONT_SIZE = 11;

// Fonts
const std::string REGULAR_FONT = "../src/gui/fonts/OpenSans-Regular.ttf";
const std::string BOLD_FONT = "../src/gui/fonts/OpenSans-Bold.ttf";
const float FONT_WIDTH_ERROR = 8.0f;
