#!/bin/bash

set -x

script_dir=$(cd $(dirname ${0});pwd)
path_to_repository=${script_dir}/../project
repository_name=$(basename ${path_to_repository})
path_to_repository_in_docker=/tmp/${REPOSITORY_NAME}

docker run -it --rm \
  --volume ${path_to_repository}:${path_to_repository_in_docker} \
  sphinx-breathe:alpine-1.6.3 \
  sphinx-build ${path_to_repository_in_docker}/docs/source ${path_to_repository_in_docker}/docs/build
