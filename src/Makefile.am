AUTOMAKE_OPTIONS = foreign
LIBVER = 0:8:0

lib_LTLIBRARIES = libp.la
libp_la_SOURCES = \
    bitmem.cc \
    bitobs.cc \
    contract.cc \
    file.cc \
    format.cc \
    log.cc \
    terminal.cc \
    typeinfo.cc \
    version.cc
libp_la_LDFLAGS = -version-info $(LIBVER) -no-undefined
libp_la_LIBADD = -lfmt

AM_CXXFLAGS = -std=gnu++2a -O2 -I$(srcdir)/../include
