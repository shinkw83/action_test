FROM ghcr.io/shinkw83/sioc_devel:1.0
MAINTAINER shinkw83@gmail.com

ADD include/ /root/project/include
ADD src/ /root/project/src
ADD CMakeLists.txt /root/project
ADD install.sh /root/project

WORKDIR /root/project
RUN ./install.sh
