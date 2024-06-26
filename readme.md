# Web Server
A simple web server create using c++ and can be use for linux daemon

## How to install
This project was build with autotools build system and conan package manager,
before that you need to check all dependencies are available

> I was build this project with debian because debian is my fav linux distro

```sh
$ apt install autoconf automake build-essential cmake libtool pkg-config python3 python3-pip -y
$ pip3 install conan==1.63.0
```

### build
clone this project, compile and install
```sh
$ autoreconf -i
$ mkdir build && cd build
$ ../configure
$ make
$ make check # run testing
$ make install # install file configuration from resource folder
```
or you can build with shell
```sh
$ ./build.sh
```

### build with docker
```sh
# build image
$ docker build -t rizkyalam/web-server:1.0 .

# create and run container
$ docker run -dit --name web-server -p 80:80 rizkyalam/web-server:1.0

# stop container
$ docker container stop web-server

# remove container
$ docker container rm web-server
```

## How To Start Daemon

```sh
# start daemon
$ systemctl start web-server

# check daemon status
$ systemctl status web-server

# stop daemon
$ systemctl stop web-server
```

you can check the logs generated by daemon
```sh
# see all syslog
$ tail -f /var/log/syslog

# see logs daemon
$ tail -f /var/log/syslog | grep web-server
```
