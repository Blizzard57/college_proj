function getMeNextFirst(str){
	var hey = str.trim();
	var len = hey.length;
	var i;
	var wow = "";
	for(i=0;i<len;i++){
		if(hey[i]==' ' && i<hey.length -1){
			wow = wow + hey[i+1];
			wow=wow+' ';			
			i++;
			i++;
		}
		wow = wow + hey[i];
	}
	return wow;
}
var hey = "Hello World !!";
var wow = getMeNextFirst(hey);
console.log(wow);
