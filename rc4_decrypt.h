#ifndef RC4_DECRYPT_H
#define RC4_DECRYPT_H

#include "rc4.h"
#include <stdio.h>
#include <string.h>

/**
 * Giải mã dữ liệu bằng RC4
 * @param ciphertext: Văn bản đã mã hóa
 * @param ct_len: Độ dài ciphertext
 * @param key: Khóa giải mã
 * @param key_len: Độ dài khóa
 * @param plaintext: Buffer lưu văn bản gốc
 */
void decrypt_data(const uint8_t *ciphertext, size_t ct_len,
                  const uint8_t *key, size_t key_len,
                  uint8_t *plaintext) {
    RC4_Context context;
    rc4_initialize(&context, key, key_len);
    rc4_process_data(&context, ciphertext, plaintext, ct_len);
}

/**
 * In plaintext sau khi giải mã
 */
void display_decrypted_text(const uint8_t *data, size_t len) {
    printf("Plaintext: ");
    for (size_t i = 0; i < len; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

/**
 * In plaintext dưới dạng hex
 */
void display_decrypted_hex(const uint8_t *data, size_t len) {
    printf("Plaintext (Hex): ");
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

/**
 * Đọc ciphertext từ file
 */
int load_from_file(const char *filename, uint8_t *buffer, size_t *len) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Không thể mở file để đọc");
        return -1;
    }
    
    // Lấy kích thước file
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(fp);
        fprintf(stderr, "Lỗi khi đọc kích thước file\n");
        return -1;
    }
    
    *len = (size_t)file_size;
    size_t read_bytes = fread(buffer, 1, *len, fp);
    fclose(fp);
    
    if (read_bytes != *len) {
        fprintf(stderr, "Lỗi khi đọc dữ liệu từ file\n");
        return -1;
    }
    
    printf("Đã đọc %zu bytes từ file: %s\n", *len, filename);
    return 0;
}

#endif // RC4_DECRYPT_H
