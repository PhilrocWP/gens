# mp3_dec: MP3 decoder.

AUTOMAKE_OPTIONS = foreign subdir-objects

noinst_LTLIBRARIES = libmp3_dec.la

libmp3_dec_la_CFLAGS		= $(AM_CFLAGS) -O3 -funroll-loops
libmp3_dec_la_LDFLAGS		= $(AM_LDFLAGS)
libmp3_dec_la_LIBTOOLFLAGS	= $(AM_LIBTOOLFLAGS) --tag=disable-shared

libmp3_dec_la_SOURCES = \
		common.c \
		dct64_i386.c \
		decode_i386.c \
		interface.c \
		layer3.c \
		tabinit.c

noinst_HEADERS = \
		huffman.h \
		mpg123.h \
		mpglib.h
