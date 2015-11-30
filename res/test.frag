// normal

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D Samp0;

varying vec2 TexCoordF;

void main() {
    gl_FragColor = vec4(0.5,0.5,1,1);//texture2D(Samp0, TexCoordF.st);
}
