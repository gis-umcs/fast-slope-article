OPT = 2

CXX = g++
CPPFLAGS = -I/usr/include/gdal/
CXXFLAGS = -std=c++17 -Wall
LDLIBS = -lgdal
OUTPUT_OPTION = -MMD -MP -o $@

EXE = slope

%: %.o
	$(CXX) $(LDFLAGS) -o $(@) $(^) $(LDLIBS)

.PHONY: release debug clean

release: slope
debug: slope

release: CXXFLAGS += -O$(OPT) -s
debug: CXXFLAGS += -g

clean:
	rm -rf $(EXE) *.o *.d

slope: slope.o error.o terrain.o time.o

SOURCE = $(wildcard *.cpp)
OBJS = $(SOURCE:.cpp=.o)
DEPS = $(SOURCE:.cpp=.d)
-include $(DEPS)
