# 接收來自 test_1st_half.cpp 的輸出
# 功能：自動繪製時域脈衝響應與頻域頻率響應

import numpy as np 
import matplotlib.pyplot as plt
import soundfile as sf
from scipy.fft import rfft, rfftfreq

# 1. 讀取 WAV 檔案 (注意順序：data, sr)
try:
    data, sr = sf.read("filter_ir_results.wav")
except Exception as e:
    print(f"找不到檔案或讀取失敗: {e}")
    exit()

# 2. 準備畫圖 (1x2 佈局：時域 + 頻域)
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))
plt.subplots_adjust(hspace=0.4)

# --- 時域圖 (Impulse Response) ---
# 脈衝響應通常在開頭，我們只畫前 1000 個點來觀察細節
zoom_samples = 1000
ax1.plot(data[:zoom_samples], color='teal')
ax1.set_title(f"Impulse Response (First {zoom_samples} samples)")
ax1.set_xlabel("Sample Index")
ax1.set_ylabel("Amplitude")
ax1.grid(True, alpha=0.3)

# --- 頻域圖 (Frequency Response) ---
# 執行 FFT 轉換為頻率響應
N = len(data)
yf = rfft(data)
xf = rfftfreq(N, 1 / sr)

# 轉換為分貝 (dB)
# 加上 1e-10 防止 log10(0) 錯誤
magnitude_db = 20 * np.log10(np.abs(yf) + 1e-10)

ax2.semilogx(xf, magnitude_db, color='crimson')
ax2.set_title("Frequency Response (Magnitude)")
ax2.set_xlabel("Frequency (Hz)")
ax2.set_ylabel("Magnitude (dB)")
ax2.set_xlim(20, sr // 2) # 0 到 尼奎斯特頻率
ax2.set_ylim(-60, 10)     # 觀察 -60dB 到 10dB 的範圍
ax2.grid(True, which="both", ls="-", alpha=0.3)

# 標註截止頻率 (1000Hz)
ax2.axvline(x=1000, color='orange', linestyle='--', label='Target: 1000Hz')
ax2.legend()

print(f"分析完成！取樣率: {sr} Hz, 數據長度: {len(data)} 樣本")
plt.show()
