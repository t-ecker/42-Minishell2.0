# 42-Minishell2.0


# Program Flow:

Check argv/argc (maybe envp)
Create Env and stuff
Check shellLVL

LOOP:
- reset structure
- Set signals
- Readline
- If input not empty, add to history
- Check input:
	- Trim everything	
	- empty
	- pipes, quotes, redirs, parentheses placement
	- (maybe if line too long)
- Check if exit
- lexer
- Create env arr for faster env lookup (maybe?)
- Create linked list of all parts of the path (maybe?)
- Build ast that contains raw values (still with quotes, not expanded)

- Execute
	- first all heredocs
		- run expander on delimiter first
	- execute the tree
		- first use expander on all arguments
		- execute redirections (also use expander here for filenames)
		- execute command
- free everything
- do something with error code

	






# GOOD TO KNOW:
Heredoc delimiter can have „“ that need to be removed. E“s“ = Es and E\s = Es
Heredoc with quoted delimiter changes expansion behaviour inside heredoc