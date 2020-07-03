#ifdef GL_ES
precision highp float;
#endif

varying vec2 vTextureCoord;

uniform float timeFactor;
uniform sampler2D uSampler;
uniform sampler2D uSampler2;

void main() {

	float time_offset = timeFactor*0.01;

	vec2 animated_vCoords = mod(vTextureCoord + vec2(time_offset, time_offset), vec2(1.0,1.0));
	vec4 color = texture2D(uSampler2, animated_vCoords);

	gl_FragColor = texture2D(uSampler, animated_vCoords) - vec4(0.4*color.b, 0.4*color.b, 0.4*color.b, 0.0);
}