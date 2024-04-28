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
                        
            filteredImage.setColor(x, y, ofColor(r, g, b));
        }
    }

    filteredImage.update();

    return filteredImage;
}

ofImage Filter::toTonalMappingReinhard(ofImage& texture) {
    ofImage filteredImage(texture);

    int width = filteredImage.getWidth();
    int height = filteredImage.getHeight();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofColor color = filteredImage.getColor(x, y);

            float r = color.r;
            float g = color.g;
            float b = color.b;

            r = r / (r + 1);
            g = g / (g + 1);
            b = b / (b + 1);

            filteredImage.setColor(x, y, ofColor(r, g, b));
        }
    }

    filteredImage.update();

    return filteredImage;
}

ofImage Filter::toTonalMappingExposition2(ofImage& texture) {
    ofImage filteredImage(texture);

    int width = filteredImage.getWidth();
    int height = filteredImage.getHeight();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofColor color = filteredImage.getColor(x, y);

            float f = 2.;

            float r = color.r;
            float g = color.g;
            float b = color.b;

            r = 1 - exp(-r * f);
            g = 1 - exp(-g * f);
            b = 1 - exp(-b * f);

            filteredImage.setColor(x, y, ofColor(r, g, b));
        }
    }

    filteredImage.update();

    return filteredImage;
}

ofImage Filter::toTonalMappingExposition05(ofImage& texture) {
    ofImage filteredImage(texture);

    int width = filteredImage.getWidth();
    int height = filteredImage.getHeight();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofColor color = filteredImage.getColor(x, y);

            float f = 0.5;

            float r = color.r;
            float g = color.g;
            float b = color.b;

            r = 1 - exp(-r * f);
            g = 1 - exp(-g * f);
            b = 1 - exp(-b * f);

            filteredImage.setColor(x, y, ofColor(r, g, b));
        }
    }

    filteredImage.update();

    return filteredImage;
}