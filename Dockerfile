# To build use:
# docker build -t orian/cppenv:v1 .
FROM gcc:4.9
MAINTAINER Manuel Velasco

COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -o myapp main.c
CMD ["./myapp"]