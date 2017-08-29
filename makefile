OBJECTS = main.o fsm.o main_fsm.o
SRCS = main.c fsm.c main_fsm.c
 
CC = gcc
CFLAGS = -g -c
 
TARGET =fsm 
 
$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) -g $(OBJECTS)
 
clean : 
	rm -f $(OBJECTS) $(TARGET)
