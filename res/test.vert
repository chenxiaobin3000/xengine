// normal

#ifdef GL_ES
precision mediump float;
#endif

uniform mat4 ModelViewProj;
uniform vec3 AmbiColor;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 EyePosition;
uniform vec4 MaterialD;
uniform vec4 MaterialA;
uniform vec4 MaterialS;
uniform vec4 MaterialE;
uniform vec3 FogColor;

attribute vec4 Position;
attribute vec2 TexCoord;
attribute vec3 Normal;

varying vec2 TexCoordF;
varying vec3 ColorF;

void main() {
    gl_Position = ModelViewProj * Position;
//    gl_Position[0] = Position[0]*2.0-1.0;
//    gl_Position[1] = Position[1]*2.0-1.0;
//	gl_Position[2] = Position[2];
//	gl_Position[3] = 1.0;
	TexCoordF = TexCoord;
}
