# Makefile cho dự án RC4

# Compiler và flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.
TARGET_ENCRYPT = encrypt
TARGET_DECRYPT = decrypt

# Source files
SRC_ENCRYPT = main_encrypt.c rc4.c
SRC_DECRYPT = main_decrypt.c rc4.c

# Object files
OBJ_ENCRYPT = $(SRC_ENCRYPT:.c=.o)
OBJ_DECRYPT = $(SRC_DECRYPT:.c=.o)

# Default target
.PHONY: all
all: $(TARGET_ENCRYPT) $(TARGET_DECRYPT)

# Build encrypt program
$(TARGET_ENCRYPT): $(OBJ_ENCRYPT)
	@echo "Đang liên kết chương trình mã hóa..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Đã tạo: $@"

# Build decrypt program
$(TARGET_DECRYPT): $(OBJ_DECRYPT)
	@echo "Đang liên kết chương trình giải mã..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Đã tạo: $@"

# Compile object files
%.o: %.c
	@echo "Đang biên dịch: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Test target
.PHONY: test
test: all
	@echo ""
	@echo "=== Chạy test mã hóa ==="
	./$(TARGET_ENCRYPT)
	@echo ""
	@echo "=== Chạy test giải mã ==="
	./$(TARGET_DECRYPT)
	@echo ""
	@echo "Test hoàn tất!"

# Clean target
.PHONY: clean
clean:
	@echo "Đang xóa các file build..."
	rm -f $(TARGET_ENCRYPT) $(TARGET_DECRYPT)
	rm -f $(OBJ_ENCRYPT) $(OBJ_DECRYPT)
	rm -f ciphertext.bin
	@echo "Đã xóa sạch!"

# Help target
.PHONY: help
help:
	@echo "Các lệnh có sẵn:"
	@echo "  make all     - Biên dịch cả hai chương trình"
	@echo "  make test    - Chạy test tự động"
	@echo "  make clean   - Xóa các file build"
	@echo "  make help    - Hiển thị trợ giúp này"
