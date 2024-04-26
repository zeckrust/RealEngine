#version 330

in vec2 surface_texcoord;
out vec4 fragment_color;

uniform sampler2D image;

void main() {
    vec3 texture_sample = texture(image, surface_texcoord).rgb;

    vec3 kelvin_color_temperature = vec3(1.0, 0.698, 0.564);
    vec3 filtered_color = mix(texture_sample, kelvin_color_temperature, 0.3);

    fragment_color = vec4(filtered_color, 1.0);
}