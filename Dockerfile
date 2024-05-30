FROM debian:stable-slim

WORKDIR /web-server

COPY . .

EXPOSE 80

RUN apt update -y && apt upgrade -y
RUN apt install autoconf automake build-essential cmake libtool pkg-config python3 python3-pip -y
RUN pip3 install conan==1.63.0 --break-system-packages

RUN /web-server/build.sh

CMD ["web_server", "--run"]
