#!/bin/sh

HEAD="./includes/"
LIBS="-Lvendor/liblist/ -llist"

make
if [[ $? == 0 ]]; then
	SRCS=$(find ./srcs -iname "*.c" ! -name "main.c")

	echo "#A 1)\n#A 2) PAIR\n#A 3) \n#A 4) PAIR x4\n#A 5) \n#A 6) PAIR\n#A 7) \n#A 8) PAIR x4" \
		"\n#B 1) \n#B 2) \n#B 3) \n#B 4) x4\n#B 5) \n#B 6) \n#B 7) \n#B 8) x4" > .tmp_in

	echo "====== MINISHELL DIFFS ======"
	#./test/diff.sh "grep #A" "grep PAIR"
	#./test/diff.sh "ls -l" "wc -l"
	#./test/diff.sh "grep #A" "wc -w"

	echo "====== MINISHELL TESTS ======"
	export ABC=abc
	gcc -g -o test.out ./test/test.c $SRCS $LIBS -fno-builtin -I "$HEAD" && ./test.out && rm ./test.out

	echo "========= NORMINETTE ========"
	norminette ./srcs/*.c ./srcs/**/*.c ./includes/*.h | grep -v ": OK!"
	echo "============================="
fi
