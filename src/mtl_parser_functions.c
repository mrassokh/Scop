/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_parser_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:47:50 by mrassokh          #+#    #+#             */
/*   Updated: 2018/03/31 15:47:52 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_parser.h"
#include "scope.h"

void	parse_ambient(char *str, t_material *material)
{
	int		matches;

	matches = sscanf(str, "%f %f %f", &material->ambient[0],
		&material->ambient[1], &material->ambient[2]);
	if (matches != 3)
	{
		printf("incorrect ambient format in material file\n");
		exit(0);
	}
}

void	parse_diffuse(char *str, t_material *material)
{
	int		matches;

	matches = sscanf(str, "%f %f %f", &material->diffuse[0],
		&material->diffuse[1], &material->diffuse[2]);
	if (matches != 3)
	{
		printf("incorrect diffuse format in material file\n");
		exit(0);
	}
}

void	parse_specular(char *str, t_material *material)
{
	int		matches;

	matches = sscanf(str, "%f %f %f", &material->specular_refl[0],
		&material->specular_refl[1], &material->specular_refl[2]);
	if (matches != 3)
	{
		printf("incorrect specular_refl format in material file\n");
		exit(0);
	}
}

void	parse_refr(char *str, t_material *material)
{
	int		matches;

	matches = sscanf(str, "%f", &material->ns);
	if (matches != 1)
	{
		printf("incorrect refraction(Ns) format in material file\n");
		exit(0);
	}
}

void	parse_illum(char *str, t_material *material)
{
	int		matches;

	matches = sscanf(str, "%d", &material->illum);
	if (matches != 1)
	{
		printf("incorrect refraction(Ns) format in material file\n");
		exit(0);
	}
}
