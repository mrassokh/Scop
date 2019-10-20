/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 08:39:20 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/02 08:39:27 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

int			check_shader_compile(GLuint shader, t_shaders *shaders)
{
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaders->success);
	if (!shaders->success)
	{
		glGetShaderInfoLog(shader, 512, NULL, shaders->info_log);
		printf("%s\n%s\n", "ERROR::SHADER::COMPILATION_FAILED\n",
				shaders->info_log);
	}
	return (shaders->success);
}

int			shaders_compile(t_shaders *shaders)
{
	shaders->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	shaders->vertex_shader_source = get_shader_source(
		"src/shaders/vertex_shader_with_texture.glsl", &shaders->shader_reader);
	glShaderSource(shaders->vertex_shader, 1,
					&shaders->vertex_shader_source, NULL);
	glCompileShader(shaders->vertex_shader);
	if (!check_shader_compile(shaders->vertex_shader, shaders))
		return (0);
	shaders->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	shaders->fragment_shader_source = get_shader_source(
		"src/shaders/fragment_shader_with_texture.glsl",
			&shaders->shader_reader);
	glShaderSource(shaders->fragment_shader, 1,
						&shaders->fragment_shader_source, NULL);
	glCompileShader(shaders->fragment_shader);
	if (!check_shader_compile(shaders->fragment_shader, shaders))
		return (0);
	return (1);
}

void		create_shader_program(t_shaders *shaders)
{
	if (!shaders_compile(shaders))
		return ;
	shaders->shader_program = glCreateProgram();
	glAttachShader(shaders->shader_program, shaders->vertex_shader);
	glAttachShader(shaders->shader_program, shaders->fragment_shader);
	glLinkProgram(shaders->shader_program);
	glGetProgramiv(shaders->shader_program, GL_LINK_STATUS, &shaders->success);
	if (!shaders->success)
	{
		glGetProgramInfoLog(shaders->shader_program, 512, NULL,
			shaders->info_log);
		printf("%s\n%s\n", "ERROR::SHADER::PROGRAM::LINKING_FAILED\n",
			shaders->info_log);
	}
	glDeleteShader(shaders->vertex_shader);
	glDeleteShader(shaders->fragment_shader);
}

GLchar		*get_shader_source(char *filename, t_file_reader *reader)
{
	if (ft_strlen(reader->raw_file))
		ft_memdel((void **)&reader->raw_file);
	read_file(filename, reader);
	if (reader->raw_file)
		return ((GLchar*)reader->raw_file);
	else
		printf("Warning!!! Unreadable file %s", filename);
	return ("#version 400 core\n");
}
