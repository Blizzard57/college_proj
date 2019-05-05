function checkQuiz() {

	correctAns = 0
	if($('input[name=A1]:checked').val() == "2") {
		document.getElementById('Q1').style.backgroundColor = "green";
		correctAns+=1;
	}

	else
	{
		document.getElementById('Q1').style.backgroundColor = "red";		
	}

	if($('input[name=A2]:checked').val()=="ECB") {
		document.getElementById('Q2').style.backgroundColor = "green";
		correctAns+=1;
	}

	else
	{
		document.getElementById('Q2').style.backgroundColor = "red";		
	}

	if($('input[name=A3]:checked').val()=="4"){
		document.getElementById('Q3').style.backgroundColor = "green";
		correctAns+=1;
	}

	else
	{
		document.getElementById('Q3').style.backgroundColor = "red";		
	}
	console.log($('input[name=A1]:checked').val())
	alert("You scored "+correctAns+"/3. Congrats!");
	correctAns=0;
}
