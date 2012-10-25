AM_CPPFLAGS=-I$(top_srcdir)/include
lib_LTLIBRARIES=libctproperties.la libctprocess.la
libctproperties_la_SOURCES=properties.c
libctprocess_la_SOURCES=process.c
bin_PROGRAMS=craftik
craftik_SOURCES=craftik.c
craftik_LDADD=libctproperties.la libctprocess.la
