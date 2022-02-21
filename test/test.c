/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:50:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/15 17:52:17 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "minunit.h"
#include "minishell.h"

extern char		**environ;

char	OUTPUT[2048] = {0};

void	ft_putstr(char *s)
{
	strlcat(OUTPUT, s, 2048);
}

MU_TEST(allowed_function) {
	mu_check(system("sh ./test/allowed_function.sh") == 0);
}

MU_TEST(test_parse_arg) {
	*OUTPUT = '\0';
	const char	*argvErr[3] = {"1", "2", "3"};
	mu_assert_int_eq(1, minishell(3, argvErr, environ));
	mu_assert_string_eq("\033[0;33mUsage: ./minishell [cmd]\033[0m\n", OUTPUT); *OUTPUT = '\0';
}

void	init_app_for_test(t_app *app)
{
	init_app(app);
	init_env(app, environ);
}

MU_TEST(test_workdir) {
	t_app		app;
	char 		*save_path[4];

	init_app_for_test(&app);
	save_path[0] = ft_getcwd();
	ft_cd(&app, "/");
	save_path[1] = ft_getcwd();
	ft_cd(&app, "/dev");
	save_path[2] = ft_getcwd();
	ft_cd(&app, save_path[0]);
	save_path[3] = ft_getcwd();
	mu_assert_string_eq("/", save_path[1]);
	mu_assert_string_eq("/dev", save_path[2]);
	mu_assert_string_eq(save_path[0], save_path[3]);
	*OUTPUT = '\0';
	ft_pwd();
	mu_assert_string_eq(save_path[0], OUTPUT); *OUTPUT = '\0';
}

MU_TEST(test_env) {
	t_app		app;
	char		str[] = "ABC=abc";

	init_app_for_test(&app);

	mu_assert_string_eq("abc", ft_getenv(&app, "ABC"));
	mu_assert_int_eq(0, ft_setenv(&app, "ABC", "def"));
	mu_assert_string_eq("def", ft_getenv(&app, "ABC"));
	mu_assert_string_eq(NULL, ft_getenv(&app, "__A_B___C"));
	mu_assert_string_eq(NULL, ft_getenv(&app, "__A_B___C"));
	mu_assert_int_eq(1, ft_setenv(&app, "__A_B___C", "abcdef"));
	mu_assert_string_eq("abcdef", ft_getenv(&app, "__A_B___C"));

	*OUTPUT = '\0';
	mu_assert_string_eq("def", ft_getenv(&app, "ABC"));
	mu_assert_int_eq(0, ft_export(&app, str));
	mu_assert_string_eq("", OUTPUT); *OUTPUT = '\0';
	mu_assert_string_eq("abc", ft_getenv(&app, "ABC"));
	mu_assert_int_eq(0, ft_export(&app, "ABC=def"));
	mu_assert_string_eq("def", ft_getenv(&app, "ABC"));
	mu_assert_int_eq(0, ft_export(&app, str));
	mu_assert_string_eq("", OUTPUT); *OUTPUT = '\0';
	mu_assert_string_eq("abc", ft_getenv(&app, "ABC"));
	mu_assert_int_eq(1, ft_unsetenv(&app, "ABC"));
	mu_assert_string_eq(NULL, ft_getenv(&app, "ABC"));
	mu_assert_int_eq(1, ft_export(&app, "ABC"));
	mu_assert_string_eq("bad key=value for ABC\n", OUTPUT); *OUTPUT = '\0';
	mu_assert_string_eq(NULL, ft_getenv(&app, "ABC"));
	mu_assert_int_eq(1, ft_export(&app, "ABC="));
	mu_assert_string_eq("bad key=value for ABC=\n", OUTPUT); *OUTPUT = '\0';
	mu_assert_string_eq(NULL, ft_getenv(&app, "ABC"));
	mu_assert_int_eq(1, ft_export(&app, "="));
	mu_assert_string_eq("bad key=value for =\n", OUTPUT); *OUTPUT = '\0';
	mu_assert_string_eq(NULL, ft_getenv(&app, "ABC"));
	mu_assert_int_eq(0, ft_export(&app, str));
	mu_assert_string_eq("", OUTPUT); *OUTPUT = '\0';
	mu_assert_string_eq("abc", ft_getenv(&app, "ABC"));
	mu_assert_int_eq(1, ft_unsetenv(&app, "ABC"));
	mu_assert_int_eq(0, ft_unsetenv(&app, "ABC"));
	mu_assert_string_eq(NULL, ft_getenv(&app, "ABC"));

	mu_assert_string_eq(NULL, ft_getenv(&app, "__A_B___C2"));
	mu_assert_string_eq(NULL, ft_getenv(&app, "__A_B___C2"));
	mu_assert_int_eq(0, ft_export(&app, "__A_B___C2=abcdef"));
	mu_assert_string_eq("abcdef", ft_getenv(&app, "__A_B___C2"));
	mu_assert_int_eq(0, ft_unset(&app, "__A_B___C2"));
	mu_assert_string_eq(NULL, ft_getenv(&app, "__A_B___C2"));
	mu_assert_int_eq(1, ft_unset(&app, "__A_B___C2"));
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(allowed_function);

	MU_RUN_TEST(test_parse_arg);
	MU_RUN_TEST(test_workdir);
	MU_RUN_TEST(test_env);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
