#!/bin/bash

script_dir=$(cd $(dirname ${0});pwd)
path_to_repository=${script_dir}/../project
repository_name=$(cd $(dirname ${0});cd ..;pwd)
path_to_repository_in_docker=/tmp/${repository_name}

docker run -it --rm \
  --volume ${path_to_repository}:${path_to_repository_in_docker} \
  sphinx-breathe:ubuntu-1.6.3 \
  doxygen -g ${path_to_repository_in_docker}/Doxyfile
