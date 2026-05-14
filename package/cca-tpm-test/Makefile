CC = arch64-buildroot-linux-gnu-gcc
CFLAGS = -Wall -Wextra -I/usr/include
LDFLAGS = -ltpms

TARGET = tpm_test

all: $(TARGET)

$(TARGET): tpm_test.c
	$(CC) $(CFLAGS) -o $(TARGET) tpm_test.c $(LDFLAGS)

clean:
	rm -f $(TARGET)
