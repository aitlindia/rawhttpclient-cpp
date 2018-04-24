
# arm-linux-gnueabi-g++

CXX					:=g++
#CXX					:=arm-linux-gnueabi-g++
CC					:=arm-linux-gnueabi-gcc
AR					:=ar
#AR					:=arm-linux-gnueabi-ar
STRIP				:=arm-linux-gnueabi-strip

#CXX					:=arm-none-linux-gnueabi-g++
#CC					:=arm-none-linux-gnueabi-gcc
#AR					:=arm-none-linux-gnueabi-ar
#STRIP				:=arm-none-linux-gnueabi-strip

CONFIGFLAGS             :=-fPIC -Wall -O3 -g
TARGET_LIB = libhttprequest.a

SRCS = HttpRequest.cpp HttpResponse.cpp HttpException.cpp
OBJS = $(SRCS:.cpp=.o)


all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(AR) -rs $@ $^

$(SRCS:.cpp=.d):%.d:%.cpp
	$(CXX) $(CXXFLAGS) -MM $< >$@@

clean:
	rm -f $(OBJS) $(TARGET_LIB) $(SRCS:.cpp=.d)
