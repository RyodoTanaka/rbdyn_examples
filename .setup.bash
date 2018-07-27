#!/bin/bash

# This Script's Path
SCRIPT_PATH=$( dirname ${BASH_SOURCE:-$0} )

# ENV PATH
export EIGEN_APPS_DIR=${SCRIPT_PATH}
export EIGEN_APPS_EXE_FILES=$(echo `ls ${SCRIPT_PATH}/bin`)

function _func_complete_eigenrun()
{
    local cur=${COMP_WORDS[COMP_CWORD]}
    if [ "$COMP_CWORD" -eq 1 ]; then
        COMPREPLY=( $(compgen -W "$EIGEN_APPS_EXE_FILES" -- $cur) )
fi
}

function func_eigen()
{
    core=$(find ${SCRIPT_PATH}/bin -name $1)
    option=$(echo $@ | sed -e "s/$1//g")
    command=$core$option
    $command
}

alias eigenrun=func_eigen
complete -o default -F _func_complete_eigenrun eigenrun
