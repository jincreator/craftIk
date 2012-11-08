AM_CPPFLAGS=-I$(top_srcdir)/include
lib_LTLIBRARIES=libctinit.la libctsetting.la libctprocess.la
libctinit_la_SOURCES=init.c
libctsetting_la_SOURCES=setting.c
libctprocess_la_SOURCES=process.c
bin_PROGRAMS=craftik
craftik_SOURCES=craftik.c
craftik_LDADD=libctinit.la libctsetting.la libctprocess.la
