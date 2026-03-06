# 動態處理器 (Compressor) 架構藍圖與學習筆記

本篇筆記基於業界經典論文 **《Digital Dynamic Range Compressor Design — A Tutorial and Analysis》 (Giannoulis, Massberg, and Reiss, JAES 2012)** 與相關教材彙整。

## 🎯 核心概念：什麼是數位 Compressor？

Compressor 本質上是一個「**自動調整音量的機器人**」。相較於 Filter 是操作頻率，Compressor 是操作**時域 (Time Domain) 上的非線性控制**。

一個標準的現代數位 Compressor (通常採用 Feed-forward 架構) 是由 **4 個模塊** 串接而成的系統。在 C++ 實作中，這 4 個模塊通常會對應到 4 個不同的類別或處理步驟。

---

## 🏗️ 4 大基礎模塊詳解

### 1. 偵測器 (Level Detector / Envelope Follower)
*   **目標**：把具有正負震盪的交流音訊 (AC)，轉換成一條代表「音量大小（輪廓）」的平滑正數曲線 (DC 包絡線)。
*   **數學實作原理**：
    *   **Peak 偵測 (峰值)**：直接對訊號取絕對值 `abs(x)`。反應極快，適合捕捉瞬間的瞬態 (Transients)。
    *   **RMS 偵測 (均方根)**：較貼近人類聽覺。先將訊號平方 `x^2`，接著通過一個低通濾波器 (一階 LPF)，最後開根號 `sqrt()`。

### 2. 增益電腦 (Gain Computer / Static Curve)
*   **目標**：計算「目前的訊號音量，距離我們設定的 Threshold，應該要被扣掉多少 dB？」這是一個純數學映射 (Static Transfer Function)。
*   **數學實作原理**：
    *   轉換為分貝：`x_dB = 20 * log10(x)`
    *   判斷是否超過門檻 (Hard-knee 範例)：
        *   若 `x_dB <= Threshold`：不用動，`gain_reduction_dB = 0`
        *   若 `x_dB > Threshold`：`gain_reduction_dB = (Threshold - x_dB) * (1 - 1/Ratio)`
            *(這代表訊號超過門檻的部分，必須按照 Ratio 比例被壓下來)*
*   **進階 (Soft-knee)**：在 Threshold 轉折處放入一個二階多項式（平滑的拋物線），讓壓縮動作聽起來更自然。

### 3. 平滑器 (Ballistics / Attack & Release Envelope)
*   **目標**：增益電腦算出來的 `gain_reduction_dB` 會變化得非常劇烈，如果直接套用會產生失真 (Clipping/Zipper Noise)。我們必須讓它的變化「平滑化」。
*   **數學實作原理**：
    *   這是一個 **不對稱的一階低通濾波器 (Asymmetrical One-Pole LPF)**。
    *   當我們需要向下壓 (Gain 變小) 時，時間常數套用 **Attack Time**，計算出 $\alpha_A$。
    *   當我們釋放壓縮 (Gain 變大) 時，時間常數套用 **Release Time**，計算出 $\alpha_R$。
    *   這與我們實作 ParamSmoother 的概念極為相似，只是係數根據訊號前進方向動態切換。

### 4. 增益應用器 (Gain Application / VCA)
*   **目標**：將最終平滑後的 Gain 數值，乘回原始輸入訊號上。
*   **數學實作原理**：
    *   將 dB 轉換回線性數值：`linear_gain = 10^(smooth_gain_reduction_dB / 20)`
    *   輸出訊號：`output = input * linear_gain`
    *   *(通常還會再乘上一個 Make-up Gain 來補足整體失去的音量)*

---

## 🛠️ 研發/學習路徑建議 (Milestones)

在 `experiments/` 進行實作時，不建議一開始就挑戰完整的 Compressor。請循序漸進：

1.  **里程碑 1：Envelope Follower 圖形化**
    *   實作出能產生 RMS 與 Peak 曲線的類別。
    *   送入單純弦波或是鼓聲 (Drum Loop) WAV。
    *   透過 Python 畫出來，看看包絡線是否完美的把波形的「山峰」描繪出來。
2.  **里程碑 2：Attack/Release 平滑器 (Ballistics)**
    *   沿用 ParamSmoother 經驗，實作具備不對稱係數的平滑器。
    *   測試一個突然變小的方波，看看 Attack 曲線是否平滑抵達。
3.  **里程碑 3：Static Curve 與合體**
    *   完成純 dB 域的增益電腦。
    *   將 1, 2, 3, 4 串接，寫出第一支具備 Threshold, Ratio, Attack, Release 的標準 Compressor。
4.  **里程碑 4：Feed-forward 與 Feed-back 架構設計**
    *   研讀論文中介紹的 Branching point (分支點) 差異。
    *   (加分挑戰) 實作 Soft-Knee 插值。
