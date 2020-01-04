#version 400

in vec3 frag_Colors;

out vec4 gl_Color;

uniform vec2 u_ScreenResolution;
uniform float u_Time;

//Calculates the distance from the center of UV coordinate to the hexagon's edge.
float HexagonalDistance(vec2 pos) {
	//"pos": position of the UV coordinates
	pos = abs(pos);

	float constantC = dot(pos, normalize(vec2(1, 1.73)));
	constantC = max(constantC, pos.x);
	return constantC;
}

//Gives UV coordinates (x, y) of the rectangle grids, and for each hexagon, give the id (z, w).
//Hence its return type is vec4.
vec4 HexagonalCoords(vec2 uv) {
	vec2 repeatRate = vec2(1, 1.73);
	vec2 half = repeatRate * 0.5;

	//fract(x) = mod(x, 1.0)
	vec2 a = mod(uv, repeatRate) - half;
	vec2 b = mod(uv - half, repeatRate) - half;

	vec2 gridUV;
	if (length(a) < length(b)) {
		gridUV = a;
	}
	else {
		gridUV = b;
	}

	//ID generation
	vec2 id = uv - gridUV;

	//Distance to the edge of the hexagon.
	float x = atan(gridUV.x, gridUV.y);
	float y = 0.5 - HexagonalDistance(gridUV);

	return vec4(x, y, id.x, id.y);
}

void main() {
	//ShaderToy stuffs
	vec2 uv = (gl_FragCoord.xy - 0.5 * u_ScreenResolution) / u_ScreenResolution.y;
	vec3 color = vec3(0);
	
	//Displays a white hexagon in the center, with a radius of 0.2 normalized units long.
	//color += step(HexagonalDistance(uv), 0.2);

	//Animating the hex to move towards the center.
	//color += sin(HexagonalDistance(uv) * 10.0 + u_Time);

	//Enlarge the resolution of the UV coordinates, so we're looking at large hexagons.
	uv *= 10.0;
	
	//Obtain the hexagon coordinates.
	vec4 hexCoords = HexagonalCoords(uv + 100.0);

	//Apply bilinear filtering as the hexagon fades in and out by deltaTime.
	float constantC = smoothstep(0.01, 0.03, hexCoords.y * sin(hexCoords.z * hexCoords.w + u_Time));

	//Add the colors on top of the black background.
	color += constantC;

	//Final color applied at the End
	gl_Color = vec4(color, 1.0);
}