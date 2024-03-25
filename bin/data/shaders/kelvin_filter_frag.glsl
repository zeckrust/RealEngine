#version 330

in vec2 surface_texture_coords;
out vec4 fragment_color_out;

uniform sampler2D texture_image;

void main() {
    vec4 fragment_color_in = texture(texture_image, surface_texture_coords);
    vec3 kelvin_color_temperature = vec3(1.0, 0.7, 0.6);
    fragment_color_in.rgb = mix(fragment_color_in.rgb, kelvin_color_temperature, 0.5);
    
    fragment_color_out = fragment_color_in;
}
