################################################
# builds crs exercise
# Author: M. Luecke, M. Scherer
################################################
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		src/testCRS.o \
	src/datastructures/CRS.o \
	src/datastructures/VectorFunc.o \
	src/exceptions/DimensionException.o \
	src/algorithms/JacobiMethod.o

LIBS =

TARGET =	testCRS

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

doc:
	doxygen -s doc.Doxyfile