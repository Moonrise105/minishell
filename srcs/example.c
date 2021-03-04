#include "minishell.h"

void	print(void *s) //печатает аргумент
{
	printf("%s\n", (char*)s);
}

void 	iter2(void *s) //эта функция итерируется уже по списку аргументов
{
	ft_lstiter(((t_command*)s)->args, print);
}

int main(void)
{
	
	t_command *command = (t_command*)malloc(sizeof(t_command));
	t_list *commands = ft_lstnew(command);

	char *buf = malloc(sizeof(char) * 20); //костыльный буфер
	buf[19] = '\0';
	int buf_pos = 0;


	int flag = 1; //флаг означающий первый ли это аргумент
	char *s = ft_strdup("ls -la ;echo hello ;cat -e");
	int i = 0;
	t_command *com_tmp; //просто временная переменная
	t_list *first_command = commands;
	while (s[i])
	{
		buf[buf_pos] = s[i];
		if (s[i] == ' ')
		{
			buf[buf_pos] = '\0';
			com_tmp = commands->content;
			if (flag)
			{
				com_tmp->args = ft_lstnew(ft_strdup(buf));
				flag = 0;
			}
			else
			{
				ft_lstadd_back(&com_tmp->args, ft_lstnew(ft_strdup(buf)));
			}
			buf_pos = -1;
		}
		if (s[i] == ';')
		{
			command = NULL;
			command = (t_command*)malloc(sizeof(t_command));
			ft_lstadd_back(&commands, ft_lstnew(command));
			commands = commands->next;
			buf_pos = -1;
			flag = 1;
		}
		++i;
		++buf_pos;
	}
	buf[buf_pos] = '\0';
	ft_lstadd_back(&com_tmp->args, ft_lstnew(ft_strdup(buf)));


	char **dirs = malloc(sizeof(char*) * 5);
	dirs[0] = ft_strdup("/home/moonrise/.local/bin");
	dirs[1] = ft_strdup("/usr/local/bin");

	dirs[2] = ft_strdup("/usr/sbin");
	dirs[3] = ft_strdup("/usr/bin");
	dirs[4] = NULL;
	char *res;
	res = parse_dirs(dirs, "iptest");
	if (res)
		printf("%s\n", res);
	return (0);
}