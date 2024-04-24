#include "Filter.h"

ofImage Filter::toGray(ofImage& texture) {
    ofImage filteredImage = ofImage(texture);

    int width = filteredImage.getWidth();
    int height = filteredImage.getHeight();

    // Iterate through each pixel of the image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofColor color = filteredImage.getColor(x, y);
            float grayscale = 0.2989 * color.r + 0.5870 * color.g + 0.1140 * color.b;
            filteredImage.setColor(x, y, ofColor(grayscale));
        }
    }

    filteredImage.update();

    return filteredImage;

}

ofImage Filter::toKelvin(ofImage& texture) {
    ofImage filteredImage = ofImage(texture);

    int width = filteredImage.getWidth();
    int height = filteredImage.getHeight();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofColor pixel_color = filteredImage.getColor(x, y);
            ofColor kelvin = ofColor(255, 178, 144);
            ofColor filtered_color = pixel_color.lerp(kelvin, 0.5);
            
            filteredImage.setColor(x, y, filtered_color);
        }
    }

    filteredImage.update();

    return filteredImage;
}

ofImage Filter::toNashville(ofImage& texture) {
    ofImage filteredImage(texture);

    int width = filteredImage.getWidth();
    int height = filteredImage.getHeight();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofColor color = filteredImage.getColor(x, y);

            float r = color.r;
            float g = color.g;
            float b = color.b;

            r = ofClamp(0.9 * r + 0.1 * g - 30, 0, 255);
            g = ofClamp(0.9 * r + 0.1 * b - 30, 0, 255);
            b = ofClamp(0.9 * b + 0.1 * g - 30, 0, 255);

            //r = ofClamp(0.9 * r + 0.05 * g + 0.05 * b, 0, 255);
            //g = ofClamp(0.75 * r + 0.1 * g + 0.15 * b, 0, 255);
            //b = ofClamp(0.6 * r + 0.2 * g + 0.2 * b, 0, 255);
                        
            filteredImage.setColor(x, y, ofColor(r, g, b));
        }
    }

    filteredImage.update();

    return filteredImage;
}
