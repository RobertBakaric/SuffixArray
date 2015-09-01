AUTOMAKE_OPTIONS = gnu

SUBDIRS = aux/sais-lite-2.4.1/ \
          src/apps/
          
EXTRA_DIST = bin src/include doc/SuffixArray.pdf demo aux
 
LDFLAGS_BOOST = \
    $(BOOST_SYSTEM_LDFLAGS) \
    $(BOOST_PROGRAM_OPTIONS_LDFLAGS)

LIBS_BOOST = \
    $(BOOST_SYSTEM_LIBS) \
    $(BOOST_PROGRAM_OPTIONS_LIBS) \
    $(BOOST_FILESYSTEM_LIBS)

AM_CPPFLAGS = -I$(top_srcdir)/src/include $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(LDFLAGS_BOOST)
LIBS += $(LIBS_BOOST)

