#version 400 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normalCoord;
layout (location = 3) in vec3 defColor;
out vec3 ourColor;
out vec3 fragPos;
out vec4 normal;
out vec2 TexCoord;
uniform vec4 frag_flags;
uniform mat4 projection;
uniform mat4 scale;
uniform mat4 translate;
uniform mat4 rotate;
uniform vec3 diffuse;

void generateTexture(in vec3 vertex, out vec2 genTextCoord )
{
	const float PI = 3.1415926535897932384626433832795;
	vec3 vector_y = vec3(0, 1, 0);
	vec3 vector_x = vec3(1, 0, 0);
	vec3 normalToSphere = normalize(vertex);
	float dot_dir_y_norm = dot(normalToSphere,vector_y);
	float phi = acos(dot_dir_y_norm);
	float v = phi / PI;
	float dot_dir_x_norm = dot(normalToSphere,vector_x);
	float test = dot_dir_x_norm / sin (phi);
	if (abs(test) == 1.0)
		test += (test > 0) ? -0.0001 : 0.0001;
	float theta = acos(test) / (2 * PI);
	vec3 cross_dir_y_dir_x = cross(vector_x, vector_y);
	float u = dot(cross_dir_y_dir_x, normalToSphere) > 0 ? 1 - theta : theta;
	genTextCoord.x = u * 12 ;
	genTextCoord.y = -v * 12 ;
}


void main()
{
	vec2 genTextCoord = vec2(0,0);
	mat4 model_matrix = translate * rotate * scale;
	gl_Position = projection * model_matrix * vec4(position, 1.0);
	normal = rotate * vec4(normalCoord, 1.0);
	fragPos = vec3(model_matrix * vec4(position, 1.0));

	if (frag_flags.z == 0)
		ourColor = defColor;
	else if (frag_flags.z == 1)
		ourColor = vec3((1.0f - normalCoord.x) / 2 + 0.2f , (1.0f - normalCoord.y) / 2 + 0.2f,  (1.0f - normalCoord.z) / 2 + 0.2f);
	else if (frag_flags.z == 2)
		ourColor = diffuse;
	if (frag_flags.x != 0)
		TexCoord = texCoord;
	else
	{
		generateTexture(position, genTextCoord);
		TexCoord = genTextCoord;
	}
}
