#!/bin/bash

function _in {
	local e match="$1"
	shift
	for e; do [[ "$e" == "$match" ]] && return 0; done
	return 1
}

ARG1="$1"
ARG2="$2"
./minishell .tmp_in "$ARG1" "$ARG2" .tmp_out_minishell
< .tmp_in $ARG1 | $ARG2 > .tmp_out_sh
DIFF=$(diff -u .tmp_out_sh .tmp_out_minishell)
if $(_in "--print" $@); then
	cat .tmp_out_minishell
fi
if [[ $DIFF ]]; then
	echo "\033[0;31m===== ERROR DIFF! =====\033[0m"
	echo "$DIFF"
	echo "\033[0;31m=======================\033[0m"
fi
if $(_in "--rm" $@); then
	rm .tmp_out_minishell
	rm .tmp_out_sh
fi
