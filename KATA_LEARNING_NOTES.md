# KATA 學習筆記 (DSP 萬用工具箱)

這裡記錄了在 100 題 Code Kata 中學到的「絕對不能忘記」的關鍵技術與面試重點。

---

## ⚡️ 位元與記憶體黑魔法 (Sprint 1)

### 1. `std::memcpy` 的安全搬運術
在 DSP 中，我們常需要在不同類型（如 `float` 與 `int`）之間交換「位元內容」而不改變它們。直接轉型會觸發數值轉換或違反 C++ 的安全規則。

*   **用法備忘：**
    ```cpp
    #include <cstring>
    
    // 目的地與來源「都必須加 &」取地址
    // 第三個參數是「搬移的大小 (bytes)」
    std::memcpy(&destination, &source, sizeof(type));
    ```
*   **為什麼要加 `&`？** 因為 `memcpy` 是搬運工，它需要知道「從哪個地址搬」到「哪個地址」。
*   **面試點：** 這是避免 Strict Aliasing Rule 導致未定義行為 (UB) 的最穩定做法。

---

## 🛠 Sprint 1 常用標準庫工具 (std::)

這 10 題中我們頻繁使用的兵器庫，這些在實作 DSP 時極度常用：

| 函數 | 標頭檔 | 用途 | 備註 |
| :--- | :--- | :--- | :--- |
| `std::pow(base, exp)` | `<cmath>` | 次方運算 | 用於 dB 轉 Linear ($10^{dB/20}$) |
| `std::log10(x)` | `<cmath>` | 底數為 10 的對數 | 用於 Linear 轉 dB，**必加防 0 檢查** |
| `std::abs(x)` | `<cmath>` | 絕對值 | 偵測訊號強度或 Noise Gate 判斷 |
| `std::sin(rad)` | `<cmath>` | 正弦函數 | 用於 Constant Power Panning (等功率平移) |
| `std::cos(rad)` | `<cmath>` | 餘弦函數 | 用於 Constant Power Panning (等功率平移) |
| `std::tanh(x)` | `<cmath>` | 雙曲正切 | 最基本的 **Soft Clipper** (軟剪裁) 公式 |
| `std::clamp(v, lo, hi)` | `<algorithm>` | 數值區間限制 | **C++17** 必備，用於 Hard Clipper 或參數防呆 |
| `std::fill(beg, end, v)` | `<algorithm>` | 填充容器 | 用於快速清空或初始化 Buffer (KATA 011) |
| `std::copy(s_beg, s_end, d_beg)` | `<algorithm>` | 拷貝容器內容 | 用於 Buffer 之間的數據搬運 (KATA 012) |
| `std::memcpy(d, s, n)` | `<cstring>` | 記憶體拷貝 | 用於位元層級的操作 (如 Fast Abs) |

---

## 🎧 Buffer 操作邏輯 (Sprint 2)

### 1. 混音 (Mixing) 的本質
在數位訊號處理中，**混音就等於「加法」**。
*   當多個聲音 Buffer 同時輸出時，我們將它們對應位置的樣本相加即可。
*   **注意點**：相加後若超過 1.0 或低於 -1.0，會產生數位削波 (Clipping)，通常需要在最後加上一個 Clipper (KATA 007) 或 Limiter。

---

### 2. 絕對值的符號位：`0x7FFFFFFF`
浮點數 (32-bit float) 的最左邊一位 (Bit 31) 是符號位。
*   `0x7FFFFFFF` 的二進位是：`0111 1111 1111 1111 ...` (第一個是 0，後面全是 1)。
*   **用途：** 與浮點數的位元做 `&` (AND) 運算，能強制把符號位變 0（正數），達成「不用 if 的絕對值」。

---

*最後更新時間：2026-03-17*
