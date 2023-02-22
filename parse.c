#include "mini_shell.h"

int handle_pipes(char *line)
{
	char *str;

	str = ft_strtrim(line, " ");
	if(str[0] == '|' || str[ft_strlen(str) - 1] == '|')
		return (1);
	return (0);
}

int	parse_syntax(char *line)
{
	int i;
    char c;

	i = 0;
    if(handle_pipes(line))
        return (1);
	// hanldle if the line par example == "<"
	line = ft_strtrim(line, "\"");
	////hanldle if the line par example == '<'
	line = ft_strtrim(line, "\'");
	while (line[i])
	{
        if(line[i] == '\'' || line[i] == '\"')
        {
            c = line[i];
            i++;
            while(line[i] && line[i] != c)
                i++;
        }
        //if((line[i] == '|' && line[i + 1] == '|') || (line[i] == '|' && !line[i + 1]))
        //    return (1);
        //if(line[i] == '<' && line[i + 1] == '>')
        //    return (1);
		//if (line[i] == '>' || line[i] == '<')
		//{
		//	// handle if the redirect exist in the last of the line
		//	if(!line[i + 1])
		//		return(1);
		//	if(line[i + 1] == line[i] && line[i + 2] == line[i])
		//		return (1);
		//}
		if(line[i] == '|')
		{
			i++;
			while(line[i] == ' ')
				i++;
			if(!line[i] || line[i] == '|')
				return (1);
		}
		i++;
	}
	return(0);
}