echo "Enter Your Number"
while true; do
	read n
	if [ $n -ge 10 ]; then
		break
	else
		echo "So phai lon hon 10"
	fi
done	
sum=0
for (( i=1; i<=n; i++ )); do
	sum=$((sum+i))
done
echo "Tổng các số từ 1 đến $n là: $sum"
