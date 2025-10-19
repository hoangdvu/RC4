#ifndef RC4_ENCRYPT_H
#define RC4_ENCRYPT_H

#include "rc4.h"
#include <stdio.h>
#include <string.h>

/**
 * Mã hóa dữ liệu bằng RC4
 * @param plaintext: Văn bản gốc
 * @param pt_len: Độ dài plaintext
 * @param key: Khóa mã hóa
 * @param key_len: Độ dài khóa
 * @param ciphertext: Buffer lưu văn bản mã hóa
 */
void encrypt_data(const uint8_t *plaintext, size_t pt_len,
                  const uint8_t *key, size_t key_len,
                  uint8_t *ciphertext) {
    RC4_Context context;
    rc4_initialize(&context, key, key_len);
    rc4_process_data(&context, plaintext, ciphertext, pt_len);
}

/**
 * In ciphertext dưới dạng hex
 */
void display_hex_output(const uint8_t *data, size_t len) {
    printf("Ciphertext (Hex): ");
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

/**
 * In ciphertext dưới dạng ký tự
 */
void display_char_output(const uint8_t *data, size_t len) {
    printf("Ciphertext (Chars): ");
    for (size_t i = 0; i < len; i++) {
        if (data[i] >= 32 && data[i] <= 126) {
            printf("%c", data[i]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

/**
 * Lưu ciphertext vào file
 */
int save_to_file(const char *filename, const uint8_t *data, size_t len) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Không thể mở file để ghi");
        return -1;
    }
    
    size_t written = fwrite(data, 1, len, fp);
    fclose(fp);
    
    if (written != len) {
        fprintf(stderr, "Lỗi khi ghi file\n");
        return -1;
    }
    
    printf("Đã lưu ciphertext vào file: %s\n", filename);
    return 0;
}

#endif // RC4_ENCRYPT_H
