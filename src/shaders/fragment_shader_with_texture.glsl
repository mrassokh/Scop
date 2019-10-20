#version 400 core
out vec4 color;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 fragPos;
in vec4 normal;
uniform sampler2D ourTexture;
uniform vec4 frag_flags;
uniform vec3 lightPos;


void main()
{
	float cosinus;
	vec3 norm = vec3(normalize(normal));
	vec3 camDir = vec3(0, 0, -1);
	vec3 ambient = vec3(1, 1, 1);
	vec3 lightDir = normalize(lightPos - fragPos);

	if (frag_flags.w != 0)
	{
		if (dot(camDir,norm) > 0)
			cosinus = max(dot(norm, lightDir), 0.0);
		else
			cosinus = 0;
		vec3 diff = cosinus * ourColor * 0.8 + ambient * 0.2;
		color = vec4(diff,  1.0f);
	}
	else
	{
		color =  vec4(ourColor , 1.0f);
	}
	if (frag_flags.y != 0)
		color = texture(ourTexture, TexCoord) * color;
}
