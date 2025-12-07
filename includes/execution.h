#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_piper
{
	int pipe_fd[2];
	int prev_fd;
	int last_pid;
} t_piper;

typedef enum s_builtin_type
{
	NONE,
	EXIT,
	PWD,
	CD,
	ENV,
	EXPORT,
	UNSET,
	ECHOO
}	t_builtin_type;

typedef enum e_heredoc_status
{
    HEREDOC_SUCCESS,
    HEREDOC_FAILED,
    HEREDOC_SIGNAL
} t_heredoc_status;

bool execute_heredoc(t_shell *shell, t_astNode *node);
int execute(t_shell *shell, t_astNode *node);
int execute_cmd(t_shell *shell, t_astNode *node, bool exec_in_child);
int execute_logical(t_shell *shell, t_astNode *node);
int execute_pipe(t_shell *shell, t_astNode *node);
int get_exit_code(int status);

int ft_env(char **args, t_shell *shell);
int ft_cd(char **args, t_shell *shell);
int ft_echo(char **args);

#endif