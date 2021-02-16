/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:22:13 by flavon            #+#    #+#             */
/*   Updated: 2020/08/12 18:05:06 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.hpp"

static int		ft_check_all_line(t_line *content, char **first_str)
{
	if ((*first_str = (char *)malloc((content->length + 1))) == 0)
		return (-1);
	(*first_str)[content->length] = '\0';
	while (content->length)
	{
		content->length--;
		(*first_str)[content->length] = content->line[content->length];
	}
	free(content->line);
	if ((content->line = (char *)malloc(BUFFER_SIZE)) != 0)
		return (-1);
	return (1);
}

static int		ft_recheck_line(t_line *line, char **dst, size_t index)
{
	size_t	count;
	char	*tmp;
	size_t	length;

	count = 0;
	if ((*dst = (char *)malloc((index + 1))) == 0)
		return (-1);
	while (index > count)
	{
		(*dst)[count] = line->line[count];
		(*dst)[count + 1] = '\0';
		count++;
	}
	if ((tmp = (char *)malloc((line->length - count - 1))) == 0)
		return (-1);
	length = line->length;
	line->length = 0;
	while (++index < length)
		tmp[line->length++] = line->line[index];
	free(line->line);
	line->line = tmp;
	return (1);
}

static int		ft_check_line(t_line *line, char **src)
{
	size_t	index;

	*src = NULL;
	index = 0;
	while (line->line[index] != '\n' && line->length > index)
		index++;
	if (index == line->length && line->buff != BUFFER_SIZE && index != 0)
	{
		if ((ft_check_all_line(line, src)) == 0)
			return (-1);
		return (0);
	}
	else if (index < line->length)
		if ((ft_recheck_line(line, src, index)) == 0)
			return (-1);
	return (1);
}

static int		ft_list_elem(t_line *line, char **dst)
{
	char	*src;
	char	*tmp;
	char	*tmp_src;
	int		status;

	src = (char *)malloc(BUFFER_SIZE);
	if ((status = ft_check_line(line, &tmp_src)) == -1)
		return (-1);
	while (tmp_src == 0 && line->buff != 0)
	{
		if ((line->buff = (int)read(line->fd, src, BUFFER_SIZE)) == -1 ||
			(tmp = ft_strjoin(line->line, src, line->length, BUFFER_SIZE)) == 0)
			return (-1);
		free(line->line);
		line->line = tmp;
		line->length += line->buff;
		if ((status = ft_check_line(line, &tmp_src)) == -1)
			return (-1);
	}
	*dst = tmp_src;
	if (line->buff == 0)
		return (0);
	return (status);
}

int				get_next_line(int fd, char **line)
{
	static t_data 	*list = NULL;
	t_data 			*list_elem;
	int				out;

	if (fd < 0 || line == 0)
		return (-1);
	if ((list_elem = ft_list_get_elem(fd, list)) == NULL &&
		(list_elem = ft_list_new_add(fd, &list)) == NULL)
	{
		ft_list_clear(list);
		return (-1);
	}
	if (((out = ft_list_elem(list_elem->line, line))) == 0)
		ft_list_del_elem(list_elem, &list);
	if ((*line) == NULL)
	{
		if ((*line = (char *)malloc(sizeof(char))) == NULL)
		{
			ft_list_clear(list);
			return (-1);
		}
		**line = '\0';
	}
	return (out);
}
