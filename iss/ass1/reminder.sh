clear
if [ `ls | grep rem_data.csv | wc -l` -eq 0 ]
then
    touch rem_data.csv
    echo Heading\;Time\;ID >> rem_data.csv
fi
echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Reminders \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
echo
echo \(1\) Set a reminder
echo \(2\) View reminders
echo \(3\) Edit reminder
echo \(4\) Delete reminder
echo \(5\) Quit the menu
read n
if [ `echo $n` -eq 1 ]
then
    clear
    echo Please enter the title of your reminder
    read t
    echo Please enter the time of your reminder \(24 Hours\)
    read m
    echo Please enter the frequency of the reminder \(Reminded every day\)
    read h
    for (( c=1; c<=h; c++ ))
    do
        #val=echo `./sing.sh $t $m`
        #sleep $(( $m*60 ));notify-send -t 2 "Reminder" "`echo $t`") &
        echo "notify-send "Reminder" "$t"" | at $m > /dev/null 2>&1
        val=`atq|sort -k1,1|tr "\t" " "|tail -1|cut -d " " -f1`
        echo $t\;$m\;$val>>rem_data.csv
        #read n
    done
    clear
    $0
elif [ `echo $n` -eq 2 ]
then
    clear
    column -t -s";" rem_data.csv
    echo
    echo
    echo
    echo
    echo
    echo
    echo Press return to go back to the main menu
    read v
    clear
    $0
elif [ `echo $n` -eq 3 ]
then
    clear
    echo Please specify the ID of the reminder to edit  :
    echo \(Press i to get the data table\)
    read p
    if [[ "$p" == "i" ]]
    then
        clear
        column -t -s ";" rem_data.csv
        echo
        echo
        echo
        echo
        echo
        echo
        echo Please enter the ID of the reminder to delete :
        read v
        atrm $v
        sed -i "/$v/d" music_diary.csv
    else
        sed -i "/$p/d" music_diary.csv
    fi
    echo Please enter the fields again\(Leave Empty if same\)
    echo Please enter the modified title :
    read v
    if [[ "$v" == "" ]]
    then
        v=echo `cat temp_file | cut -d"|" -f1`
    fi
    echo Pleae enter the modified time :
    read t
    if [[ "$t" == "" ]]
    then
        t=echo `cat temp_file | cut -d"|" -f2`
    fi
    echo Please enter the modified frequency :
    read m
    if [[ "$m" == "" ]]
    then
        m=echo `cat temp_file | cut -d"|" -f1`
    fi
    for (( c=1; c<m+1; c++ ))
    do
        #val=echo `./sing.sh $v $t`
        echo "notify-send "Reminder" "$v"" | at $t > /dev/null 2>&1
        val=`atq | sort -k1,1 |tr "\t" " "|tail -1|cut -d " " -f1`
        echo $vi\;$(($t*c))\;$val>>rem_data.csv
    done
    clear
    $0
elif [ `echo $n` -eq 4 ]
then
    clear
    echo Please enter the ID of the reminder to delete :
    echo \(Press i to get the data table\)
    read p
    if [[ "$p" == "i" ]]
    then
        clear
        touch temp_file
        column -t -s ";" rem_data.csv
        echo
        echo
        echo
        echo
        echo
        echo
        echo Please enter the ID of the reminder to delete :
        read v
        atrm $v
        sed -i "/$v/d" music_diary.csv
    else
        sed -i "/$p/d" music_diary.csv
    fi
    clear
    $0
else
    clear
fi
