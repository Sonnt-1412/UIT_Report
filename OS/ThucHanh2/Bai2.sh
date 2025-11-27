#!/bin/bash
MY_MSSV="123456"

echo "Enter Your Name"
read name
while true; do
	read -p "Enter Your ID" mssv
	if [ "$mssv" = "$MY_MSSV" ]; then
		break
	else 
		echo "MSSV không đúng, vui lòng nhập lại."
	fi
done
echo "Tên: $name"
echo "MSSV: $mssv"
 
