FROM ubuntu:16.04
USER root

RUN apt-get update \
 && apt-get dist-upgrade -y \
 && apt-get install -y \
  sudo \
  apt-utils \
  git \
 && apt-get clean

RUN mkdir -p /home/user/workspace/rbdyn_ws
COPY install.bash /home/user/workspace/rbdyn_ws
RUN /bin/bash -c 'source /home/user/workspace/rbdyn_ws/install.bash'
