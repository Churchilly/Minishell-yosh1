/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:26:46 by obastug           #+#    #+#             */
/*   Updated: 2025/06/03 15:08:23 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	expander(t_token **tokens);
char	*expand_dollar_in_dquote(char *token_value);
t_token	*expand_dollar(t_token *tokens);
char	*expand_quotes(char *token_value);
void	expand_tilde(t_token *tokens);
int		have_heredoc(t_token *tokens);
int		dollar_in_tokens(t_token *tokens);
int		dollar_in_dquote(char *str);
int		have_quotes(char *str);
int		tilde_in_tokens(t_token *tokens);
void	replace_dollars(t_token *tokens);
t_token	*divide_tokens(t_token *tokens);
char	*create_new_value(char *token_val);
void	pass_env_var(char **token_val, char ***env_vars);
int		get_env_vars(char *token_value, char **env_vars);
t_token	*allocate_divided(t_token *tokens);
int		count_divided(char *s);