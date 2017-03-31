CC	= g++
CFLAGS	= -O3 -Wall -g
LDFLAGS	= -O3
INCLUDES = -I/opt/local/include
LIBS = -L/opt/local/lib -lfftw3

TARGET	= main 
OBJS	= convolution.o main.o

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	-rm -f $(TARGET) $(OBJS) .nfs* *~ \#* core

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
