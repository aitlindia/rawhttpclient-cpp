RPI_LIB = httprequest

CXX					:=g++
#CXX					:=arm-linux-gnueabi-g++
CC					:=arm-linux-gnueabi-gcc
AR					:=arm-linux-gnueabi-ar
STRIP				:=arm-linux-gnueabi-strip

#CXX					:=arm-none-linux-gnueabi-g++
#CC					:=arm-none-linux-gnueabi-gcc
#AR					:=arm-none-linux-gnueabi-ar
#STRIP				:=arm-none-linux-gnueabi-strip

CXXFLAGS = -Wall -O3 -g -I..
LDFLAGS = -L..
LIBS = -l$(RPI_LIB)
TARGET = httpdemo

SRCS = Demo.cpp
OBJS = $(SRCS:.cpp=.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
