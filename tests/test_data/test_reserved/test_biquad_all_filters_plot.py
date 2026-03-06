# 接收來自 test_1st_half.cpp 的輸出
# 功能：自動繪製多個濾波器的頻率響應以進行綜合驗證

import numpy as np 
import matplotlib.pyplot as plt
import soundfile as sf
from scipy.fft import rfft, rfftfreq
import os

filters = ["LPF", "HPF", "BPF", "Notch", "Peaking", "LShelf", "HShelf"]
colors = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red', 'tab:purple', 'tab:brown', 'tab:pink']

cutoff_freq = 1000.0
gain_db = 6.0

fig, ax = plt.subplots(figsize=(10, 6))

for f_name, color in zip(filters, colors):
    filename = f"testOutput_{f_name}.wav"
    if not os.path.exists(filename):
        print(f"找不到檔案: {filename}")
        continue
    
    data, sr = sf.read(filename)
    
    # 計算頻率響應
    N = len(data)
    yf = rfft(data)
    xf = rfftfreq(N, 1 / sr)
    
    # 轉換為 dB，加上微小值避免 log(0)
    magnitude_db = 20 * np.log10(np.abs(yf) + 1e-10)
    
    # 使用對數頻率軸畫圖 (更符合真實聽覺及Bode Plot標準)
    ax.semilogx(xf, magnitude_db, color=color, label=f_name, linewidth=1.5)

# --- 添加關鍵參考平水與垂直線 ---
ax.axvline(x=cutoff_freq, color='k', linestyle='--', alpha=0.7, label=f'Cutoff Frequency ({cutoff_freq} Hz)')
ax.axhline(y=0, color='k', linestyle='-', linewidth=0.8)
ax.axhline(y=-3.0, color='gray', linestyle=':', label='-3 dB (LPF/HPF/BPF Cutoff)')
ax.axhline(y=gain_db, color='c', linestyle=':', label=f'+{gain_db} dB (Peaking/Shelf Max)')
ax.axhline(y=-gain_db, color='m', linestyle=':', label=f'{-gain_db} dB (Shelf Min/Notch)')

ax.set_title("Biquad Filters Frequency Response Showcase")
ax.set_xlabel("Frequency (Hz) - Log Scale")
ax.set_ylabel("Magnitude (dB)")
ax.set_xlim(20, sr // 2)
ax.set_ylim(-30, 15)
ax.grid(True, which="both", ls="-", alpha=0.3)
ax.legend(loc='lower left', prop={'size': 9})

plt.tight_layout()
plt.show()

print("所有濾波器分析與繪圖完成！")
