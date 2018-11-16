#!/bin/bash

# This Script's Path
SCRIPT_PATH=$( dirname ${BASH_SOURCE:-$0} )

# ENV PATH
export RBDYN_APPS_DIR=${SCRIPT_PATH}
export RBDYN_APPS_EXE_FILES=$(echo `ls ${SCRIPT_PATH}/bin`)

function _func_complete_rbdynrun()
{
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
    local cur=${COMP_WORDS[COMP_CWORD]}
    if [ "$COMP_CWORD" -eq 1 ]; then
        COMPREPLY=( $(compgen -W "$RBDYN_APPS_EXE_FILES" -- $cur) )
fi
}

function func_rbdyn()
{
    core=$(find ${SCRIPT_PATH}/bin -name $1)
    option=$(echo $@ | sed -e "s/$1//g")
    command=$core$option
    $command
}

alias rbdynrun=func_rbdyn
complete -o default -F _func_complete_rbdynrun rbdynrun
