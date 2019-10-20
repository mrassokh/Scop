/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scope.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:24:19 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/17 10:24:21 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

int			initialize(t_programm *root)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return (0);
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	root->window = SDL_CreateWindow("SCOP", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_OPENGL);
	root->gl_context = SDL_GL_CreateContext(root->window);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	return (1);
}

void		quit_programm(t_programm *root)
{
	glDeleteVertexArrays(1, &root->ogl.vao[0]);
	glDeleteVertexArrays(1, &root->ogl.vao[1]);
	glDeleteVertexArrays(1, &root->ogl.vbo);
	SDL_GL_DeleteContext(root->gl_context);
	SDL_DestroyWindow(root->window);
	SDL_Quit();
	exit(0);
}

int			main(int argc, char **argv)
{
	t_obj_reader	reader;
	t_programm		root;
	t_processing	proc;

	if (argc == 2)
		parse_obj(argv[1], &reader);
	else
	{
		printf("Warning! You should pass one file. Program switch to default");
		parse_obj("./images/teapot2.obj", &reader);
	}
	prepare_buffer_data(&root, &reader);
	if (!initialize(&root))
		return (1);
	load_texture(&root);
	create_shader_program(&root.shaders);
	instant_buffers(&root);
	fill_buffers_by_prepared_data(&root);
	fill_settings(&reader, &root, &proc);
	while (proc.cycl)
	{
		event_handler(&proc.cycl, &proc.color_state, &proc.rot_flag, &root);
		render(&root, &reader, &proc);
	}
	quit_programm(&root);
}
