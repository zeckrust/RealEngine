#version 330

in vec4 position;
in vec2 texture_coords;

out vec2 surface_texture_coords;

void main() {
    gl_Position = position;
    surface_texture_coords = texture_coords;
}