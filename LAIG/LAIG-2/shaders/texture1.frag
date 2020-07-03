#ifdef GL_ES
precision highp float;
#endif

varying vec2 vTextureCoord;
uniform sampler2D uSampler;
uniform sampler2D uSampler2;
uniform float timeFactor;

void main() {
    vec4 color = texture2D(uSampler, vTextureCoord);
    vec4 camera_filter = texture2D(uSampler2, vTextureCoord);
    float scaledDistance = (vTextureCoord.x - 0.5) * (vTextureCoord.x - 0.5) + (vTextureCoord.y - 0.5) * (vTextureCoord.y - 0.5);
    if (sin(timeFactor) > 0.5) {
        if(mod(vTextureCoord.y * 40.0, 3.0) > 2.8)
            color = vec4(1.0, 1.0, 1.0, 1.0); 
    }
    else {
        if(mod(vTextureCoord.y * 40.0 + 5.0, 3.0) > 2.8)
            color = vec4(1.0, 1.0, 1.0, 1.0); 
    }
    color = vec4(color.rgb - (color.rgb * (scaledDistance/0.4)), 1.0);

    if (camera_filter.r > 0.1)
        gl_FragColor = camera_filter;
    else
        gl_FragColor = color;
}