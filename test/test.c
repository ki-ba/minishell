#include "libft.h"
#include "unity.h"
#include "minishell.h"
#include "builtins.h"
#include <stdlib.h>

void	setUp(void)
{
	return ;
}

void	tearDown(void)
{
	return ;
}

void	test_check_quotes(void)
{
	TEST_ASSERT_EQUAL_INT(0, check_quotes("Hello world"));
	TEST_ASSERT_EQUAL_INT(0, check_quotes("""Hello ''''''world"""));
	TEST_ASSERT_EQUAL_INT(0, check_quotes("\"Hello\"' world'"));
	TEST_ASSERT_EQUAL_INT(1, check_quotes("\"\"'Hello'' world"));
	TEST_ASSERT_EQUAL_INT(1, check_quotes("Hello world'"));
	TEST_ASSERT_EQUAL_INT(1, check_quotes("''He''l'l''o' 'w'o'rld"));
	TEST_ASSERT_EQUAL_INT(2, check_quotes("\"Hello world"));
	TEST_ASSERT_EQUAL_INT(2, check_quotes("Hello world\""));
	TEST_ASSERT_EQUAL_INT(2, check_quotes("Hello\" \"wo\"rld"));
}

void	test_count_token_len(void)
{
	TEST_ASSERT_EQUAL_INT(4, count_token_len("echo test : token is only 'echo'")); 
	TEST_ASSERT_EQUAL_INT(11, count_token_len("'echo test' : token is only 'echo test'"));
	TEST_ASSERT_EQUAL_INT(ft_strlen("\"token is this whole string\""), count_token_len("\"token is this whole string\""));
	TEST_ASSERT_EQUAL_INT(0, count_token_len(" space at the beginning"));
	TEST_ASSERT_EQUAL_INT(ft_strlen("\" 'hi'   still token\""), count_token_len("\" 'hi'   still token\""));
	TEST_ASSERT_EQUAL_INT(1, count_token_len("$ <- not a var because of the space"));
}

void test_determine_redirect(void)
{
    TEST_ASSERT_EQUAL(TRUE, determine_redirect(">"));
    TEST_ASSERT_EQUAL(TRUE, determine_redirect("<"));
    TEST_ASSERT_EQUAL(TRUE, determine_redirect(">>"));
    TEST_ASSERT_EQUAL(FALSE, determine_redirect("Hello"));
}

void test_determine_option(void) 
{
    TEST_ASSERT_EQUAL(TRUE, determine_option("-n"));
    TEST_ASSERT_EQUAL(FALSE, determine_option("Hello"));
}

void test_create_token(void) 
{
    t_list *tokens = NULL;
	t_bool	cmd_bool = FALSE;
    t_token *cur_token = token(&tokens, ft_strdup("Hello"), &cmd_bool);
    TEST_ASSERT_NOT_NULL(cur_token);
    TEST_ASSERT_EQUAL(TOKEN_CMD, cur_token->type);
    TEST_ASSERT_EQUAL_STRING("Hello", cur_token->token);
}

void test_tokenize(void) 
{
    t_list *tokens = NULL;
    tokenize(&tokens, "echo 'Hello, World!'");
    TEST_ASSERT_EQUAL(2, ft_lstsize(tokens));
    t_token *token = (t_token *)tokens->content;
    TEST_ASSERT_EQUAL(TOKEN_CMD, token->type);
    TEST_ASSERT_EQUAL_STRING("echo", token->token);
    token = (t_token *)tokens->next->content;
    TEST_ASSERT_EQUAL(TOKEN_STR, token->type);
    TEST_ASSERT_EQUAL_STRING("'Hello, World!'", token->token);
}

void test_create_env(void)
{
	extern char **environ;
	t_env_lst *env_lst;
	create_environment(&env_lst, environ);
	size_t	i = 0;
	while (environ[i])
	{
		TEST_ASSERT_EQUAL_STRING(ft_substr(environ[i], 0, ft_strlen_c(environ[i], '=')),env_lst->name);
		TEST_ASSERT_EQUAL_STRING(ft_substr(environ[i], ft_strlen_c(environ[i], '=') + 1, 9999), env_lst->value);
		env_lst = env_lst->next;
		++i;
	}
}

void test_create_env_arr(void)
{
	extern char **environ;
	char		**env_arr;
	t_env_lst *env_lst;
	size_t	i = 0;

	create_environment(&env_lst, environ);
	env_arr = create_env_arr(env_lst);
	while (environ[i])
	{
		TEST_ASSERT_EQUAL_STRING(environ[i], env_arr[i]);
		++i;
	}
	TEST_ASSERT_INT_WITHIN(10,50,i);
}

void	test_must_expand(void)
{
	TEST_ASSERT_TRUE(must_expand("Hello $USER", 6));
	TEST_ASSERT_TRUE(must_expand("'Hello' $USER", 8));
	TEST_ASSERT_TRUE(must_expand("'Hello' $U'SER'", 8));
	TEST_ASSERT_TRUE(must_expand("'Hello' $USER you ar'e at '$PWD", 27));
	TEST_ASSERT_FALSE(must_expand("'Hello $USER'", 7));
	TEST_ASSERT_FALSE(must_expand("H'''ello $'USER", 9));
	TEST_ASSERT_FALSE(must_expand("'Hello' $USER'", 4));
	TEST_ASSERT_FALSE(must_expand("Hello '$USER'", 7));
}

void	test_expand_line(void)
{
	extern char	**environ;
	char		*line, *line2, *line3, *line4;
	char		*expanded, *expanded2, *expanded3, *expanded4;
	t_env_lst	*env_lst;

	env_lst = NULL;
	create_environment(&env_lst, environ);
	line = ft_strdup("hello $USER you are at $PWD");
	line2 = ft_strdup("hello '$USER' you are at $PWD");
	line3 = ft_strdup("hello \"$USER you\" are 'at $'PWD");
	line4 = ft_strdup("echo $");
	expanded = ft_concat(4, "hello ",getenv("USER"), " you are at", getenv("PWD"));
	expanded2 = ft_concat(3, "hello '$USER' you are at \"", getenv("PWD"), "\"");
	expanded3 = ft_concat(3, "hello \"", getenv("USER"), "\" you are 'at $'PWD");
	expanded4 = ft_strdup("echo $");
	TEST_ASSERT_EQUAL_STRING(expanded, expand_line(env_lst, line));
	TEST_ASSERT_EQUAL_STRING(expanded2, expand_line(env_lst, line2));
	TEST_ASSERT_EQUAL_STRING(expanded3, expand_line(env_lst, line3));
	TEST_ASSERT_EQUAL_STRING(expanded4, expand_line(env_lst, line4));
}
void	test_summarize_lexing(void)
{
	t_list	*tokens;

	tokens = NULL;
	tokenize(&tokens, "echo < infile -n | rev > outfile");
	TEST_ASSERT_EQUAL_STRING("04513045;", summarize_lexing(tokens));
	tokens = NULL;
	tokenize(&tokens, "< infile > outfile > outfile2 rev");
	TEST_ASSERT_EQUAL_STRING("4545450;", summarize_lexing(tokens));
	tokens = NULL;
	tokenize(&tokens, "echo \"hi there\" -n | rev > outfile");
	TEST_ASSERT_EQUAL_STRING("0213045;", summarize_lexing(tokens));
}

void	test_cd(void)
{
	extern char **environ;
	t_env_lst	*env_lst;
	char		*cur_wd;
	char		*old_wd;
	char		*pwd = ft_strdup("PWD");
	char		*oldpwd = ft_strdup("OLDPWD");

	env_lst = NULL;
	create_environment(&env_lst, environ);
	cur_wd = get_env_val(env_lst, "PWD"); 
	ft_cd(ft_split("cd /home", ' '), env_lst);
	TEST_ASSERT_EQUAL_STRING("/home", get_env_val(env_lst, pwd));
	TEST_ASSERT_EQUAL_STRING(cur_wd, get_env_val(env_lst, oldpwd));
	cur_wd = get_env_val(env_lst, pwd);
	old_wd = get_env_val(env_lst, oldpwd);
	ft_cd(ft_split("cd /home/inexistent_folder", ' '), env_lst);
	TEST_ASSERT_EQUAL_STRING(cur_wd, get_env_val(env_lst, pwd));
	TEST_ASSERT_EQUAL_STRING(old_wd, get_env_val(env_lst, oldpwd));
	cur_wd = get_env_val(env_lst, pwd);
	old_wd = get_env_val(env_lst, oldpwd);
	ft_cd(ft_split("cd", ' '), env_lst);
	TEST_ASSERT_EQUAL_STRING(cur_wd, get_env_val(env_lst, pwd));
	TEST_ASSERT_EQUAL_STRING(old_wd, get_env_val(env_lst, oldpwd));
	// cur_wd = get_env_val(env_lst, pwd);
	// old_wd = get_env_val(env_lst, oldpwd);
	// ft_cd(ft_split("cd \0", ' '), env_lst);
	// TEST_ASSERT_EQUAL_STRING(cur_wd, get_env_val(env_lst, pwd));
	// TEST_ASSERT_EQUAL_STRING(old_wd, get_env_val(env_lst, oldpwd));
	cur_wd = get_env_val(env_lst, pwd);
	old_wd = get_env_val(env_lst, oldpwd);
	ft_cd(ft_split("cd / home", ' '), env_lst);
	TEST_ASSERT_EQUAL_STRING(cur_wd, get_env_val(env_lst, pwd));
	TEST_ASSERT_EQUAL_STRING(old_wd, get_env_val(env_lst, oldpwd));
}

void	test_pwd(void)
{
	extern char **environ;
	t_env_lst	*env_lst;

	env_lst = NULL;
	create_environment(&env_lst, environ);
	TEST_ASSERT_TRUE(ft_pwd(ft_split("pwd", ' ')) == 0);
	ft_printf("%s\n", get_env_val(env_lst, "PWD"));
	TEST_ASSERT_TRUE(ft_pwd(ft_split("pwd test", ' ')) != 0);
}

void	test_remove_quotes(void)
{
	t_list	*tokens;
	t_list	*current;
	char	line[] = "\"hello world\" 'h''e''l''l''o w''o''r''l''d' \"h\"\"e\"\"l\"\"l\"\"o\"\" \"\"w\"\"o\"\"r\"\"l\"\"d\"";
	char	line2[] = "\"hello 'world'\" 'hel\"lo world\"' \"'hello '\"world";
	char	*expected[] = {"hello 'world'", "hel\"lo world\"", "'hello 'world"};
	size_t	i;

	tokens = NULL;
	i = 0;
	tokenize(&tokens, line);
	current = tokens;
	ft_lstiter(tokens, remove_quotes);
	while (current)
	{
		TEST_ASSERT_EQUAL_STRING("hello world", ((t_token *)current->content)->token);
		current = current->next;
	}
	ft_lstclear(&tokens, deltoken);
	tokenize(&tokens, line2);
	current = tokens;
	ft_lstiter(tokens, remove_quotes);
	while (current)
	{
		TEST_ASSERT_EQUAL_STRING(expected[i], ((t_token *)current->content)->token);
		++i;
		current = current->next;
	}
	ft_lstclear(&tokens, deltoken);
}

void	test_count_parts(void)
{
	char *line1, *line2, *line3, *line4, *line5, *line6, *line7, *line8;

	line1 = ft_strdup("a classic test without variables or quotes");
	line2 = ft_strdup("a $test with a variable");
	line3 = ft_strdup("a' complex test' with \" $VARS\" and q'uo'tes");
	line4 = ft_strdup("what about '$VARS' with single quotes?");
	line5 = ft_strdup("$var$var2$var3 \"hello $WORLD\"");
	line6 = ft_strdup("hel$var hi there'		$zouzou'$hi");
	line7 = ft_strdup("\"test with \"$TRUNCA\"TED variable\"");
	line7 = ft_strdup("\"test with \"$TRUNCA\"TED variable\"");
	line8 = ft_strdup("only two parts $USER");
	// TEST_ASSERT_EQUAL(1, count_parts(line1));
	// TEST_ASSERT_EQUAL(3, count_parts(line2));
	// TEST_ASSERT_EQUAL(3, count_parts(line3));
	// TEST_ASSERT_EQUAL(1, count_parts(line4));
	// TEST_ASSERT_EQUAL(5, count_parts(line5));
	// TEST_ASSERT_EQUAL(5, count_parts(line6));
	// TEST_ASSERT_EQUAL(3, count_parts(line7));
	// TEST_ASSERT_EQUAL(2, count_parts(line8));
}
// not needed when using generate_test_runner.rb
int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_check_quotes);
	RUN_TEST(test_count_token_len);
	RUN_TEST(test_determine_redirect);
	RUN_TEST(test_determine_option);
	RUN_TEST(test_create_token);
	RUN_TEST(test_tokenize);
	RUN_TEST(test_create_env);
	RUN_TEST(test_create_env_arr);
	RUN_TEST(test_must_expand);
	RUN_TEST(test_summarize_lexing);
	RUN_TEST(test_cd);
	RUN_TEST(test_pwd);
	RUN_TEST(test_remove_quotes);
	// RUN_TEST(test_count_parts);
	return UNITY_END();
}
