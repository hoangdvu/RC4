#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rc4.h"
#include "rc4_encrypt.h"

#define MAX_BUFFER 1024

int main() {
    // Plaintext cần mã hóa
    const char *plaintext_str = "Hanoi University of Science and Technology";
    
    // Khóa mã hóa
    const char *key_str = "MySecretKey";
    
    // Chuyển đổi sang uint8_t
    const uint8_t *plaintext = (const uint8_t *)plaintext_str;
    const uint8_t *key = (const uint8_t *)key_str;
    
    size_t pt_len = strlen(plaintext_str);
    size_t key_len = strlen(key_str);
    
    // Buffer cho ciphertext
    uint8_t ciphertext[MAX_BUFFER];
    
    printf("=== RC4 ENCRYPTION ===\n");
    printf("Plaintext: %s\n", plaintext_str);
    printf("Key: %s\n", key_str);
    printf("Plaintext length: %zu bytes\n", pt_len);
    printf("Key length: %zu bytes\n\n", key_len);
    
    // Mã hóa
    encrypt_data(plaintext, pt_len, key, key_len, ciphertext);
    
    // Hiển thị kết quả
    display_hex_output(ciphertext, pt_len);
    display_char_output(ciphertext, pt_len);
    
    // Lưu vào file
    save_to_file("ciphertext.bin", ciphertext, pt_len);
    
    printf("\nĐã hoàn thành quá trình mã hóa!\n");
    printf("Chạy ./decrypt để giải mã file ciphertext.bin\n");
    
    return 0;
}
