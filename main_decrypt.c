#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rc4.h"
#include "rc4_decrypt.h"

#define MAX_BUFFER 1024

int main() {
    // Khóa giải mã (phải giống với khóa mã hóa)
    const char *key_str = "MySecretKey";
    const uint8_t *key = (const uint8_t *)key_str;
    size_t key_len = strlen(key_str);
    
    // Buffer cho dữ liệu
    uint8_t ciphertext[MAX_BUFFER];
    uint8_t plaintext[MAX_BUFFER];
    size_t data_len = 0;
    
    printf("=== RC4 DECRYPTION ===\n");
    printf("Key: %s\n", key_str);
    printf("Key length: %zu bytes\n\n", key_len);
    
    // Đọc ciphertext từ file
    if (load_from_file("ciphertext.bin", ciphertext, &data_len) != 0) {
        fprintf(stderr, "Lỗi: Không thể đọc file ciphertext.bin\n");
        fprintf(stderr, "Vui lòng chạy ./encrypt trước để tạo file này\n");
        return 1;
    }
    
    printf("Ciphertext length: %zu bytes\n", data_len);
    
    // Hiển thị ciphertext dưới dạng hex
    printf("Ciphertext (Hex): ");
    for (size_t i = 0; i < data_len; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n\n");
    
    // Giải mã
    decrypt_data(ciphertext, data_len, key, key_len, plaintext);
    
    // Null-terminate plaintext để in ra
    plaintext[data_len] = '\0';
    
    // Hiển thị kết quả
    display_decrypted_text(plaintext, data_len);
    display_decrypted_hex(plaintext, data_len);
    
    printf("\nĐã hoàn thành quá trình giải mã!\n");
    
    return 0;
}
