#include "CustomPanel.h"

CustomPanel::CustomPanel() : ofxGuiGroup() {

}

void CustomPanel::setup(std::string panelName, float x, float y) {
	ofxGuiGroup::setup(panelName, FILE_NAME_SETTINGS, x, y);
	unregisterMouseEvents();
}
