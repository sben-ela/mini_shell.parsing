#include "mini_shell.h"


t_shell	*ft_lstlast(t_shell *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

int check_edges(char *str)
{
	if(str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (1);
	if(str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (2);
	else
		return (0);
}

t_shell	*ft_lstnew(char *content, int type, char **env)
{
	t_shell	*x;
	int i;
	int j;

	j = 0;
	i = 0;
	x = malloc(sizeof(t_shell));
	if (!x)
		return (NULL);
	x->cmds = ft_split(content, ' ');
	while(x->cmds[i])
	{
		if(x->cmds[i][0] != '\'' && x->cmds[i][ft_strlen(x->cmds[i])] != '\'')
			x->cmds[i] = get_value(x->cmds[i], env);
		if(i > 0 && !ft_strcmp(x->cmds[i - 1], "echo") && check_edges(x->cmds[i]) == 1)
			x->cmds[i] = ft_strtrim(x->cmds[i], "\"");
		else if(i > 0 && !ft_strcmp(x->cmds[i - 1], "echo") && check_edges(x->cmds[i]) == 2)
			x->cmds[i] = ft_strtrim(x->cmds[i], "\'");
		else if (i > 0 || (i == 0 && !count_char(x->cmds[i], ' ')))
		{
			x->cmds[i] = handle_param(x->cmds[i], '"');
			x->cmds[i] = handle_param(x->cmds[i], '\'');
		}
		i++;
	}
    x->type = type;
	x->next = NULL;
	return (x);
}

void	ft_lstadd_back(t_shell **lst, t_shell *new)
{
	t_shell	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

t_shell *parse_line(char *line, char **env)
{
	t_shell	*shell;
	char	**args;
	int		i;
	int		j;

	i = -1;
	j = 0;
	shell = 0;
	// split line with pipe
	args = ft_split(line, '|');
	while(args[++i])
	{
		args[i] = ft_strtrim(args[i], " ");
	}
	i = 0;
	while (args[i])
	{
		if(!strcmp(args[i], ">>"))
			ft_lstadd_back(&shell, ft_lstnew(args[i++], DELIMITER, env));
		else if(!strcmp(args[i], "<<"))
			ft_lstadd_back(&shell, ft_lstnew(args[i++], APPEND, env));
		else if(!strcmp(args[i], ">"))
			ft_lstadd_back(&shell, ft_lstnew(args[i++], REDIR_OUTPUT, env));
		else if(!strcmp(args[i], "<"))
			ft_lstadd_back(&shell, ft_lstnew(args[i++], REDIR_INPUT, env));
		// creat new node and add it to shell list(shell)
		ft_lstadd_back(&shell, ft_lstnew(args[i], 3, env));
		i++;
	}
	return(shell);
}

int	ft_checkspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

void sigint_handler(int sig) {
	if(sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 1);
		rl_redisplay();
	}
	else if(sig == SIGQUIT)
			return ;
}

void mini_shell(char **env)
{
	char *read;
	t_shell *shell;
	while(1)
	{
		read = readline("\033[0;32mMinishell>> \033[0m");
		if(!read)
			exit(0);
		add_history(read);
		read += ft_checkspace(read);
		if (!handle_redirect(read) && !count_single_couts(read) && !count_double_couts(read) && !handle_pipes(read))
		{
			read = parse_redirect(read);
			//printf("read : %s\n", read);
			shell = parse_line(read, env);
			int i = 0;
			while(shell)
			{
				i = 0;
				while(shell->cmds[i])
				{
					printf("%s ", shell->cmds[i++]);
				}
				printf("\n");
				shell = shell->next;	
			}
		}
		else
			ft_error("syntax error");
	}
}
int main(int ac, char **av, char **env)
{
	(void)av;
	if(ac != 1)
	{
		ft_error("invalid number of argument");
		return(0);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	mini_shell(env);
	return 0;
}
// ech'o "hello wor'ld"
// ech"o 'hello wor"ld'