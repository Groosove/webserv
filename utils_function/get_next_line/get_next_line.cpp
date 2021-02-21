#include "get_next_line.hpp"

static int		ft_memclean(char *buffer, char *surplus)
{
	if (buffer)
		free(buffer);
	if (surplus)
		free(surplus);
	return (-1);
}

static int		check_errors(char **line, char **surplus, int bytes)
{
	if (!bytes && !(*surplus))
	{
		if (!(*line = gnl_strdup((char *)"", 0)))
			return (-1);
		return (0);
	}
	if (bytes < 0)
	{
		if (*surplus)
		{
			free(*surplus);
			*surplus = NULL;
		}
		return (-1);
	}
	return (1);
}

static int		check_result(char **line, char **surplus, int bytes)
{
	char		*tmp;
	char		*new_surplus;
	int			errors;

	if ((errors = check_errors(line, surplus, bytes)) < 1)
		return (errors);
	if ((tmp = gnl_strchr(*surplus, '\n')))
	{
		*tmp = '\0';
		if (!(new_surplus = gnl_strdup((tmp + 1), 0)))
			return (ft_memclean(NULL, *surplus));
		if (!(*line = gnl_strdup(*surplus, 1)))
			return (ft_memclean(new_surplus, *surplus));
		*surplus = new_surplus;
		return (1);
	}
	else if (gnl_strchr(*surplus, '\0'))
	{
		if (!(*line = gnl_strdup(*surplus, 1)))
			return (ft_memclean(NULL, *surplus));
		*surplus = NULL;
	}
	return (0);
}

static char		*new_surplus(char *surplus, char *buffer)
{
	char	*new_surplus;

	if (!surplus)
		return (gnl_strdup(buffer, 0));
	else
	{
		new_surplus = gnl_join(surplus, buffer);
		free(surplus);
		return (new_surplus);
	}
}

int				get_next_line(int fd, char **line)
{
	static char	*surplus = NULL;
	char		*buffer;
	int			bytes;

	if (fd < 0 || !line || BUFFER_SIZE < 1 ||
		!(buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes] = '\0';
		if (!(surplus = new_surplus(surplus, buffer)))
			return (ft_memclean(buffer, surplus));
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	ft_memclean(buffer, NULL);
	return (check_result(line, &surplus, bytes));
}
