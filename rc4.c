#include "rc4.h"
#include <string.h>

/**
 * Khởi tạo context RC4 và chạy KSA
 */
void rc4_initialize(RC4_Context *ctx, const uint8_t *key, size_t key_len) {
    ctx->idx1 = 0;
    ctx->idx2 = 0;
    rc4_key_schedule(ctx, key, key_len);
}

/**
 * Key Scheduling Algorithm (KSA)
 * Khởi tạo mảng S với các giá trị 0-255 và xáo trộn dựa trên khóa
 */
void rc4_key_schedule(RC4_Context *ctx, const uint8_t *key, size_t key_len) {
    // Bước 1: Khởi tạo mảng state với các giá trị từ 0 đến 255
    for (int i = 0; i < 256; i++) {
        ctx->state[i] = (uint8_t)i;
    }
    
    // Bước 2: Xáo trộn mảng state dựa trên khóa
    uint8_t j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + ctx->state[i] + key[i % key_len]) % 256;
        
        // Hoán đổi state[i] và state[j]
        uint8_t temp = ctx->state[i];
        ctx->state[i] = ctx->state[j];
        ctx->state[j] = temp;
    }
}

/**
 * Pseudo-Random Generation Algorithm (PRGA)
 * Sinh một byte keystream
 */
uint8_t rc4_generate_byte(RC4_Context *ctx) {
    // Tăng chỉ số i
    ctx->idx1 = (ctx->idx1 + 1) % 256;
    
    // Cập nhật chỉ số j
    ctx->idx2 = (ctx->idx2 + ctx->state[ctx->idx1]) % 256;
    
    // Hoán đổi state[i] và state[j]
    uint8_t temp = ctx->state[ctx->idx1];
    ctx->state[ctx->idx1] = ctx->state[ctx->idx2];
    ctx->state[ctx->idx2] = temp;
    
    // Tính chỉ số keystream
    uint8_t keystream_idx = (ctx->state[ctx->idx1] + ctx->state[ctx->idx2]) % 256;
    
    // Trả về byte keystream
    return ctx->state[keystream_idx];
}

/**
 * Xử lý dữ liệu (mã hóa/giải mã)
 * RC4 sử dụng XOR nên mã hóa và giải mã giống nhau
 */
void rc4_process_data(RC4_Context *ctx, const uint8_t *input, uint8_t *output, size_t length) {
    for (size_t n = 0; n < length; n++) {
        // Sinh byte keystream
        uint8_t keystream_byte = rc4_generate_byte(ctx);
        
        // XOR với dữ liệu đầu vào
        output[n] = input[n] ^ keystream_byte;
    }
}
