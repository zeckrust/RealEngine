#version 120

uniform sampler2DRect tex;

void main() {
	vec2 texCoord = gl_TexCoord[0].xy;

	vec2 zoneMin = vec2(100, 100);
	vec2 zoneMax = vec2(500, 500);

	if (texCoord.x >= zoneMin.x && texCoord.x <= zoneMax.x &&
		texCoord.y >= zoneMin.y && texCoord.y <= zoneMax.y) {
			gl_FragColor = texture2DRect(tex, texCoord);
		} else {
			gl_FragColor = vec4(0, 0, 0, 0);
		}
}