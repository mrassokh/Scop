/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 09:28:42 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/17 09:28:44 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

void		set_projection_matrix(t_programm *root)
{
	root->matr.projection_loc = glGetUniformLocation(
									root->shaders.shader_program, "projection");
	glUniformMatrix4fv(root->matr.projection_loc, 1, GL_FALSE,
									(const GLfloat *)root->matr.projection);
}

void		set_model_matrix(t_programm *root, t_processing *proc)
{
	vector_set(&proc->axe_vector, 1, 0, 0);
	proc->x_rot = get_quaternion(&proc->axe_vector, root->matr.v_rotate.x);
	vector_set(&proc->axe_vector, 0, 1, 0);
	proc->y_rot = get_quaternion(&proc->axe_vector, root->matr.v_rotate.y);
	vector_set(&proc->axe_vector, 0, 0, 1);
	proc->z_rot = get_quaternion(&proc->axe_vector, root->matr.v_rotate.z);
	proc->base_quat = mul_quaternion(mul_quaternion(proc->y_rot,
												proc->x_rot), proc->z_rot);
	fill_rotate_matrix(&proc->base_quat, root->matr.rotate);
	fill_scale_matrix(root->matr.scale, &root->matr.v_scale);
	fill_translate_matrix(root->matr.translate, &root->matr.v_translate);
	root->matr.rotate_loc = glGetUniformLocation(root->shaders.shader_program,
									"rotate");
	root->matr.translate_loc = glGetUniformLocation(
									root->shaders.shader_program, "translate");
	root->matr.scale_loc = glGetUniformLocation(root->shaders.shader_program,
									"scale");
	glUniformMatrix4fv(root->matr.rotate_loc, 1, GL_FALSE,
									(const GLfloat *)root->matr.rotate);
	glUniformMatrix4fv(root->matr.translate_loc, 1, GL_FALSE,
									(const GLfloat *)root->matr.translate);
	glUniformMatrix4fv(root->matr.scale_loc, 1, GL_FALSE,
									(const GLfloat *)root->matr.scale);
}

void		set_color_managment(t_programm *root, t_processing *proc)
{
	proc->diffuse_color_loc = glGetUniformLocation(root->shaders.shader_program,
									"diffuse");
	glUniform3f(proc->diffuse_color_loc, proc->mat.diffuse[0],
									proc->mat.diffuse[1], proc->mat.diffuse[2]);
	proc->light_pos_loc = glGetUniformLocation(root->shaders.shader_program,
									"lightPos");
	vector_set(&root->light_pos, 120, 120, -120);
	glUniform3f(proc->light_pos_loc, root->light_pos.x,
									root->light_pos.y, root->light_pos.z);
	proc->frag_flags_loc = glGetUniformLocation(root->shaders.shader_program,
									"frag_flags");
	glUniform4f(proc->frag_flags_loc, root->gen_text, root->has_texture,
									proc->color_state, root->has_shading);
}

void		render(t_programm *root, t_obj_reader *reader, t_processing *proc)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(root->shaders.shader_program);
	if (proc->rot_flag)
	{
		root->matr.v_rotate.y -= 1;
		SDL_Delay(20);
	}
	set_model_matrix(root, proc);
	set_projection_matrix(root);
	set_color_managment(root, proc);
	glBindTexture(GL_TEXTURE_2D, root->ogl.texture);
	glBindVertexArray(root->ogl.vao[0]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, reader->index_counter, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	SDL_GL_SwapWindow(root->window);
}
