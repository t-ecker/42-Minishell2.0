# include "../../includes/minishell.h"

volatile sig_atomic_t g_signal_received;

void sigint_main_handler(int sig)
{
	(void)sig;
	if (g_signal_received != SIGINT)
		ft_putchar_fd('\n', 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void heredoc_signal_handler(int sig)
{
    g_signal_received = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void disable_ctrl_c_echo(void)
{
    struct termios term;
    
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;  // Disable echoing of control characters
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void setup_main_signals(void)
{
	disable_ctrl_c_echo();
	signal(SIGINT, sigint_main_handler);
	signal(SIGQUIT, SIG_IGN);
}

void setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_handler);
}