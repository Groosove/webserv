/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@21-school.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:22:22 by flavon            #+#    #+#             */
/*   Updated: 2020/08/11 15:22:24 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_HPP
# define GET_NEXT_LINE_HPP

# define BUFFER_SIZE 32

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef struct			s_line
{
	char				*line;
	size_t				length;
	int					fd;
	int					buff;
}						t_line;

typedef struct			s_data
{
	t_line				*line;
	struct s_data		*next;
}						t_data;

void					ft_list_del_elem(t_data *list, t_data **begin_list);
int						get_next_line(int fd, char **line);
t_data					*ft_list_get_elem(int fd, t_data *list);
void					ft_list_clear(t_data *list);
t_data					*ft_list_new_add(int fd, t_data **begin_list);
char					*ft_strjoin(char *s1, char *s2, size_t len1, size_t len2);

#endif
