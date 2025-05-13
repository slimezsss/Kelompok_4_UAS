CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = menusigap
SRCS = menusigap.c produk.c pesanan.c riwayat.c sortproduk.c login.c
HDRS = sigap.h
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET).exe 2>nul || exit 0

