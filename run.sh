#!/usr/bin/env bash
set -e  # 出错立即退出

# 1. 生成 code.tex
echo "[INFO] Generating code.tex..."
python tools/gen.py

# 2. 编译 PDF
echo "[INFO] Building PDF..."
latexmk -xelatex -shell-escape -outdir=tex tex/template.tex

# 3. 编译成功后提示
echo "[OK] PDF generated at tex/template.pdf"

latexmk -c -outdir=tex tex/template.tex