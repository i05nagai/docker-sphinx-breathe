FROM python:3.6.2rc1-alpine3.6
MAINTAINER i05nagai

ADD sphinxrenderer.py.patch /tmp
RUN apk update \
    && apk add --no-cache \
        graphviz=2.38.0-r6 \
        doxygen=1.8.13-r0 \
    && pip install \
        sphinx==1.6.3 \
        breathe==4.6.0 \
        sphinx_rtd_theme \
    && cd /usr/local/lib/python3.6/site-packages/breathe/renderer \
    && patch < /tmp/sphinxrenderer.py.patch

