/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:21:03 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/10 15:21:06 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

void	check_flag(int *flag)
{
	if (*flag)
		*flag = 0;
	else
		*flag = 1;
}

void	handle_rotation_keys(int key, t_programm *root)
{
	if (key == SDLK_a)
		root->matr.v_rotate.y += 45;
	if (key == SDLK_d)
		root->matr.v_rotate.y -= 45;
	if (key == SDLK_w)
		root->matr.v_rotate.x += 45;
	if (key == SDLK_s)
		root->matr.v_rotate.x -= 45;
	if (key == SDLK_x)
		root->matr.v_rotate.z += 45;
	if (key == SDLK_z)
		root->matr.v_rotate.z -= 45;
}

void	handle_translate_scale_keys(int key, t_programm *root)
{
	if (key == SDLK_LEFT)
		root->matr.v_translate.x -= 0.2;
	else if (key == SDLK_RIGHT)
		root->matr.v_translate.x += 0.2;
	else if (key == SDLK_UP)
		root->matr.v_translate.y += 0.2;
	else if (key == SDLK_DOWN)
		root->matr.v_translate.y -= 0.2;
	else if (key == SDLK_PAGEDOWN)
		root->matr.v_translate.z -= 0.2;
	else if (key == SDLK_PAGEUP)
		root->matr.v_translate.z += 0.2;
	else if (key == SDLK_KP_PLUS)
		vector_product_float(&root->matr.v_scale, 1.25);
	else if (key == SDLK_KP_MINUS)
	{
		if (root->matr.v_scale.x > 0.001)
			vector_product_float(&root->matr.v_scale, 0.8);
	}
}

void	handle_check_key(int key, enum e_color_flag *color_state,
										int *rot_flag, t_programm *root)
{
	if (key == SDLK_SPACE)
	{
		if (*color_state != 2)
			(*color_state)++;
		else
			(*color_state) = 0;
	}
	else if (key == SDLK_r)
		check_flag(rot_flag);
	else if (key == SDLK_l)
		check_flag(&root->gen_text);
	else if (key == SDLK_i)
		check_flag(&root->has_shading);
	else if (key == SDLK_k)
		check_flag(&root->has_texture);
}

void	event_handler(int *cycl, enum e_color_flag *color_state,
											int *rot_flag, t_programm *root)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		{
			*cycl = 0;
			break ;
		}
		if (event.type == SDL_KEYDOWN)
		{
			handle_translate_scale_keys(event.key.keysym.sym, root);
			handle_rotation_keys(event.key.keysym.sym, root);
			handle_check_key(event.key.keysym.sym, color_state, rot_flag, root);
		}
	}
}
