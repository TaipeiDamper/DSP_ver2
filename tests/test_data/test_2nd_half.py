# 接收來自 test_1st_half.cpp 的輸出
# 功能：自動繪製時域脈衝響應與頻域頻率響應

import numpy as np 
import matplotlib.pyplot as plt
import soundfile as sf
from scipy.fft import rfft, rfftfreq

# 1. 讀取 WAV 檔案 (注意順序：data, sr)
import os

filename = "testOutput.wav"
if not os.path.exists(filename):
    filename = "test.wav"

try:
    data, sr = sf.read(filename)
except Exception as e:
    print(f"找不到檔案 or 讀取失敗: {e}")
    exit()

# 2. 準備畫圖 (2x1 佈局)
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))
plt.subplots_adjust(hspace=0.4)

# --- 時域圖 (Full Duration) ---
time_axis = np.linspace(0, len(data)/sr, len(data))
ax1.plot(time_axis, data, color='teal')
ax1.set_title(f"Time Domain Signal (Full Duration: {len(data)/sr:.2f}s)")
ax1.set_xlabel("Time (s)")
ax1.set_ylabel("Amplitude")
ax1.grid(True, alpha=0.3)

# --- 頻域圖 (Frequency Response) ---
N = len(data)
yf = rfft(data)
xf = rfftfreq(N, 1 / sr)

# 轉換為分貝 (dB)
magnitude_db = 20 * np.log10(np.abs(yf) + 1e-10)

# 使用線性頻率軸以顯示完整的 0 ~ Nyquist
ax2.semilogx(xf, magnitude_db, color='crimson')
ax2.set_title("Frequency Response (0 Hz ~ Nyquist)")
ax2.set_xlabel("Frequency (Hz)")
ax2.set_ylabel("Magnitude (dB)")
ax2.set_xlim(20, sr // 2) 
ax2.set_ylim(-20, 10) # 擴大觀察範圍
ax2.grid(True, ls="-", alpha=0.3)

print(f"分析完成！檔案: {filename}, 取樣率: {sr} Hz, 長度: {len(data)} 樣本")
plt.show()
