#pragma once

#include "ofMain.h"

namespace ButtonsDefinition {

	void import() {
		ofFileDialogResult result = ofSystemLoadDialog("Load file");
		if (result.bSuccess) {
			string path = result.getPath(); 
			ofDirectory dir(path);

			ofImage image;
			std::filesystem::path dire = std::filesystem::u8path(dir.getAbsolutePath());
			image.load(dire);
			image.draw(100, 100);
		}
		
	}


}
