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

int	handle_redirect(char *line)
{
	int i;

	i = 0;
	if (line[0] == '|')
		return (1);
	// hanldle if the line par example == "<"
	line = ft_strtrim(line, "\"");
	// hanldle if the line par example == '<'
	line = ft_strtrim(line, "\'");
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			// handle if the redirect exist in the last of the line
			if(!line[i + 1])
				return(1);
			if(line[i + 1] == line[i] && line[i + 2] == line[i])
				return (1);
		}
		i++;
	}
	return(0);
}

char	*parse_redirect(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	/// allocate to the new string
	if (!(new_line = malloc(ft_strlen(line) + 1 + (count_redirect(line) * 2))))
	{
		ft_error("malloc not allocate");
		return (0);
	}
	/// make the redirect between two pipe becouse when i split with pipe the redirect will exist alone in a argument
	while (line[i])
	{
		if(line[i] == '"')
		{
			new_line[j++] = line[i++];
				while(line[i] != '"')
					new_line[j++] = line[i++];
			new_line[j++] = line[i++];
		}
		if(line[i] == '\'')
		{
			new_line[j++] = line[i++];
				while(line[i] != '\'')
					new_line[j++] = line[i++];
			new_line[j++] = line[i++];
		}
		//if we have "<<" in this case we make the the dilimeter between to pipe like it "|<<|"
		if(line[i] == '<' && line[i + 1] == '<' && line[i + 2] != '<')
		{
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
		}
		else if(line[i] == '>' && line[i + 1] == '>' && line[i + 2] != '>')
		{
			new_line[j++] = '|';
			new_line[j++] = '>';
			new_line[j++] = '>';
			new_line[j++] = '|';
			// skipp ">>"
			i += 2;
			// cpy the the string after >>
			while(line[i] && line[i] != '|')
			{
				new_line[j++] = line[i++];
			}
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			new_line[j++] = '|';
			new_line[j++] = line[i++];
			new_line[j++] = '|';
			// cpy the the string after > or <
			while(line[i] && line[i] != '|')
			{
				new_line[j++] = line[i++];
			}
		}
		// cpy character in the new string
		new_line[j++] = line[i++];
	}
	// add null in the last of the new string
	new_line[j] = '\0';
	return(new_line);
}

int handle_pipes(char *line)
{
	char *str;

	str = ft_strtrim(line, " ");
	if(str[0] == '|' || str[ft_strlen(str) - 1] == '|')
		return (1);
	return (0);
}