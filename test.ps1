# DSP 測試自動化腳本 (test_1st 專用)
# 內容：建置 -> 執行 -> 視覺化

Write-Host "`n[1/3] Building C++ (test_1st)..." -ForegroundColor Cyan
cmake --build build --config Debug --target test_1st
if ($LASTEXITCODE -ne 0) { Write-Host "Build Failed!" -ForegroundColor Red; exit }

Write-Host "`n[2/3] Running C++ (test_1st.exe)..." -ForegroundColor Cyan
.\build\Debug\test_1st.exe
if ($LASTEXITCODE -ne 0) { Write-Host "Execution Failed!" -ForegroundColor Red; exit }

Write-Host "`n[3/3] Plotting results via Python (test_2nd_half.py)..." -ForegroundColor Cyan
python tests\test_data\test_2nd_half.py

Write-Host "`nPipeline Success!" -ForegroundColor Green
