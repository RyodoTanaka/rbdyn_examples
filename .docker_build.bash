#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

sudo docker build --no-cache -t ryodo/rbdyn_example $DIR
