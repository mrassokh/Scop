/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_instant_and_fill.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:50:28 by mrassokh          #+#    #+#             */
/*   Updated: 2018/04/10 14:50:30 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scope.h"

void		fill_buffers_by_prepared_data(t_programm *root)
{
	glBufferData(GL_ARRAY_BUFFER, root->vert_size, root->vertices,
											GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, root->indices_size,
											root->indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE,
											11 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 11 * sizeof(GLfloat),
												(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(GLfloat),
												(GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(GLfloat),
												(GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void		instant_buffers(t_programm *root)
{
	glGenVertexArrays(1, &root->ogl.vao[0]);
	glGenVertexArrays(1, &root->ogl.vao[1]);
	glGenBuffers(1, &root->ogl.vbo);
	glGenBuffers(1, &root->ogl.ebo);
	glBindVertexArray(root->ogl.vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, root->ogl.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, root->ogl.ebo);
}
