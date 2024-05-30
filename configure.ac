AC_INIT([web-server], [1.0], [rizky.alams09@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_SRCDIR([src/main.cpp])

# Checks for programs
AC_PROG_INSTALL

# enable dependency tracking
AM_MAINTAINER_MODE

# check for conan-generated pkg-config files
PKG_PROG_PKG_CONFIG

PKG_CHECK_MODULES([GTEST], [gtest gmock])
PKG_CHECK_MODULES([SPDLOG], [spdlog >= 1.9.0])
PKG_CHECK_MODULES([LIBCONFIG], [libconfig++ >= 1.7.3])
PKG_CHECK_MODULES([YAMLCPP], [yaml-cpp >= 0.8.0])
PKG_CHECK_MODULES([BOOST], [boost_filesystem boost_system])

AC_PROG_CXX

AC_OUTPUT
