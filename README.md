# Thuật toán mã hóa RC4 (Rivest Cipher 4)

Dự án này implement thuật toán mã hóa dòng RC4 để mã hóa và giải mã chuỗi ký tự. RC4 là một stream cipher được phát triển bởi Ron Rivest vào năm 1987.

## 📁 Cấu trúc dự án
```
rc4-project/
├── rc4.h              # Header chính - định nghĩa RC4_Context và hàm API
├── rc4.c              # Implementation của thuật toán RC4 (KSA, PRGA)
├── rc4_encrypt.h      # Module mã hóa - các hàm encrypt và hiển thị
├── rc4_decrypt.h      # Module giải mã - các hàm decrypt và đọc file
├── main_encrypt.c     # Chương trình chính cho mã hóa
├── main_decrypt.c     # Chương trình chính cho giải mã
├── Makefile           # Build script tự động
└── README.md          # Tài liệu này
```

## 🔧 Yêu cầu hệ thống

- GCC compiler (hoặc compiler C khác hỗ trợ C99)
- Make (tùy chọn, để build tự động)
- Hệ điều hành: Linux/Unix/MacOS hoặc Windows với MinGW/Cygwin

## 🚀 Hướng dẫn build

### Cách 1: Sử dụng Makefile (Khuyến nghị)
```bash
# Biên dịch cả hai chương trình
make all

# Chạy test tự động (mã hóa và giải mã)
make test

# Xóa các file đã build
make clean

# Xem trợ giúp
make help
```

### Cách 2: Biên dịch thủ công

**Biên dịch chương trình mã hóa:**
```bash
gcc -Wall -Wextra -std=c99 -I. main_encrypt.c rc4.c -o encrypt
```

**Biên dịch chương trình giải mã:**
```bash
gcc -Wall -Wextra -std=c99 -I. main_decrypt.c rc4.c -o decrypt
```

## 📖 Cách sử dụng

### Bước 1: Mã hóa văn bản
```bash
./encrypt
```

**Output:**
- In ra ciphertext dưới dạng hex
- In ra ciphertext dưới dạng ký tự
- Lưu ciphertext vào file `ciphertext.bin`

### Bước 2: Giải mã văn bản
```bash
./decrypt
```

**Output:**
- Đọc ciphertext từ file `ciphertext.bin`
- In ra plaintext đã giải mã
- In ra plaintext dưới dạng hex

## 🧪 Test Cases

### Test 1: Default Test
- **Plaintext:** `"Hanoi University of Science and Technology"`
- **Key:** `"MySecretKey"`
- **Expected:** Ciphertext sẽ hiển thị khi chạy, plaintext sau giải mã phải khớp với ban đầu

### Test 2: Standard Test Vectors

#### Test 2.1
- **Key:** `"Key"` (0x4B 0x65 0x79)
- **Plaintext:** `"Plaintext"` (0x50 0x6C 0x61 0x69 0x6E 0x74 0x65 0x78 0x74)
- **Expected Ciphertext:** `BB F3 16 E8 D9 40 AF 0A D3`

#### Test 2.2
- **Key:** `"Wiki"` (0x57 0x69 0x6B 0x69)
- **Plaintext:** `"pedia"` (0x70 0x65 0x64 0x69 0x61)
- **Expected Ciphertext:** `10 21 BF 04 20`

#### Test 2.3
- **Key:** `"Secret"` (0x53 0x65 0x63 0x72 0x65 0x74)
- **Plaintext:** `"Attack at dawn"` (0x41 0x74 0x74 0x61 0x63 0x6B 0x20 0x61 0x74 0x20 0x64 0x61 0x77 0x6E)
- **Expected Ciphertext:** `45 A0 1F 64 5F C3 5B 38 35 52 54 4B 9B F5`

### Chạy test vectors

Để test với các test vector trên, sửa giá trị `plaintext_str` và `key_str` trong file `main_encrypt.c` và `main_decrypt.c`, sau đó biên dịch lại.

**Ví dụ:**
```c
const char *plaintext_str = "Plaintext";
const char *key_str = "Key";
```

## 📚 Giải thích thuật toán RC4

RC4 là thuật toán mã hóa dòng (stream cipher) bao gồm 2 giai đoạn chính:

### 1. Key Scheduling Algorithm (KSA)

- **Khởi tạo:** Tạo mảng hoán vị S với 256 giá trị từ 0-255
- **Xáo trộn:** Xáo trộn mảng S dựa trên khóa đầu vào
```c
void rc4_key_schedule(RC4_Context *ctx, const uint8_t *key, size_t key_len) {
    // Khởi tạo S = [0, 1, 2, ..., 255]
    for (int i = 0; i < 256; i++) {
        ctx->state[i] = i;
    }
    
    // Xáo trộn dựa trên khóa
    uint8_t j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + ctx->state[i] + key[i % key_len]) % 256;
        swap(ctx->state[i], ctx->state[j]);
    }
}
```

### 2. Pseudo-Random Generation Algorithm (PRGA)

- **Sinh keystream:** Tạo dòng byte pseudo-random từ mảng S
- **Mã hóa/Giải mã:** XOR keystream với plaintext/ciphertext
```c
uint8_t rc4_generate_byte(RC4_Context *ctx) {
    ctx->idx1 = (ctx->idx1 + 1) % 256;
    ctx->idx2 = (ctx->idx2 + ctx->state[ctx->idx1]) % 256;
    swap(ctx->state[idx1], ctx->state[idx2]);
    
    uint8_t k = (ctx->state[idx1] + ctx->state[idx2]) % 256;
    return ctx->state[k];
}
```

### Đặc điểm quan trọng:

- **Đối xứng:** Mã hóa và giải mã sử dụng cùng một quy trình (XOR với keystream)
- **Kích thước khóa linh hoạt:** Hỗ trợ khóa từ 40-2048 bits (thường dùng 128 bits)
- **Đơn giản và nhanh:** Thuật toán đơn giản, tốc độ xử lý cao

## 🔍 Chi tiết Implementation

### Cấu trúc RC4_Context
```c
typedef struct {
    uint8_t state[256];  // Mảng trạng thái S
    uint8_t idx1;        // Chỉ số i (cho PRGA)
    uint8_t idx2;        // Chỉ số j (cho PRGA)
} RC4_Context;
```

### Các hàm chính

**rc4.h / rc4.c:**
- `rc4_initialize()` - Khởi tạo context RC4 với khóa
- `rc4_key_schedule()` - Key Scheduling Algorithm
- `rc4_generate_byte()` - Pseudo-Random Generation Algorithm
- `rc4_process_data()` - Xử lý dữ liệu (mã hóa/giải mã)

**rc4_encrypt.h:**
- `encrypt_data()` - Hàm mã hóa chính
- `display_hex_output()` - Hiển thị ciphertext dạng hex
- `display_char_output()` - Hiển thị ciphertext dạng ký tự
- `save_to_file()` - Lưu ciphertext vào file

**rc4_decrypt.h:**
- `decrypt_data()` - Hàm giải mã chính
- `display_decrypted_text()` - Hiển thị plaintext
- `display_decrypted_hex()` - Hiển thị plaintext dạng hex
- `load_from_file()` - Đọc ciphertext từ file

## 🎯 Các điểm cải tiến so với implementation cơ bản

1. **Cấu trúc dữ liệu:**
   - Sử dụng `RC4_Context` thay vì struct đơn giản
   - Tên biến `idx1, idx2` thay vì `i, j` (rõ ràng hơn)

2. **Tách module:**
   - Tách implementation ra file `rc4.c` riêng
   - Module hóa encrypt/decrypt functionality

3. **Tên hàm mô tả:**
   - `rc4_initialize()` - Khởi tạo rõ ràng
   - `rc4_key_schedule()` - Tên đầy đủ thay vì KSA
   - `rc4_generate_byte()` - Mô tả chính xác chức năng
   - `encrypt_data()`, `decrypt_data()` - Ngắn gọn, dễ hiểu

4. **Error handling:**
   - Kiểm tra lỗi khi đọc/ghi file
   - Thông báo lỗi chi tiết cho người dùng
   - Return codes để xử lý lỗi

5. **Code quality:**
   - Comment đầy đủ bằng tiếng Việt
   - Format code nhất quán
   - Tuân thủ coding conventions

## ⚠️ Lưu ý bảo mật

**QUAN TRỌNG:** RC4 hiện không còn được khuyến nghị sử dụng trong các ứng dụng bảo mật thực tế do các lỗ hổng đã được phát hiện. Dự án này **CHỈ phục vụ mục đích học tập và nghiên cứu**.

### Các lỗ hổng đã biết:

1. **Bias trong keystream:**
   - Byte thứ 2 của keystream có xác suất không đồng đều
   - Có thể bị tấn công thống kê với đủ dữ liệu

2. **Weaknesses trong WEP:**
   - RC4 đã bị tấn công thành công trong giao thức WEP
   - Không nên dùng cho mã hóa wireless

3. **Related-key attacks:**
   - Dễ bị tấn công khi sử dụng các khóa có liên quan

4. **Không có authentication:**
   - RC4 chỉ mã hóa, không xác thực tính toàn vẹn dữ liệu

### Khuyến nghị:

- Dùng **AES** cho mã hóa đối xứng hiện đại
- Dùng **ChaCha20** cho stream cipher an toàn hơn
- Luôn kết hợp với MAC (Message Authentication Code)

## 📝 Ví dụ sử dụng

### Ví dụ 1: Sử dụng mặc định
```bash
# Build
make all

# Chạy mã hóa
./encrypt
# Output: Ciphertext được lưu vào ciphertext.bin

# Chạy giải mã
./decrypt
# Output: Hiển thị plaintext gốc
```

### Ví dụ 2: Tùy chỉnh plaintext và key

**Bước 1:** Sửa file `main_encrypt.c`
```c
const char *plaintext_str = "Hello World";
const char *key_str = "SecretKey123";
```

**Bước 2:** Sửa file `main_decrypt.c`
```c
const char *key_str = "SecretKey123";  // Phải giống với mã hóa
```

**Bước 3:** Build và chạy
```bash
make clean
make all
make test
```

### Ví dụ 3: Output mẫu
```
=== RC4 ENCRYPTION ===
Plaintext: Hanoi University of Science and Technology
Key: MySecretKey
Plaintext length: 43 bytes
Key length: 11 bytes

Ciphertext (Hex): A3 5F 8E ... [các byte hex]
Ciphertext (Chars): ._. ... [các ký tự]
Đã lưu ciphertext vào file: ciphertext.bin

Đã hoàn thành quá trình mã hóa!
Chạy ./decrypt để giải mã file ciphertext.bin
```

## 🐛 Debugging và Troubleshooting

### Lỗi thường gặp:

1. **"Không thể mở file để đọc"**
   - **Nguyên nhân:** Chưa chạy encrypt trước
   - **Giải pháp:** Chạy `./encrypt` trước khi chạy `./decrypt`

2. **Plaintext sau giải mã không đúng**
   - **Nguyên nhân:** Key mã hóa và giải mã khác nhau
   - **Giải pháp:** Đảm bảo key trong `main_encrypt.c` và `main_decrypt.c` giống nhau

3. **Compilation error**
   - **Nguyên nhân:** Thiếu file hoặc compiler không hỗ trợ C99
   - **Giải pháp:** Kiểm tra có đủ các file `.h` và `.c`, dùng GCC với flag `-std=c99`

4. **Warning về unused variable**
   - **Nguyên nhân:** Có biến khai báo nhưng không dùng
   - **Giải pháp:** Loại bỏ các biến không dùng hoặc sử dụng chúng

### Debug tips:
```bash
# Biên dịch với debug symbols
gcc -g -Wall -Wextra -std=c99 -I. main_encrypt.c rc4.c -o encrypt

# Chạy với valgrind để check memory leaks
valgrind --leak-check=full ./encrypt

# Dùng gdb để debug
gdb ./encrypt
```

## 🧪 Kiểm tra tính đúng đắn

### Test 1: Encryption -> Decryption
```bash
make test
```

Kết quả mong đợi:
- Ciphertext được tạo ra
- Plaintext sau giải mã phải giống với plaintext ban đầu

### Test 2: Test với các test vectors chuẩn

Sửa code để test với test vectors trong RFC 6229:
```c
// Test 2.1
const char *plaintext_str = "Plaintext";
const char *key_str = "Key";
// Expected: BB F3 16 E8 D9 40 AF 0A D3
```

Chạy và so sánh output với expected ciphertext.

### Test 3: File integrity
```bash
# Sau khi chạy encrypt
ls -lh ciphertext.bin  # Kiểm tra file size

# Xem nội dung dạng hex
hexdump -C ciphertext.bin

# So sánh với plaintext length
# File size phải bằng plaintext length
```

## 📊 Performance

RC4 là một trong những stream cipher nhanh nhất:

- **Tốc độ:** Rất cao, chỉ cần vài phép toán đơn giản cho mỗi byte
- **Memory:** Chỉ cần 256 bytes cho state array
- **Initialization:** Nhanh, O(256) operations

### Benchmark (ước tính):

- KSA: ~256 operations
- PRGA: ~10 operations per byte
- Throughput: Hàng trăm MB/s trên CPU hiện đại

## 📄 License

MIT License - Free for educational purposes

## 👨‍🎓 Thông tin

- **Môn học:** Mật mã học
- **Trường:** Hanoi University of Science and Technology (HUST)
- **Mục đích:** Học tập và nghiên cứu thuật toán mã hóa
- **Năm:** 2024

## 📚 Tài liệu tham khảo

1. **Wikipedia - RC4**  
   https://en.wikipedia.org/wiki/RC4

2. **RFC 6229 - Test Vectors for the Stream Cipher RC4**  
   https://tools.ietf.org/html/rfc6229

3. **Applied Cryptography - Bruce Schneier**  
   Chapter on Stream Ciphers

4. **IETF Draft - The RC4 Stream Encryption Algorithm**  
   Historical documentation

5. **Cryptanalysis of RC4**  
   Various academic papers on RC4 weaknesses

## 🤝 Contributing

Đây là project học tập. Nếu bạn tìm thấy bug hoặc có cải tiến:

1. Tạo issue mô tả vấn đề
2. Fork repository
3. Tạo branch mới
4. Commit changes
5. Tạo Pull Request

## ❓ FAQ

**Q: Tại sao cần 2 chương trình riêng cho encrypt và decrypt?**  
A: Để dễ sử dụng và demo. Trong thực tế, có thể gộp chung với command-line arguments.

**Q: Có thể mã hóa file binary không?**  
A: Có, RC4 hoạt động trên byte stream, không quan tâm nội dung là text hay binary.

**Q: Key length tối ưu là bao nhiêu?**  
A: Thường dùng 128 bits (16 bytes) cho security tốt và performance cao.

**Q: RC4 có an toàn không?**  
A: Không. RC4 đã bị deprecated. Chỉ dùng cho học tập, không dùng trong production.

**Q: Có thể dùng RC4 cho HTTPS không?**  
A: Không nên. Các trình duyệt hiện đại đã loại bỏ RC4 khỏi SSL/TLS.

---

**Lưu ý:** Code này được phát triển cho mục đích giáo dục. **KHÔNG** sử dụng RC4 trong các ứng dụng production đòi hỏi bảo mật cao! 🔒

**Happy Coding! 🎉**
