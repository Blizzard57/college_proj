n=$1
for (( c=1; c<=n; c++ ))
do
echo "Time to Work !!"
sleep 1
if [ `echo $(($c%4))` -eq 0 ]
then
	echo "Time for a long break"
	sleep 3
else
	echo "Time for a short break"
	sleep 1    
fi
done 

