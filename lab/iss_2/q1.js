function fifthDay(){
	var d = new Date();
	var n = d.getDay();
	var m = (n + 5) % 7;
	var week = [ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" ];
	console.log(week[m]);
}
fifthDay();

