#include "lexer.h"
#include "environment.h"
#include "str.h"

void    expand_tilde(t_token *tokens)
{
	int 	i;
	int		j;
	char	*home;
	int		tilde_count;
	char	*final_token;

	home = get_variable("HOME");
	if (!home || !*home)
		return ;
	i = 0;
	tilde_count = 0;
	while (tokens[i].value)
	{
		j = 0;
		while (tokens[i].value[j])
		{
			if (tokens[i].value[j] == '~')
				tilde_count++;
			j++;
		}
		final_token = gc_calloc((tilde_count * ft_strlen(home) - tilde_count) + ft_strlen(tokens[i].value) + 1, SECTION_LA);
		j = 0;
		while (tokens[i].value[j])
		{
			if (tokens[i].value[j] != '~')
				final_token[ft_strlen(final_token)] = tokens[i].value[j];
			else
				ft_strcpy(final_token + ft_strlen(final_token), home);
			j++;
		}
		final_token[ft_strlen(final_token)] = '\0';
		tokens[i].value = final_token;
		i++;
	}
}