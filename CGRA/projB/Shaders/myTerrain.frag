#ifdef GL_ES
precision highp float;
#endif

varying vec2 vTextureCoord;

uniform sampler2D uSampler;
uniform sampler2D uSampler2;
uniform sampler2D uSampler3;

void main() {

	vec4 color = texture2D(uSampler, vTextureCoord);
	vec4 heightMap = texture2D(uSampler2, vTextureCoord);

	vec4 filter = texture2D(uSampler3, vec2(1.0-heightMap.b, 1.0-heightMap.b));

	gl_FragColor = (color + filter)/2.0;
}