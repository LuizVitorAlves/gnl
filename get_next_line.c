#include "get_next_line.h"

static char	*read_file(int fd, char *backup)
{
	char	*buffer;
	int	count;
	
	if (!backup)
		backup = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	count = 1;
	while (count > 0 && !ft_strchr(backup, '\n'))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count < 0)
		{
			free(buffer);
			free(backup);
			return (NULL);
		}
		buffer[count] = '\0';
		backup = ft_strjoin(backup, buffer);
	}
	free(buffer);
	return (backup);
}

static char	*get_line(char *save)
{
	char	*line;
	int	i;

	if (!save || !*save)
		return (NULL);
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, save, i + 1);
	line[i + (save[i] == '\n' ? 1 : 0)] = '\0';
	return (line);
}

static char	*remove_line(char *save)
{
	int	i;
	char	*backup;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	backup = ft_strdup(save + i + 1);
	free(save);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char	*line;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = remove_line(save);
	return (line);
}
