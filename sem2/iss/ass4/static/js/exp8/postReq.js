//The default method is ECB in which only plaintext and Key are required, hence these are hidden
$("#ivtext").hide();
$("#ctrtext").hide();

// Selection of modes should only display the textboxes required
function selectMode(){
    
    var iv = $("#ivtext");
        var ctr = $("#ctrtext");

    iv.hide();
    ctr.hide();

    $("select#mode").change(function() {
        iv.show();
        ctr.show();

        // ECB mode only requires key & plaintext
        if (this.value == "ecb") {
            iv.hide();
            ctr.hide();
        } 
        // CBC mode also requires an IV
        else if (this.value == "cbc") {
            ctr.hide();
        } 
        // CTR mode requires a counter but not an IV
        else if (this.value == "ctr") {
            iv.hide();
        } 
         // OFB mode also requires an IV
        else if (this.value == "ofb") {
            ctr.hide();
        }
    });
        
    item =  document.getElementById('mode').value;
    
    // Sending the mode to the python script so the validation can be done properly
    $.ajax({
        type: "POST",
        url:"/experiment/selectMode",
        data: JSON.stringify(item),
        contentType: 'application/json;charset=UTF-8',
    });
}

function selectKey(){
    
    item =  document.getElementById('keySize').value;
    // Change of the Key Size affects the algorithm, hence sending it to the script
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
    // For XOR to be properly calculated, the two stings must be of equal length
    if(item["one"].length!=item["two"].length)
        alert("Enter strings of same length!")
    else
    {
        // XOR is calculated by the python script, hence sending it
        $.ajax({
            type: "POST",
            url:"/experiment/answer",
            data: JSON.stringify(item),
            contentType: 'application/json;charset=UTF-8',

        success: function(result){
            $('#xor').text(result);
            }
        });
    }
}

function doEncryption() {
    // For AES encryption, the Key and the Plaintext size must be of 16 bytes
    // But the values taken are in hex, hence the size must be 32 hex
    // The Plaintext and Key printed above are space seperated for readability
    // hence if coppied directly, the size is 35 bytes which should also be accepted 
    item ={}
    item["one"] = document.getElementById('key').value;
    if(item["one"].length!=32 && item["one"].length!=35)
        alert("Key should only have 16 bytes of characters")
    else{    
        item["two"] = document.getElementById('plaintext').value;
        if(item["two"].length!=32 && item["two"].length!=35)
            alert("Plaintext should only have 16 bytes of characters")
        else{
            $.ajax({
                type: "POST",
                url:"/experiment/encrypt",
                data: JSON.stringify(item),
                contentType: 'application/json;charset=UTF-8',

            success: function(result){
                $('#ciphertext').val(result);
                }
            });
        }
    }
}

function doDecryption() {
    //Similarly, decryption also requires 32 hex length
    item ={}
    item["one"] = document.getElementById('key').value; 
    if(item["one"].length!=32 && item["one"].length!=35)
        alert("Key should only have 16 bytes of characters")
    else{
        item["two"] = document.getElementById('ciphertext').value;
        if(item["two"].length!=32 && item["two"].length!=35)
            alert("Ciphertext should only have 16 bytes of characters")
        else{
            $.ajax({
                type: "POST",
                url:"/experiment/decrypt",
                data: JSON.stringify(item),
                contentType: 'application/json;charset=UTF-8',

            success: function(result){
                $('#plaintext').val(result);
                }
            });
        }
    }
}

function checkAnswer() {
    // The answer calculated by the user is already precalculated by the program, hence  when asked to check
    // It is sent to the script for validation
    item = document.getElementById('userans').value; 

    $.ajax({
        type: "POST",
        url:"/experiment/check",
        data: JSON.stringify(item),
        contentType: 'application/json;charset=UTF-8',

    success: function(result){
        if(result == "True")
            alert("Answer is correct!")
        else alert("Answer is incorrect!")
        }
    });
}