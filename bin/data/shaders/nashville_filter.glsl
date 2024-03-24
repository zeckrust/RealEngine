#version 330

in vec2 texture_coords;
out vec4 fragment_color_out;

uniform sampler2D texture_image;

void main() {
    vec4 fragment_color_in = texture(texture_image, texture_coords);

    vec3 nashville_color_temperature = vec3(1.0, 0.9, 0.9);
    fragment_color_in.rgb = mix(frag_color_in, nashville_color_temperature, 0.4);

    // Increse contrast
    fragment_color_in.rgb = clamp((fragment_color_in.rgb - 0.5) * 1.5 + 0.5, 0.0, 1.0);

    // Add effect
    float distance = distance(texture_coords, vec2(0.5, 0.5));
    float strength = smoothstep(0.7, 0.9, distance);
    fragment_color_in.rgb *= mix(1.0, 1.0 - strength, 0.5);

    fragment_color_out = fragment_color_in;
}