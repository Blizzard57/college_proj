(sleep $(( $2*60 ));notify-send "Reminder" "`echo $1`") &
echo $!
