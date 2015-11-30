// normal

#ifdef GL_ES
precision mediump float;
#endif

attribute vec4 Position;
attribute vec2 TexCoord;
attribute vec3 Normal;

varying vec2 TexCoordF;

void main() {
    gl_Position[0] = Position[0]*2.0-1.0;
    gl_Position[1] = Position[1]*2.0-1.0;
	gl_Position[2] = Position[2];
	gl_Position[3] = 1.0;
	TexCoordF = TexCoord;
}
