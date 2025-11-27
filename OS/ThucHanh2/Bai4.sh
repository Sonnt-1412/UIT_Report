#!/bin/bash
# Nhập chuỗi từ người dùng
read -p "Nhập chuỗi cần kiểm tra: " chuoi
if grep -q "$chuoi" test.txt; then
    echo "Chuỗi '$chuoi' tồn tại trong file test.txt"
else
    echo "Chuỗi '$chuoi' không tồn tại trong file test.txt"
fi
