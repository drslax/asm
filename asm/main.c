#include "asm.h"

int		is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
	|| c == '\f' | c == '\0')
		return (1);
	return (0);
}

void	check_file_name(t_asm *data, char *path)
{
	
	char	*file_name;
	int		len;

	if (!(file_name = grab_name(path)))
		file_name = path;
	len = ft_strlen(file_name);
	if (file_name[len - 2] == '.' && file_name[len - 1] == 's' && len >= 3)
	{
		file_name[len - 2] = '\0';
		data->file_name = file_name;
	}
	else
	{
		printf("ERROR\n");
		exit(-1);
	}
}

void	get_instruction(t_asm *data)
{
	int		i;
	int		j;
	char	*element;

	i = 0;
	printf("*");
	while (data->line[i])
	{ 
		while (is_blank(data->line[i]))
			i++;
		j = i;
		if (!is_blank(data->line[i]))
			while (!is_blank(data->line[i]))
				i++;
		else
				return ;
		element = ft_strsub(data->line, j, i - j);
		if (data->line[i - j - 1] == ':')
		{
			add_list(&(data->lexer), element, LABEL, data);
			printf("%s||", data->lexer->name);
		}
		else
		{
			add_list(&(data->lexer), element, INST, data);
			printf("%s||", data->lexer->name);
		}
		data->lexer->next != NULL ? data->lexer = data->lexer->next : 0;
	}
	printf("*\n");
}

void	get_command(t_asm *data)
{
	char	*command;
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (!is_blank(data->line[i]))
		i++;
	command = ft_strsub(data->line, 1, i - 1);
	while (is_blank(data->line[i]))
		i++;
	if (data->line[i] == '"')
	{
		j = ++i;
		while (data->line[i] && data->line[i] != '"')
			i++;
		str = ft_strsub(data->line, j, i - j);
		printf("/%s/\n", str);
	}
	printf("|%s|\n", command);
}

void	parse_asm(t_asm *data)
{
	int		i;

	i = 0;
	while (is_blank(data->line[i]) && data->line[i])
		i++;
	if (data->line[i] == '.')
		get_command(data);
	else if (!ft_isblank(data->line[i]))
		get_instruction(data);
}

int		main(int argc, char **argv)
{
	t_asm	*data;
	int		ret;

	if (!(data = (t_asm *)ft_memalloc(sizeof(t_asm))))
		return (-1);
	if ((data->s_fd = open(argv[1], O_RDONLY)) <= 0)
			exit(-1);
	check_file_name(data, argv[1]);
	printf("%s, %d\n", data->file_name, data->s_fd);
	while (get_next_line(data->s_fd, &(data->line)))
	{
		if (data->line[0] != '\0')
			parse_asm(data);
		free(data->line);
	}
	return (0);
}
