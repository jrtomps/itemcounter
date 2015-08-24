INSTDIR=/usr/opt/nscldaq/11.0-007

include $(INSTDIR)/filterkit/FilterIncludes




#
#  Add your own compilation/link flags here:

USERCXXFLAGS= -std=c++11
USERCCFLAGS=$(USERCCFLAGS)
USERLDFLAGS=

#
#  Add the names of objects you need here if you modified the name of the driver file, 
#  this should also reflect thtat.
#
OBJECTS = FragmentIndex.o CFragCounterFilter.o CCounterFilter.o SkeletonMain.o

#
#  Modify the line below to provide the name of the library you are trying to build
#  it must be of the form libsomethingorother.so
#

USERFILTER = UserFilter

$(USERFILTER): $(OBJECTS)
	   $(CXX) $(OBJECTS) -o $@ $(USERLDFLAGS) $(LDFLAGS)






