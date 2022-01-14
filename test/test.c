/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:50:45 by gkgpteam          #+#    #+#             */
/*   Updated: 2022/01/14 13:42:46 by gphilipp         ###   ########.fr       */
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

	//test qui va fail:
	mu_assert_string_eq("A", "B");
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(allowed_function);

	MU_RUN_TEST(test_parse_arg);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
