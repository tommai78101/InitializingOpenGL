#version 400

in vec3 vertexPoints;
in vec3 vertexColors;

out vec3 frag_Colors;

//ShaderToy stuffs
uniform vec2 u_ScreenResolution;
uniform float u_Time;
out vec2 iResolution;


void main() {
    gl_Position = vec4(vertexPoints, 1.0);
	 frag_Colors = vertexColors;

	 //ShaderToy stuffs
	 iResolution = u_ScreenResolution;
}