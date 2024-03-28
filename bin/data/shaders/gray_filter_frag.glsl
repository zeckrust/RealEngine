#version 330

in vec2 surface_texcoord;
out vec4 fragment_color;

uniform sampler2D image;

void main() {
    vec3 texture_sample = texture(image, surface_texcoord).rgb;

    float gray_mean = (texture_sample.r + texture_sample.g + texture_sample.b) / 3.0;
    
    fragment_color = vec4(gray_mean, gray_mean, gray_mean, 1.0);
}
