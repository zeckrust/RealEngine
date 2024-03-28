#version 330

in vec2 surface_texcoord;
out vec4 fragment_color;

uniform sampler2D image;

void main() {
    vec3 texture_sample = texture(image, surface_texcoord).rgb;

    vec3 nashville_color_temperature = vec3(0.933, 0.674, 0.545);
    vec3 filtered_color = mix(texture_sample, nashville_color_temperature, 0.3);

    // Increase contrast
    filtered_color = clamp((filtered_color - 0.5) * 1.5 + 0.5, 0.0, 1.0);

    // Add effect
    float distance = distance(surface_texcoord, vec2(0.5, 0.5));
    float strength = smoothstep(0.7, 0.9, distance);
    filtered_color *= mix(1.0, 1.0 - strength, 0.5);

    fragment_color = vec4(filtered_color, 1.0);
}