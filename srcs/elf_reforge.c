/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_reforge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 10:32:01 by jguyet            #+#    #+#             */
/*   Updated: 2017/06/09 14:51:46 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

bool	replace_section(t_section *section, t_elf *elf)
{
	t_section	*tmp;
	int			augmente_off;

	tmp = elf->sections;
	augmente_off = 0;
	while (tmp)
	{
		if (ft_strcmp(section->name, tmp->name) == 0)
		{
			tmp->content = ft_strnew(section->data->sh_size);
			ft_bzero(tmp->content, section->data->sh_size);
			ft_memcpy(tmp->content, section->content, section->data->sh_size);
			//500 - 40 = 480
			//40 - 500 = -480
            printf("p_memsz %d, p_memsz2 %d\n", tmp->parent->data->p_memsz, section->parent->data->p_memsz);
			augmente_off = (int)section->data->sh_size - tmp->data->sh_size;
            printf("section->data->sh_size %d, tmp->data->sh_size %d, augmente_off %d\n", section->data->sh_size, tmp->data->sh_size, augmente_off);
            elf->len += augmente_off;
			tmp->data->sh_size = section->data->sh_size;
            while (tmp)
			{
				tmp->data->sh_offset = tmp->data->sh_offset + augmente_off;
				tmp = tmp->next;
			}
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}
