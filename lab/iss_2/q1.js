function fifthDay(){
	var today= new Date();
	var weekday = [ "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" ];
		var n = weekday[(today.getDay()+5)%7];
console.log(n);
}
fifthDay();
