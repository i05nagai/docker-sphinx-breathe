[![Build Status](https://travis-ci.org/i05nagai/docker-sphinx-breathe.svg?branch=master)](https://travis-ci.org/i05nagai/docker-sphinx-breathe)

## Overview

* base image
    * `python:3.6.2rc1-alpine3.6`
* python
    * 3.6
* sphinx
    * 1.6.3
* breathe
    * 4.6.0

## Usage

```
cp Doxyfile project/
```

```
bash docker_run_gen_docs.sh
```

```
bash docker_run_sphinx_build.sh
```

## To push docker image
Automated build is ready to use so that you just need to push the commit with a git tag as the tag of docker image.

```
git tag -a 1.6.3
git push origin 1.6.3
```
