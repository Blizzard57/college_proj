function selectMode(){
    item =  document.getElementById('mode').value;
    console.log(document.getElementById('mode').value);
    $.ajax({
type: "POST",
url:"/experiment/selectMode",
data: JSON.stringify(item),
contentType: 'application/json;charset=UTF-8',
});
}

function selectKey(){
    item =  document.getElementById('keySize').value;
    console.log(document.getElementById('keySize').value);
    $.ajax({
type: "POST",
url:"/experiment/selectKey",
data: JSON.stringify(item),
contentType: 'application/json;charset=UTF-8',
});
}

function XOR() {
    item ={}
    item["one"] = document.getElementById('num1').value; 
        item["two"] = document.getElementById('num2').value;
        console.log(item);

        $.ajax({
type: "POST",
url:"/experiment/answer",
data: JSON.stringify(item),
contentType: 'application/json;charset=UTF-8',

success: function(result){
$('#xor').text(result);
console.log(result);
}
});
}

function doEncryption() {
    item ={}
    item["one"] = document.getElementById('key').value; 
        item["two"] = document.getElementById('plaintext').value;
        console.log(item);

        $.ajax({
type: "POST",
url:"/experiment/encrypt",
data: JSON.stringify(item),
contentType: 'application/json;charset=UTF-8',

success: function(result){
$('#ciphertext').val(result);
console.log(result);
}
});
}

function doDecryption() {
    item ={}
    item["one"] = document.getElementById('key').value; 
        item["two"] = document.getElementById('ciphertext').value;
        console.log(item);

        $.ajax({
type: "POST",
url:"/experiment/decrypt",
data: JSON.stringify(item),
contentType: 'application/json;charset=UTF-8',

success: function(result){
$('#plaintext').val(result);
console.log(result);
}
});
}

function checkAnswer() {
    item = document.getElementById('userans').value; 
        console.log(item);

        $.ajax({
type: "POST",
url:"/experiment/check",
data: JSON.stringify(item),
contentType: 'application/json;charset=UTF-8',

success: function(result){
console.log(result);
}
});
}
