i=1
while [ `echo $i` -le `echo $1` ];
do
    notify-send -t 2 "Time Management" "Time to Work !!"
    sleep 1500
    if [ `echo $(($i%4))` -eq 0 ]
    then
        notify-send -t 2 "Time Management" "Time for a long break"
        sleep 900
    else
        notify-send -t 2 "Time Management" "Time for a short break"
        sleep 300
    fi
done &
