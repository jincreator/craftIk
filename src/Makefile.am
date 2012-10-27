AM_CPPFLAGS=-I$(top_srcdir)/include
lib_LTLIBRARIES=libctinit.la libctproperties.la libctprocess.la
libctinit_la_SOURCES=init.c
libctproperties_la_SOURCES=properties.c
libctprocess_la_SOURCES=process.c
bin_PROGRAMS=craftik
craftik_SOURCES=craftik.c
craftik_LDADD=libctinit.la libctproperties.la libctprocess.la
