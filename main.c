#include "norm.h"

int		get_tabs(char *s)
{
	int		tabs;

	tabs = 0;
	while (*s)
	{
		if (*s == '\t')
			tabs += TAB_SIZE - 1;
		s++;
	}
	return (tabs);
}

void	get_lines_lens(int fd)
{
	char	*now;
	int		ln;
	int		len;

	ln = 1;
	while (get_next_line(fd, &now) > 0)
	{
		len = ft_strlen(now);
		len += get_tabs(now);
		if ((len = ft_strlen(now)) > MAX_LINE_LEN)
			printf("Error: line %d have %d characters\n", ln, len);
		free(now);
		ln++;
	}
}

void	go_line(char *s, int *brack)
{
	while (*s)
	{
		if (*s == '{')
			(*brack)++;
		if (*s == '}')
			(*brack)--;
		s++;
	}
}

void	get_functions_lens(int fd)
{
	char	*now;
	char	*func;
	int		func_num;
	int		ln;
	int		brack;
	int		count;
	int		count_func;

	ln = 0;
	func = 0;
	brack = 0;
	now = 0;
	count_func = 0;
	while (get_next_line(fd, &now) > 0)
	{
		ln++;
		go_line(now, &brack);
		if (brack > 0)
		{
			count_func++;
			count = 0;
			while (get_next_line(fd, &now) > 0 && brack > 0)
			{
				ln++;
				count++;
				go_line(now, &brack);
			}
			count--;
			ln++;
			if (count > MAX_FUNCTION_LEN)
				printf("Error: line %d\nFunction %s: have %d lines\n\n", func_num, func, count);
		}
		if (func != 0)
			free(func);
		func = now;
		func_num = ln;
	}

	if (func != 0)
		free(func);
	if (count_func > MAX_FUNCTIONS_IN_FILE)
		printf("\nError: file have %d functions\n", count_func);
}

void	start_norm(char *fname)
{
	int		fd;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		printf("Error reading file\n");
	get_lines_lens(fd);
	close(fd);
	printf("\n");
	fd = open(fname, O_RDONLY);
	get_functions_lens(fd);
	close(fd);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: my_norm filename\n");
		return (0);
	}
	system(CLEAR_CONSOLE);
	start_norm(argv[1]);
	return (0);
}
