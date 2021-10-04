FROM python:3.6.2-slim
MAINTAINER i05nagai

# ADD sphinxrenderer.py.patch /tmp
RUN apt-get update \
    && apt-get install -y \
        graphviz \
        doxygen \
        patch \
    && pip install \
        sphinx==1.8.1 \
        breathe==4.10.0 \
        sphinx_rtd_theme

