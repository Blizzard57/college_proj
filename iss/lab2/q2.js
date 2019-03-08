function altSpaceToUnderscore(x){
	var ram=x.trim();
	var lal=ram.split(" ");
	var n="";
	for(i=0;i<lal.length;i++){
		n=n+lal[i];
		if(i%2!=0 && i!=lal.length - 1){
			n=n+"_";
		}
		else if (i!=lal.length - 1)
			n=n+" ";
	}
	console.log(n)
}
altSpaceToUnderscore("Hello there, how are you !!");
