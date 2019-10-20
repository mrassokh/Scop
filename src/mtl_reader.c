/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 12:26:53 by mrassokh          #+#    #+#             */
/*   Updated: 2018/03/24 12:26:55 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_parser.h"
#include "scope.h"

void		parse_mtl_string(char *trim_str, t_material *material)
{
	char	*token;

	token = strtok(trim_str, " ");
	if (!token)
		return ;
	if (!ft_strcmp(token, "Ka"))
		parse_ambient(trim_str + 3, material);
	else if (!ft_strcmp(token, "Kd"))
		parse_diffuse(trim_str + 3, material);
	else if (!ft_strcmp(token, "Ks"))
		parse_specular(trim_str + 3, material);
	else if (!ft_strcmp(token, "d"))
	{
		if (!sscanf(trim_str + 2, "%f", &material->dissolve))
			material->dissolve = 1.0;
	}
	else if (!ft_strcmp(token, "Ns"))
		parse_refr(trim_str + 3, material);
	else if (!ft_strcmp(token, "illum"))
		parse_illum(trim_str + 6, material);
}

void		fill_material_properties(char **properties, t_material *material,
			char *trim_name)
{
	int		i;
	char	*trim_str;

	i = 1;
	while (properties[i++])
	{
		trim_str = ft_strtrim(properties[i - 1]);
		if (trim_str[0] != '#' && ft_strlen(trim_name))
		{
			parse_mtl_string(trim_str, material);
		}
		ft_memdel((void **)&trim_str);
		ft_memdel((void **)&properties[i - 1]);
	}
	ft_memdel((void **)&properties);
}

void		split_material_to_properties(t_mtl_reader *reader)
{
	int			i;
	t_material	material;
	t_list		*new_material;
	char		*trim_name;

	i = 1;
	free(reader->split_file_to_material[0]);
	while (reader->split_file_to_material[i++])
	{
		ft_bzero(&material, sizeof(t_material));
		reader->split_material_to_properties = ft_strsplit_with_empty(
				reader->split_file_to_material[i - 1], '\n');
		trim_name = ft_strtrim(reader->split_material_to_properties[0]);
		ft_memdel((void **)&reader->split_material_to_properties[0]);
		fill_material_properties(reader->split_material_to_properties,
			&material, trim_name);
		if (ft_strlen(trim_name))
		{
			material.name = ft_strdup(trim_name);
			new_material = ft_lstnew(&material, sizeof(material));
			ft_lstpushback(&reader->materials, new_material);
		}
		ft_memdel((void **)&reader->split_file_to_material[i - 1]);
		ft_memdel((void **)&trim_name);
	}
}

int			parse_mtl(char *filename, t_mtl_reader *reader)
{
	char	*trim_str;
	char	*path_mtl;

	trim_str = ft_strtrim(filename);
	path_mtl = ft_strjoin("images/", trim_str);
	printf("read mtl file: %s\n", path_mtl);
	read_file(path_mtl, &reader->file_reader);
	free(trim_str);
	free(path_mtl);
	reader->split_file_to_material = ft_str_strsplit(
		reader->file_reader.raw_file, "newmtl");
	split_material_to_properties(reader);
	free(reader->split_file_to_material);
	return (1);
}
