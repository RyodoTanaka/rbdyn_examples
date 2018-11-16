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
RUN git clone --recursive https://github.com/RyodoTanaka/rbdyn_examples.git /home/user/workspace/rbdyn_ws/rbdyn_examples
COPY install.bash /home/user/workspace/rbdyn_ws/rbdyn_examples
RUN cd /home/user/workspace/rbdyn_ws/rbdyn_examples \
 && /bin/bash -c 'source /home/user/workspace/rbdyn_ws/rbdyn_examples/install.bash'
