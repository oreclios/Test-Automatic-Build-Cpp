# To build use:
# docker build -t orian/cppenv:v1 .
FROM gcc:4.9
MAINTAINER Manuel Velasco

COPY . /usr
WORKDIR /usr
RUN g++ -o myapp Test_project1.cpp
CMD ["./myapp"]