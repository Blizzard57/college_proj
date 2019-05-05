from aesLib import *

#For the ECB method
key = "c42abbad 545471f9 b52fc4cc 3b1fcab9"
plaintext = "36a1a2df 6e589888 da407754 ead9564d 891725ec d6d61674 33b2cbce aafa574a dc7fc5af 95e4898d 2ed630f2 0ace0db3 bdd7a6c4 1ba98e92 fcf63ff3 80479b98 ba6dc685 97adeeef cfb36061 a53d0702"
iv = "49dcdd47 94d58ee1 6c73bc30 18e30cc6"
ctr = "18459974 b8ca57fe"
encyptedDataECB = "6efcc18759b4091fc27e1ae901da33f2 d2d87efb529263b2eb2677b7846fd5ec 537a83f2cda1f134acb60bd303bf3d78 95f12b6dbfef7233e6d307a167a86b8e b67bfb6848ece712b92db5062efce9a3"
encyptedDataCBC = "c27b56b7 5d540185 f8c49c75 b1e09a7a 7ea500b6 fa11a80c a0578398 dac84b15 62ca253b 418f8433 73ad4b92 3cfcdf31 20b1a986 37182336 d5be1316 0dff1d3e 7c34842e c5c55c99 5f9835f3 c8df6091"
encyptedDataOFB = "66b8a5aa 38bc654a c557222c f30eb6c0 347f6afd d9344ff9 884ce954 3a1781cf a2e61182 e90d2e82 9205f1d6 2ee16fbd c594e22e 97f63ce0 d516d691 2698c7fd fb26dbe1 347d9bf0 2e6b89e4 59609343"
encyptedDataCTR = "ff5b16de 59fb7b84 15542088 504bb575 af7457f5 f98bf13b b4511688 1ba850cc 83b605fb afc1cdcc 9ceb6a7e 38dce73f 4ac681b5 93608d74 e864c747 9e56b931 f44310b1 72c434d9 1e67f07a eab6c527"

#All the variables in required format
#The values given above are Hex but the program evaluates everything in bytes
#Hence removing all the spaces and converting to bytes
keyReq = bytes.fromhex("".join(key.split(" ")))
plaintextReq = bytes.fromhex("".join(plaintext.split(" ")))
ivReq = bytes.fromhex("".join(iv.split(" ")))
ctrReq = bytes.fromhex("".join(ctr.split(" ")))
encyptedDataECBReq = bytes.fromhex("".join(encyptedDataECB.split(" ")))
encyptedDataCBCReq = bytes.fromhex("".join(encyptedDataCBC.split(" ")))
encyptedDataOFBReq = bytes.fromhex("".join(encyptedDataOFB.split(" ")))
encyptedDataCTRReq = bytes.fromhex("".join(encyptedDataCTR.split(" ")))

#This is the object generated to give the output required
def computation(mode):
    new = aesMeth(mode)
    new.key = keyReq
    new.plaintext = plaintextReq
    new.iv = ivReq
    new.ctr = ctrReq
    return new.encrypt()

def test_ECB():
    assert computation("ECB") == encyptedDataECBReq

def test_CBC():
    assert computation("CBC") == encyptedDataCBCReq

def test_OFB():
    assert computation("OFB") == encyptedDataOFBReq

def test_CTR():
    assert computation("CTR") == encyptedDataCTRReq
