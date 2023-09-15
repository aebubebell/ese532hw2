# define the C++ compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g -O2 -Wno-unused-label -std=c++11

# define any directories containing header files other than /usr/include
INCLUDES = -I./assignment  # Make sure this path is correct

# define library paths in addition to /usr/lib
LFLAGS =

# define any libraries to link into executable
LIBS =

# define the C++ source files
SRCS = ./Differentiate.cpp ./Filter.cpp ./Scale.cpp ./Compress.cpp ./App.cpp

# define the C++ object files
OBJS = $(SRCS:.cpp=.o)

# define the executable file
MAIN = App
GPROF_MAIN = App1

.PHONY: depend clean profile

all:    $(MAIN)
	@echo  Executable $(MAIN) compiled!

gprof:	$(GPROF_MAIN)
	@echo  Executable $(GPROF_MAIN) compiled!
	@echo  Running ./$(GPROF_MAIN) to get gmon.out for gprof...
	@./$(GPROF_MAIN)
	@echo  Running gprof -p ./$(GPROF_MAIN)...
	@gprof -p ./$(GPROF_MAIN)

perf: all
	@echo Running perf stat...
	@sudo perf stat ./$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

$(GPROF_MAIN): $(OBJS)
	$(CC) -pg $(CFLAGS) $(INCLUDES) -o $(GPROF_MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .cpp's
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) -rf perf* Output.bin *.txt *.out *.o *~ $(MAIN) $(GPROF_MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
