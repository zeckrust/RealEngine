#version 330

in vec2 surface_texture_coords;
out vec4 fragment_color_out;

uniform sampler2D texture_image; 

void main() {
    vec4 frag_color_in = texture(texture_image, surface_texture_coords);
    float gray_mean = (frag_color_in.r + frag_color_in.g + frag_color_in.b) / 3;
    fragment_color_out = vec4(gray_mean, gray_mean, gray_mean, frag_color_in.a);
}
