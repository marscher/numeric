################################################
# builds crs exercise
# Author: M. Luecke, M. Scherer
# $Revision: $
# $Id: $
################################################
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		src/tests/testJacobi.o \
	src/datastructures/CRS.o \
	src/datastructures/VectorFunc.o \
	src/exceptions/DimensionException.o \
	src/algorithms/JacobiMethod.o \
	src/algorithms/GS.o \
	src/algorithms/Solver.o \
	src/algorithms/CG.o

LIBS =

TARGET =	testJacobi

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET) doc

clean:
	rm -rf $(OBJS) $(TARGET) doc/

doc:
	doxygen -s doc.Doxyfile
