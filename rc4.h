#ifndef RC4_H
#define RC4_H

#include <stdint.h>
#include <stddef.h>

// Định nghĩa cấu trúc lưu trạng thái RC4
typedef struct {
    uint8_t state[256];  // Mảng trạng thái S
    uint8_t idx1;        // Chỉ số i
    uint8_t idx2;        // Chỉ số j
} RC4_Context;

/**
 * Khởi tạo trạng thái RC4 với khóa
 * @param ctx: Con trỏ tới context RC4
 * @param key: Mảng byte chứa khóa
 * @param key_len: Độ dài khóa
 */
void rc4_initialize(RC4_Context *ctx, const uint8_t *key, size_t key_len);

/**
 * Key Scheduling Algorithm (KSA) - Thuật toán lập lịch khóa
 * Khởi tạo và xáo trộn mảng trạng thái dựa trên khóa
 */
void rc4_key_schedule(RC4_Context *ctx, const uint8_t *key, size_t key_len);

/**
 * Pseudo-Random Generation Algorithm (PRGA) - Sinh keystream
 * Sinh một byte keystream từ trạng thái hiện tại
 */
uint8_t rc4_generate_byte(RC4_Context *ctx);

/**
 * Xử lý dữ liệu (mã hóa hoặc giải mã)
 * @param ctx: Con trỏ tới context RC4
 * @param input: Dữ liệu đầu vào
 * @param output: Dữ liệu đầu ra
 * @param length: Độ dài dữ liệu
 */
void rc4_process_data(RC4_Context *ctx, const uint8_t *input, uint8_t *output, size_t length);

#endif // RC4_H
