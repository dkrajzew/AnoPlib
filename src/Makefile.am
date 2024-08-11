noinst_LIBRARIES = libanop.a
bin_PROGRAMS = anopTest

libanop_a_SOURCES = AnoP.h AnoPhelpers.cpp AnoPhelpers.h \
AnoPemergency1.h AnoPflashlight1.h AnoPstarfield1.h AnoPtentacle1.h \
AnoPwavelogo1.h AnoPwavepropagation1.h

anopTest_SOURCES = AnoPtest.cpp
anopTest_INCLUDES = -IGL
anopTest_LDADD = libanop.a -lglut

