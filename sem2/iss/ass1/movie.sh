mkdir -p $2Bad/
mkdir -p $2Average/
mkdir -p $2Good/
mkdir -p $2Awesome/
j=1
for i in `cat $1 | cut -d ":" -f 2 | cut -b 1 | tr "\n" " "`
do
	x="$(cat $1 | cut -d ":" -f 1 | head -`echo $j` | tail -1)"
	if [ $i -lt 5 ]
	then
		touch $2Bad/$x.mp4
	elif [ $i -lt 8 ]
	then
		touch $2Average/$x.mp4
	elif [ $i -lt 9 ]
	then
		touch $2Good/$x.mp4
	else
		touch $2Awesome/$x.mp4
	fi
	j=$(( $j + 1 ))
done
