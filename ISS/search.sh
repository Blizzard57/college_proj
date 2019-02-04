clear
echo \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ Search Script
if [ "$#" != "2" ]
then
	echo "PLease provide the correct number of arguemnts."
else
	CURL_RESPONSE=`curl -s -o /dev/null -w "%{http_code}" $2`
	if [[ $CURL_RESPONSE -eq 000 ]]
	then
		echo "URL does not exist."
	else
		wget $2 -q -O temp.html
		sed -e 's/<[^>]*>//g' temp.html > temp2.txt
		temp_var=`tr ' ' '\n' < temp2.txt | grep $1 | wc -l`
		echo "$1 $temp_var"
		rm temp.html temp2.txt
	fi
fi

