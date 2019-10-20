/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 10:12:46 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/17 10:12:48 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

void	load_texture(t_programm *root)
{
	t_bmp_image		*im;
	unsigned char	*imagedata;

	if (!(im = image_bmp_load("./textures/tiger.bmp")))
	{
		printf("Warning! Texture was not loaded\n");
		return ;
	}
	imagedata = (unsigned char*)im->data;
	glGenTextures(1, &root->ogl.texture);
	glBindTexture(GL_TEXTURE_2D, root->ogl.texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im->width, im->height,
							0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	free(imagedata);
	free(im);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	set_material(t_obj_reader *reader, t_material *mat)
{
	if (reader->mtl_reader.materials)
		*mat = *((t_material*)reader->mtl_reader.materials->content);
	else
	{
		mat->ambient[0] = 1.0f;
		mat->ambient[1] = 1.0f;
		mat->ambient[2] = 1.0f;
		mat->diffuse[0] = 1.0f;
		mat->diffuse[1] = 0.0f;
		mat->diffuse[2] = 0.0f;
		mat->specular_refl[0] = 0.0f;
		mat->specular_refl[1] = 1.0f;
		mat->specular_refl[2] = 0.0f;
		mat->dissolve = 1.0f;
		mat->illum = 2;
		mat->name = ft_strdup("material");
	}
}

void	fill_settings(t_obj_reader *reader, t_programm *root,
													t_processing *proc)
{
	set_material(reader, &proc->mat);
	root->has_normal = reader->has_normal;
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	proc->cycl = 1;
	root->matr.projection = create_projection_matrix(85, 1, 0.01, 10);
	root->matr.v_translate.z =
		(3.5 * find_max_size(&reader->first_view.max_size)) / tan(85 * ANGLE);
	vector_set(&root->matr.v_scale, 1, 1, 1);
	fill_scale_matrix(root->matr.scale, &root->matr.v_scale);
	fill_translate_matrix(root->matr.translate, &root->matr.v_translate);
	proc->color_state = define;
	proc->rot_flag = 0;
}
