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
            ofColor color = filteredImage.getColor(x, y);

            float red = color.r / 255.0;
            float green = color.g / 255.0;
            float blue = color.b / 255.0;

            float temp = 0.5;

            float redKelvin = red * (temp <= 66 ? 1 : (float)(temp - 60) / (temp <= 66 ? 66 : 255));
            float greenKelvin = green * (temp <= 66 ? (float)((temp <= 66 ? 99.4708025861 : temp - 60.0) * log(temp <= 66 ? temp : 255 - temp)) - 161.1195681661 : (float)(temp - 60) / (temp <= 66 ? 66 : 255));
            float blueKelvin = (temp >= 66 ? 1 : temp <= 19 ? 0 : (float)((temp <= 66 ? 138.5177312231 : temp - 10) * log(temp <= 66 ? temp : 255 - temp)) - 305.0447927307);

            filteredImage.setColor(x, y, ofColor(redKelvin * 255, greenKelvin * 255, blueKelvin * 255));
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

            r = 0.393 * r + 0.769 * g + 0.189 * b;
            g = 0.349 * r + 0.686 * g + 0.168 * b;
            b = 0.272 * r + 0.534 * g + 0.131 * b;

            r = ofClamp(r, 0, 255);
            g = ofClamp(g, 0, 255);
            b = ofClamp(b, 0, 255);

            filteredImage.setColor(x, y, ofColor(r, g, b));
        }
    }

    filteredImage.update();

    return filteredImage;
}
