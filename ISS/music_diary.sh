clear
if [ `ls | grep music_diary.csv | wc -l` -eq 0 ]
then
    touch music_diary.csv
    echo \*\*\*\*\*\*\*\*\*\* Initialization Screen \*\*\*\*\*\*\*\*\*\*
    echo
    echo This is the first time the script is being is being executed.
    echo Press 0 and [ENTER] if you want the default fields for the diary
    echo Press 1 and [ENTER] for having custom fields
    echo
    echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
    echo
    echo The Default fields include :
    echo ID  Song  Artist  Album  Genre
    echo
    echo Your Option :
    read init_var
    if [ `echo $init_var` -eq 0 ]
    then
        echo Defaults fields have been added to your script
        echo Song\|Artist\|Album\|Genre\|>>music_diary.csv
        n=4
    elif [ `echo $init_var` -eq 1 ]
    then
        touch temp_file
        clear
        echo \*\*\*\*\*\*\*\*\*\* Custom Option \*\*\*\*\*\*\*\*\*\*
        echo Please input the number of fields required \(Please add the fields in the priority order \):
        read n
        for (( i=1; i<=n; i++ ))
        do
            echo Enter Field Number $i
            read temp_var
            echo $temp_var>>music_diary.csv
            #cat music_diary.csv | tr '\n' '\0' >> music_diary.csv
            #paste music_diary.csv temp_file >> music_diary.csv
        done
        cat music_diary.csv | tr '\n' '|' >> music_diary.csv
        tail -1 music_diary.csv > temp_file
        cat temp_file > music_diary.csv
        rm temp_file
        echo -e "" >> music_diary.csv
        #cat music_diary.csv | sed 's.\n..g'
    else
        echo Incorrect option selected
        echo Defaults fields have been added to your script
        echo Song\|Artist\|Album\|Genre\|>>music_diary.csv
    fi
    clear
fi
echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Main Screen \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
echo
echo \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ Your Music Diary
echo Options Menu :
echo \(1\) Add a Song
echo \(2\) Delete a Song
echo \(3\) Add a Field
echo \(4\) Edit values for a Song
echo \(5\) View the Music Diary
echo \(6\) Quit the Menu
echo
echo
echo Your Option
read opt
clear
if [ `echo $opt` -eq 1 ]
then
    echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Song Addition \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
    echo
    touch temp_file
    for i in `cat music_diary.csv | head -1 | tr "|" " "`
    do
        echo Specify the $i :
        read temp_var
        echo $temp_var>>temp_file
    done
    echo -e `cat temp_file | tr '\n' '|'` >> music_diary.csv
    rm temp_file
    $0
elif [ `echo $opt` -eq 2 ]
then
    touch temp_file1
    touch temp_file2
    echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Song Deletion \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
    echo
    echo
    echo Enter the number of primary fields required :
    echo \*\* A primary field is one which has to match. The fields as added in a priority order, first n number of feilds should match \*\*
    read n
    i=1
    cat music_diary.csv > temp_file1
    for p in `cat music_diary.csv | head -1 | tr "|" " "`
    do
        echo Specify the $p :
        read temp_var
        echo $temp_var >> temp_file2
        #echo -e `cat temp_file2 | tr '\n' '|'` > temp_file1
        i=$(($i + 1))
        if [ `echo $i` -gt `echo $n` ]
        then
            break
        fi
    done
    echo -e `cat temp_file2 | tr '\n' '|'` > temp_file1
    #cat temp_file1
    sed -i "/$(cat temp_file1)/d" music_diary.csv
    rm temp_file1 temp_file2
    $0
elif [ `echo $opt` -eq 3 ]
then
    echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Addition of Field  \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
    echo
    echo
    echo Enter the number of fields to add  :
    read n
    for (( c=0; c<n; c++ ))
    do
        touch temp_file
        touch temp_file2
        echo Enter extra field $(($c+1))  :
        read p
        echo $p\| >> temp_file
        tr "\n" "|" temp_file
        paste -d "" music_diary.csv temp_file > temp_file2
        cat temp_file2 > music_diary.csv
        rm temp_file temp_file2
    done
    $0
elif [ `echo $opt` -eq 4 ]
then
    echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Editing Fields  \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
    echo
    touch temp_file1
    touch temp_file2
    echo Enter the number of primary fields required :
    echo \*\* A primary field is one which has to match. The fields as added in  a priority order, first n number of feilds should match \*\*
    read n
    i=1
    cat music_diary.csv > temp_file1
    for p in `cat music_diary.csv | head -1 | tr "|" " "`
    do
        echo Specify the $p :
        read temp_var
        echo $temp_var >> temp_file2
        #echo -e `cat temp_file2 | tr '\n' '|'` > temp_file1
        i=$(($i + 1))
        if [ `echo $i` -gt `echo $n` ]
        then
            break
        fi
    done
    echo -e `cat temp_file2 | tr '\n' '|'` > temp_file1
    #cat temp_file1
    sed -i "/$(cat temp_file1)/d" music_diary.csv
    rm temp_file1 temp_file2
    clear
    echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Editing Fields  \*\*\*\*\*\*\*\*\*\*\*\* \*\*\*
    echo
    touch temp_file
    for i in `cat music_diary.csv | head -1 | tr "|" " "`
    do
        echo Specify the $i :
        read temp_var
        echo $temp_var>>temp_file
    done
    echo -e `cat temp_file | tr '\n' '|'` >> music_diary.csv
    rm temp_file
    $0
elif [ `echo $opt` -eq 5 ]
then
    echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Diary View \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
    echo Do you want a specific data field to sort from ? \(Specify the field if yes else write \[n\]\)
    read n
    if [ $n == "n" ]
    then
        clear
        column -t -s"|" music_diary.csv
        echo
        echo
        echo
        echo
        echo Press \[ENTER\] to return to the main menu
        read v
    else
        clear
        column -t -s"|" music_diary.csv | grep $n
        echo
        echo
        echo
        echo
        echo Press \[ENTER\] to return to the main menu
        read v
    fi
    $0
    #elif [ `echo $opt` == "q"]
    #then
    #clear
    #echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Quitting \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
    #sleep 2
    clear
fi
