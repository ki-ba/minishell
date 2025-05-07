# minishell

contributors : kbarru, mlouis

### introduction

This project aims to replicate some features from the original bash.
The main supported features are :

+ read commands from stdin.
+ history of last typed commands
+ search and launch the right executable, using path or from a relative / absolute path.
+ handle 'simple quotes' without interpreting meta-characters inside.
+ handle "double quotes" without interpreting meta-characters inside (except $).
+ redirections (<, >, <<, >>)
+ pipes ( | )
+ environment variables starting with $
+ $? expands to the return status of the last executed pipeline.
+ handle CTRL-C, CTRL-D, CTRL-\ like bash


#### builtins

+ `echo` with option `-n`
+ `cd` (absolute or relative path only)
+ `pwd` (no options)
+ `export` (no options)
+ `unset` (no options)
+ `env` (no options or arguments)
+ `exit` (no options)


### behaviour

`minishell` reads pipelines one line at a time. Every pipeline is first tokenized and lexed, then converted into a sequence of instructions (parsing), then executed.

#### lexing

every "word" from each line is interpreted as one of these types : 

+ TOKEN_CMD,
+ TOKEN_OPT,
+ TOKEN_STR,
+ TOKEN_PIPE,
+ TOKEN_REDIRECT,
+ TOKEN_FILE

for instance, the following line : 

`echo -n "hello world" | rev > outfile`

is composed of following tokens : 

`TOKEN_CMD` `TOKEN_OPT` `TOKEN_STR` `TOKEN_PIPE` `TOKEN_CMD` `TOKEN_REDIRECT` `TOKEN_FILE`
