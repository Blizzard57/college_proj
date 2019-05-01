function getHighestMarks(){
	let data = require("./data.js")
	var x;
	var max =0;
	var name;
	for(x in data)
	{
		var arr = data[x];
		var marks = arr[0] + arr[1] + arr[2] + arr[3] + arr[4];
		if(marks > max)
		{
			max = marks;
			name = x;
		}
	}
//	console.log(name);
	return name;
}
function getSubject2Toppers(){
	let data = require("./data.js")
	var x;
	var students = [];
	for(x in data)
	{
		students.push(x);
	}
	students.sort(function(n1,n2){return data[n2][1] - data[n1][1]})
	return students;
}
var wow = getHighestMarks();
console.log(wow);
var arr = getSubject2Toppers();
console.log(arr);
