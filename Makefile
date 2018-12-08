CC		= gcc
CFAGS   = -W -Wall
TARGET  = cache_simul
OBJECTS = cache_simul.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFAGS) -o $@ $^
clean:
	rm *.o cache_simul
