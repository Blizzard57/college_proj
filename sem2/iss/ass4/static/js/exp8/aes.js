function trim(str) {
    return str.replace(/\s+/g,"");
}

function makeReadable(str) {
    var text = "";
    for( var i=0; i < str.length; i++ ) {
        if (i%8 == 0) {
            text += " ";
        }
        text += str.charAt(i);
    }
    return text;
}

/*function doEncryption()
{
    var pt, key;
    var theForm = document.forms[0];
    blockSizeInBits=128;
    keySizeInBits = theForm.keySize[theForm.keySize.selectedIndex].value;

    theForm.key.value = trim(theForm.key.value);
    theForm.plaintext.value = trim(theForm.plaintext.value);

    if (theForm.key.value.toLowerCase().indexOf("0x") == 0)
        theForm.key.value = theForm.key.value.substring(2);
    if (theForm.plaintext.value.toLowerCase().indexOf("0x") == 0)
        theForm.plaintext.value = theForm.plaintext.value.substring(2);

    if (theForm.key.value.length*4 != keySizeInBits) {
        alert("For a " + keySizeInBits + " bit key, the hex string needs to be " +
                (keySizeInBits / 4) + " hex characters long. But your key is of size " + theForm.key.value.length);
        if (theForm.key.select)
            theForm.key.select();
        return;
    }

    if (theForm.plaintext.value.length*4 != blockSizeInBits) {
        alert("For a " + blockSizeInBits + " bit block, the hex plaintext string needs to be " +
                (blockSizeInBits / 4) + " hex characters long.");
        if (theForm.plaintext.select)
            theForm.plaintext.select();
        return;
    }

    pt = hex2s(theForm.plaintext.value);
    key = hex2s(theForm.key.value);
    theForm.ciphertext.value = byteArrayToHex(rijndaelEncrypt(pt, key, "ECB"));

    theForm.key.value = makeReadable(theForm.key.value);
    theForm.plaintext.value = makeReadable(theForm.plaintext.value);
    theForm.ciphertext.value = makeReadable(theForm.ciphertext.value);
}
*/
function doDecryption() {
    var ct, key;
    var theForm = document.forms[0];
    blockSizeInBits=128;
    keySizeInBits = theForm.keySize[theForm.keySize.selectedIndex].value;

    if (theForm.key.value.toLowerCase().indexOf("0x") == 0)
        theForm.key.value = theForm.key.value.substring(2);
    if (theForm.ciphertext.value.toLowerCase().indexOf("0x") == 0)
        theForm.ciphertext.value = theForm.ciphertext.value.substring(2);

    if (theForm.key.value.length*4 != keySizeInBits) {
        alert("For a " + keySizeInBits + " bit key, the hex string needs to be " +
                (keySizeInBits / 4) + " hex characters long.");
        if (theForm.key.select)
            theForm.key.select();
        return;
    }

    if (theForm.ciphertext.value.length*4 != blockSizeInBits) {
        alert("For a " + blockSizeInBits + " bit block, the hex ciphertext string needs to be " +
                (blockSizeInBits / 4) + " hex characters long.");
        if (theForm.ciphertext.select)
            theForm.ciphertext.select();
        return;
    }

    ct = hex2s(theForm.ciphertext.value);
    key = hex2s(theForm.key.value);
    theForm.plaintext.value = byteArrayToHex(rijndaelDecrypt(ct, key, "ECB"));

}

function resetDisplay() {
    document.getElementById("ivtext").style.display = "none";
    document.getElementById("ctrtext").style.display = "none";
    document.getElementById("calculateXor").style.display = "none";
}

function randomHexString(length) {
    var text = "";
    var possible = "abcdef0123456789";

    for( var i=0; i < length; i++ ) {
        if (i%8 == 0) {
            text += " ";
        }
        text += possible.charAt(Math.floor(Math.random() * possible.length));
    }
    return text;
}

/*function nextPlainText() {
    $.ajax({
type: "GET",
url:"/experiment/nextplaintext",


success: function(result){
$('#plainarea').text(result.plainarea);
console.log(result);
console.log(result.plainarea)
}
});
}*/

/*function nextKey() {
    $.ajax({
type: "GET",
url:"/experiment/nextkey",


success: function(result){
$('#keyarea').text(result.key);
console.log(result.key)
}
});
}

function nextIV() {
    $.ajax({
type: "GET",
url:"/experiment/nextIV",


success: function(result){
$('#iv').text(result.iv);
//console.log(result);
}
});
}

function nextCtr() {
    $.ajax({
type: "GET",
url:"/experiment/nextctr",


success: function(result){
$('#ctr').text(result.ctr);
//console.log(result);
console.log("Ctr printed")
console.log(result.ctr)
}
});
}
*/

/*function XOR() {
    item ={}
    item["one"] = $('#keyarea').val()
        item["two"] = $('#plainarea').val()
        console.log(item)

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
*/
function Add_one(hexNum) {
    var l = hexNum.length-1;
    var carryOver = 1;

    var output = "";
    while (l >= 0) {
        var sum = parseInt(hexNum.charAt(l), 16) + carryOver;
        if (sum >= 16) {
            carry0ver = 1;
            sum = sum%16;
        } else {
            carryOver = 0;
        }
        output += sum.toString(16);
        l--;
    }

    var revOutput = ""; 
    for (i=output.length-1; i>-1; i--) { 
        revOutput += output.charAt(i); 
    } 
    return revOutput;
}

function displayXOR() {
    var hex1 = trim(document.getElementById("num1").value);
    var hex2 = trim(document.getElementById("num2").value);

    document.getElementById('xor').value = makeReadable(XOR(hex1, hex2));
}

function checkAnswer() {
    var userAns = document.getElementById("userans").value;
    if(userAns.length == 0) {
        alert("Please type in the answer");
        return;
    }
    var answer = "";
    var selectmenu = document.getElementById("select_mode");
    var chosen_option=selectmenu.options[selectmenu.selectedIndex].value;

    var plaintext = (document.getElementById("plainarea").value).split("\n");
    var key = hex2s(trim(document.getElementById("keyarea").value));

    if (chosen_option == "ecb") {
        for (i=0; i<plaintext.length-1; i++) { 
            var pt = trim(plaintext[i]);
            var tmp = byteArrayToHex(rijndaelEncrypt(hex2s(pt), key, "ECB"));
            answer += tmp;
        }

    } else if (chosen_option == "cbc") {
        var ci = trim(document.getElementById("iv").value);
        answer += ci;
        for (i=0; i<plaintext.length-1; i++) { 
            var pt = trim(plaintext[i]);
            tmp = XOR(ci, trim(plaintext[i]));
            ci = byteArrayToHex(rijndaelEncrypt(hex2s(tmp), key, "ECB"));
            answer += ci;
        }		
    } else if (chosen_option == "ofb") {
        var ri = trim(document.getElementById("iv").value);
        answer += ri;
        for (i=0; i<plaintext.length-1; i++) { 
            var pt = trim(plaintext[i]);
            ri = byteArrayToHex(rijndaelEncrypt(hex2s(ri), key, "ECB"));
            answer += XOR(pt, ri);
        }		
    } else {
        var ctr = trim(document.getElementById("ctr").value);
        answer += ctr;
        for (i=0; i<plaintext.length-1; i++) {
            var pt = trim(plaintext[i]);
            var ctr = Add_one(ctr);
            var ri = byteArrayToHex(rijndaelEncrypt(hex2s(ctr), key, "ECB"));
            answer += XOR(ri, pt);
        }
    }
    if(trim(userAns) == trim(answer)) {
        document.getElementById("notification").innerHTML = "CORRECT!!";
    } else {
        document.getElementById("notification").innerHTML = "Sorry, answer is wrong. Please try again.";
    }
}
