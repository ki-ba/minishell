#include "unity.h"
#include "minishell.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_check_quotes(void) {
    /*TEST_ASSERT_EQUAL_INT(0,"Hello world");*/
    TEST_ASSERT_EQUAL_INT(0,check_quotes("""Hello ''''''world"""));
    TEST_ASSERT_EQUAL_INT(0,check_quotes("\"Hello\"' world'"));
    TEST_ASSERT_EQUAL_INT(1,check_quotes("\"\"'Hello'' world"));
    TEST_ASSERT_EQUAL_INT(1,check_quotes("Hello world'"));
    TEST_ASSERT_EQUAL_INT(1,check_quotes("''He''l'l''o' 'w'o'rld"));
    TEST_ASSERT_EQUAL_INT(2,check_quotes("\"Hello world"));
    TEST_ASSERT_EQUAL_INT(2,check_quotes("Hello world\""));
    TEST_ASSERT_EQUAL_INT(2,check_quotes("Hello\" \"wo\"rld"));
}

void test_count_token_len(void) {
   TEST_ASSERT_EQUAL_INT(4, count_token_len("echo test : token is only 'echo'")); 
   TEST_ASSERT_EQUAL_INT(11, count_token_len("'echo test' : token is only 'echo test'"));
   TEST_ASSERT_EQUAL_INT(ft_strlen("\"token is this whole string\""), count_token_len("\"token is this whole string\""));
   TEST_ASSERT_EQUAL_INT(0, count_token_len(" space at the beginning"));
   TEST_ASSERT_EQUAL_INT(ft_strlen("\" 'hi'   still token\""), count_token_len("\" 'hi'   still token\""));

}

// not needed when using generate_test_runner.rb
int main(void) {
		UNITY_BEGIN();
		RUN_TEST(test_check_quotes);
		RUN_TEST(test_count_token_len);
		return UNITY_END();
}
