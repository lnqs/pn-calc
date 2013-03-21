CC = clang
CFLAGS = -std=c99 -Wall -Werror -ggdb -O0
LDFLAGS = -lm

PNC_SOURCES = pncalc.c
PNC_OBJECTS = $(PNC_SOURCES:.c=.o)
PNC_EXECUTABLE = pncalc

RPNC_SOURCES = rpncalc.c
RPNC_OBJECTS = $(RPNC_SOURCES:.c=.o)
RPNC_EXECUTABLE = rpncalc

all: $(PNC_SOURCES) $(RPNC_SOURCES) $(PNC_EXECUTABLE) $(RPNC_EXECUTABLE)

$(PNC_EXECUTABLE): $(PNC_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(PNC_OBJECTS)

$(RPNC_EXECUTABLE): $(RPNC_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(RPNC_OBJECTS)

%.o: %.c %.d
	$(CC) -c $(CFLAGS) $< -o $@

%.d: %.c
	@$(SHELL) -ec '$(CC) -M $(CFLAGS) $< \
		| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
		[ -s $@ ] || rm -f $@'

clean:
	rm -rf *.o *.d $(PNC_EXECUTABLE) $(RPNC_EXECUTABLE)

-include $(SOURCES:.c=.d)
