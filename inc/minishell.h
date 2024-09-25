/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:11:22 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/10 10:09:21 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>

# define RED "\e[0;31m"
# define RESET "\e[0m"

# define CMD_ERR ": command not found"
# define FD_ERR ": No such file or directory"
# define ARG_ERR ": too many arguments"
# define NUM_ERR ": numeric argument required"
# define EF "bash: warning: here-document at line delimited by end-of-file"

# define BGRN "\e[1;32m"
# define CYN "\e[0;36m"
# define BCYN "\e[1;36m"

extern int	g_status;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmds
{
	char			*line;
	char			**envp;
	char			**cmd_tab;
	char			**infile;
	char			**outfile;
	char			**h_doc;
	int				fd_in;
	int				fd_out;
	t_token			*tok;
	int				*pipe;
	int				*prev_pipe;
	pid_t			pid;
	int				here_doc_status;
	int				status_set;
	struct s_cmds	*first;
	struct s_cmds	*next;
}			t_cmds;

typedef struct s_adr
{
	void			*address;
	struct s_adr	*next;
}	t_adr;

typedef struct s_expand
{
	char	*line;
	char	*newline;
	char	**args;
	int		len;
	int		count;
	t_cmds	*info;
}	t_expand;

typedef struct s_split
{
	char	*str;
	char	*end;
	char	*s;
	char	**result;
	int		mod;
}	t_split;

/*		--Funtion for list--		*/
int		ft_lstadd_back(t_cmds **li, char **envp, t_adr *adr);

/*		--Funtion for expand--		*/
char	*expand(char *line, t_cmds *info);
char	*expand_hdoc(char *line, t_cmds *info);

char	*get_var(char *name, t_cmds *info);
void	init_expand(t_expand *expand, char *line, t_cmds *info);
char	*get_args(t_expand *expand, int save, int j, int mod);
char	**extract_args(t_expand *expand, int mod);
char	*place_args(t_expand *expand, int *i, int nb);
int		count_args(char *line);
int		skip_agrs(char *line, int i);

int		count_quotes(char *line);
int		check_quotes_mod(char c, int mod);
void	copy_char(char *line, int *j, int *i, char *dest);

/*		--Funtion for line_check--		*/
int		line_check(char *line);

int		check_whitespace(char *line);
int		check_char(char *s, char *tofind);
int		is_charset(char s, char *charset);
int		locate_char(char *s, char *tofind);
int		skip_cmd(char *line, int *i);

char	**dup_tab(char **tab, t_adr *adr);

/*		--Funtion for spliter--		*/
char	**spliter(char *s, char *str, char *end);

int		redirec(t_split *split, unsigned int i, unsigned int k,
			unsigned int save);
int		check_spchar(t_split *sp, int k);
int		skip_charset(t_split *sp, int k);
void	init_split(t_split *split, char *s, char *str, char *end);
int		skip_word(t_split *sp, int i, int mod);

/*		--Funtion for redirections--		*/
int		locate_infile_start(t_cmds *info);
int		locate_redirection_end(t_cmds *info);

char	*get_redirection(char *str, int i, int *mod);
int		skip_redirection(char *line, int i, int *mod);
char	**update_tab(char **tab);
int		h_doc_case(t_cmds *info, int *i, int *mod);
int		infile_case(t_cmds *info, int *i, int *mod);
int		outfile_case(t_cmds *info, int *i, int *mod);
int		out_mod_case(char *line, int *i);
char	*skip_quotes(char *str, int *status);
int		nb_of_quotes(char *str);

/*		--Funtion for split_expand--		*/
char	**split_expand(char **tab);

int		check_hiden_space(char *s);
int		count_hiden_space(char *s);

/*		--utils--		*/
void	init_all(t_cmds *info, t_adr *adr);
void	init_cmds(t_cmds *info, char **envp);
void	init_perma(t_cmds *info, char **envp, t_adr *perma);
int		check_mod(char *line, int *mod, int i);
void	*freetab(char **result, int n);
int		tab_len(char **tab);
void	skip_whitespaces(char *line, int *i);
void	fix_status(void);
void	clear_all(t_adr perma);

/*		--golden garbage--		*/
void	ft_lstrm_addback(t_adr **li);
int		ft_lstadd_addback(t_adr **li, void *adr);
int		add_address(t_adr **li, void *adr);
int		clear_address(t_adr *li);
void	free_all_node(t_cmds *info);

/*		--Prompt--		*/
char	*get_prompt(void);

char	*get_pwd(void);
char	*add_char_start(char *str, char *add);
char	*add_char_end(char *str, char *add);
char	*replace(char *str, char *src);

/*		--Signal--		*/
int		init_signal(void);
void	signal_handler(int signal);
void	reset_signal(void);

/*		--Token--		*/
int		ft_lstadd_tokback(t_token **li, int type, char *str);
void	ft_lstrm_tokback(t_token **li);
int		clear_token(t_token *li);

// Exec  Utils
int		start_process(t_cmds *data, t_adr *adr, t_adr *perma);
void	cmd_loop(t_cmds *data, t_adr *adr, t_adr *perma);	
int		last_cmd(t_cmds *data, t_adr *adr, t_adr *perma);
int		exec_cmd(char **cmd_tab, char **envp, t_adr **adr);
char	**get_allpaths(char **envp, t_adr **adr);
int		set_stdin(t_cmds *data, char *infile, int type, int istrash);
int		set_stdout(t_cmds *data, char *outfile, int mod, int istrash);
int		redirect_control(t_cmds *data);
t_adr	*get_lastnode(t_adr *node);
int		check_if_builtins(t_cmds *data);
void	child_killer(t_cmds *data, t_adr *adr, t_adr *perma, int status);
int		is_directory(const char *path);

// Exec Builtins
int		builtins_control(t_cmds *data, t_adr *perma, t_adr *adr);
int		exec_builtins(t_cmds *data, t_adr *address, t_adr *perma);
int		builtins_cd(t_cmds *data, t_adr *address);
void	builtins_pwd(t_cmds *data, t_adr *address, t_adr *perma);
void	builtins_env(t_cmds *data, t_adr *address, t_adr *perma);
void	builtins_exit(t_cmds *data, t_adr *adr, t_adr *perma);
void	builtins_export(t_cmds *data, t_adr *perma);
void	builtins_unset(t_cmds *data, t_adr *perma);
int		init_env(t_cmds *data, t_adr *adr, t_adr *perma);
char	**ft_tabdup(char **tab, int new, t_adr *perma);
void	end_builtin(t_cmds *data, t_adr *adr, t_adr *perma);

// Hdoc
int		start_heredoc(t_cmds *data);
int		check_heredoc(t_cmds *data);
int		multi_hdoc_control(char *line, char *h_doc);

// Memory handling
int		append_node(t_adr **list, void *adr);

#endif
