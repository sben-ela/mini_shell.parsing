#include "mini_shell.h"

// count number of redirect becouse we need it in malloc
int count_redirect(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while(line[i])
	{
		// ila kano >> mlas9in y3ni ghadii nrdha rir |>>| machiii |>||>| ghadii ikon count zayed y3nii ghadi nalloce kter mn l9yas ==> handle leak
		if((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
			count++;
		else if(line[i] == '>' || line[i] == '<')
			count++;
		i++;
	}
	return(count);
}

int	*skip_char_between_couts(char *line, char *new_line, int i, int j)
{
	int *tab = malloc(8);
	if(line[i] == '"')
	{
		new_line[j++] = line[i++];
			while(line[i] != '"')
				new_line[j++] = line[i++];
		new_line[j++] = line[i++];
	//printf("IN FUNCTION i:%d j:%d\n", i, j);
	}
	if(line[i] == '\'')
	{
		new_line[j++] = line[i++];
			while(line[i] != '\'')
				new_line[j++] = line[i++];
		new_line[j++] = line[i++];
	}
	//printf("%s\n", new_line[0]);
	tab[0] = i;
	tab[1] = j;
	return (tab);
}

int *skip_del(char *line, char *new_line, int i, int j)
{
	int *tab;

	tab = malloc(8);
	new_line[j++] = '|';
	new_line[j++] = '<';
	new_line[j++] = '<';
	new_line[j++] = '|';
	// skipp "<<"
	i += 2;
	// cpy the the string after <<
	while(line[i] && line[i] != '|')
	{
		new_line[j++] = line[i++];
	}
	tab[0] = i;
	tab[1] = j;
	return (tab);
}

void	parse_all(char *line, char *new_line, int i, int j)
{
	int *tab;

	while (line[i])
	{
		tab = skip_char_between_couts(line, new_line, i, j);
		i = tab[0];
		j = tab[1];
		free(tab);
		//if we have "<<" in this case we make the the dilimeter between to pipe like it "|<<|"
		if(line[i] == '<' && line[i + 1] == '<' && line[i + 2] != '<')
		{
			tab = skip_del(line, new_line, i, j);
			i += tab[0];
			j += tab[1];
			free(tab);
		}
		else if(line[i] == '>' && line[i + 1] == '>' && line[i + 2] != '>')
		{
			tab = skip_del(line, new_line, i, j);
			i += tab[0];
			j += tab[1];
			free(tab);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			new_line[j++] = '|';
			new_line[j++] = line[i++];
			new_line[j++] = '|';
			// cpy the the string after > or <
			while(line[i] && line[i] != '|')
				new_line[j++] = line[i++];
		}
		// cpy character in the new string
		new_line[j++] = line[i++];
	}
	// add null in the last of the new string
	new_line[j] = '\0';
}

char	*parse_redirect(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	j = i = 0;
	/// allocate to the new string
	if (!(new_line = malloc(ft_strlen(line) + 1 + (count_redirect(line) * 2))))
	{
		free(new_line);
		ft_error("malloc not allocate");
		return (0);
	}
	parse_all(line, new_line, i, j);
	/// make the redirect between two pipe becouse when i split with pipe the redirect will exist alone in a argument
	return(new_line);
}

