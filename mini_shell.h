/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:36:00 by sben-ela          #+#    #+#             */
/*   Updated: 2023/02/21 16:15:10 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINI_SHELL_H
# define  MINI_SHELL_H

#define	CMD 3
#define	REDIR_INPUT 0
#define	REDIR_OUTPUT 1
#define	DELIMITER 4
#define	APPEND 5

#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<readline/readline.h>
#include	<readline/history.h>
#include	<fcntl.h>
#include	<sys/wait.h>
#include	<sys/errno.h>
#include	<string.h>

typedef	struct	shell
{
	int				type;
	char			*cmd;
	char			**cmds;
	char			**paths;
	char			*argv;
	struct shell	*next;
	char **env;
}	t_shell;

void	ft_error(char *str);
int		ft_strchr(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
char	**ft_split(char const *str, char c);
char	*parse_redirect(char *line);
//util	
int		ft_isalpha(int c);
int		count_redirect(char *line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_shell	*ft_lstlast(t_shell *lst);
void	ft_lstadd_back(t_shell **lst, t_shell *new);
int		count_char(char *str, char c);
char	*handle_param(char *str, char c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strjoin(char *left_str, char *buff);
void	ft_putstr_fd(char *s, int fd);
int		handle_redirect(char *line);
int		ft_checkspace(const char *str);
int		count_single_couts(char *line);
int		count_double_couts(char *line);
char	**second_split(char const *s, char c);
char   	*get_value(char *str,char **env);
int		ft_isalnum(int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *source);
int handle_pipes(char *line);
#endif
