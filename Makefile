################################################
# builds crs exercise
# Author: M. Luecke, M. Scherer
################################################
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		src/test.o src/datastructures/CRS.o src/exceptions/DimensionException.o

LIBS =

TARGET =	test

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
