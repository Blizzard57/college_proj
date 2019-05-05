// Unless the show Answer is clicked, the textbox should not be available
$('#showans').css({"display": "none"})

function nextPlainText() {
    $.ajax({
		type: "GET",
		url:"/experiment/nextplaintext",

		success: function(result){
			$('#plainarea').text(result.plainarea);
		}
	});
}

function nextKey() {
    $.ajax({
		type: "GET",
		url:"/experiment/nextkey",

	success: function(result){
		$('#keyarea').text(result.key);
		}
	});
}

function nextIV() {
    $.ajax({
		type: "GET",
		url:"/experiment/nextIV",


	success: function(result){
		$('#iv').text(result.iv);
		}
	});
}

function nextCtr() {
    $.ajax({
		type: "GET",
		url:"/experiment/nextctr",


	success: function(result){
		$('#ctr').text(result.ctr);
		}
	});
}

function showAnswer() {
	$.ajax({
	type: "GET",
	url:"/experiment/showans",


success: function(result){
	$('#showans').css({"display": "block"})
	$('#showans').val(result.ans);
	}
});
}