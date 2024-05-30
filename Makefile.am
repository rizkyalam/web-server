AUTOMAKE_OPTIONS = subdir-objects

# Programs to build
bin_PROGRAMS = web_server
web_server_SOURCES = src/main.cpp \
    src/config/log.cpp \
    src/config/daemon.cpp \
    src/config/cmd_line_parser.cpp \
    src/config/setting.cpp \
    src/config/thread_pool.cpp \
    src/config/server.cpp \
    src/include/server.hpp \
    src/include/log.hpp \
    src/include/daemon.hpp \
    src/include/cmd_line_parser.hpp \
    src/include/setting.hpp
web_server_CPPFLAGS = -I$(top_srcdir)/src/include \
    $(SPDLOG_CFLAGS) \
    $(LIBCONFIG_CFLAGS) \
    $(YAMLCPP_CFLAGS) \
    $(BOOST_CFLAGS)
web_server_LDADD = $(SPDLOG_LIBS) \
    $(LIBCONFIG_LIBS) \
    $(YAMLCPP_LIBS) \
    $(BOOST_LIBS)

# install configuration
sysconfdir = /etc/web-server
dist_sysconf_DATA = resource/web-server.conf
settingdir = /etc/web-server
dist_setting_DATA = resource/setting.yaml
systemunitdir = /etc/systemd/system
dist_systemunit_DATA = resource/web-server.service
webdir = /var/www/html
dist_web_DATA = web/index.html \
    web/style.css \
    web/script.js

# Test programs
TESTS = log_test setting_test
check_PROGRAMS = $(TESTS)

log_test_SOURCES = test/log_test.cpp \
    src/config/log.cpp \
    src/include/log.hpp
log_test_CPPFLAGS = -I$(top_srcdir)/src/include \
    $(GTEST_CFLAGS) \
    $(SPDLOG_CFLAGS)
log_test_LDADD = $(GTEST_LIBS) \ 
    $(SPDLOG_LIBS)

setting_test_SOURCES = test/setting_test.cpp \
    src/config/setting.cpp \
    src/include/setting.hpp
setting_test_CPPFLAGS = -I$(top_srcdir)/src/include \
    $(GTEST_CFLAGS) \
    $(YAMLCPP_CFLAGS)
setting_test_LDADD = $(GTEST_LIBS) \ 
    $(YAMLCPP_LIBS)
