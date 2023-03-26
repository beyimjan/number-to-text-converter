CC = gcc
CFLAGS = -g -Wall -Wextra -Wno-discarded-qualifiers

TARGET = number-to-text-converter

PO_FILES := $(wildcard locale/*/LC_MESSAGES/*.po)
MO_FILES := $(PO_FILES:.po=.mo)

all: $(TARGET) $(MO_FILES)

$(TARGET): src/main.c
	$(CC) $(CFLAGS) $^ -o $@

locale/%/LC_MESSAGES/$(TARGET).mo: locale/%/LC_MESSAGES/$(TARGET).po
	msgfmt $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
	rm -f locale/*/LC_MESSAGES/$(TARGET).mo
