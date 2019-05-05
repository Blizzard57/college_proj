# Importing libraries
from Crypto.Cipher import AES # Crypto.Cipher is the one which provides basic AES ancryption to the program
import numpy as np # Numpy allows modification and editing of the arays generated
from Crypto.Random import get_random_bytes # Random function allows to generate random keys and IVs required for encryption

def xor(str1,str2):
    ''' Gives the XOR of two hex stings with same length'''
    if(len(str1) == len(str2)):
        return "".join(["%x" % (int(x,16) ^ int(y,16)) for (x, y) in zip(str1, str2)])
    else :
        raise ValueError("Enter strings of equal lengths for XOR")

def printReadable(string, length):
    ''' Prints the given string by splitting it with spaces for every n letters mentioned in length'''
    try :
        return ' '.join(string[i:i+length] for i in range(0,len(string),length))
    except :
        raise ValueError("Please enter either a string or a hex value of a byte string")

class aesMeth :
    '''
    The following class is a wrapper to the AES class by pyCrypto with AES encryption in mind
    An object of this class can encrypt the data given with different modes of encryption defined in the init
    '''
    def __init__(self,mode = "ECB",size = 128,ptsize = 80):
        '''
        The initialization function :
        Input Method :
        It has the following arguments given to it:
            i)   Mode of operation - ECB by default
            ii)  Key Size - 128, 192 or 256
            iii) Text Size - Has to be a multiple of 16

        This function gives the following attributes to an object :
        i)   Key - Randomly generated
        ii)  Plain Text - Randomly generated
        iii) An IV - Randomly generated
        iv)  A Counter - Randomly generated
        v)   The mode of operation :
                Four options available : ECB, CBC, CTR, OFB
        vi)  The Key size - Three options for AES Encryption (128,192,256)
        vii) Text Size - Hes to be a multiple of 16
        '''

        if mode != "ECB" and mode != "CBC" and mode != "OFB" and mode != "CTR" :
            raise ValueError("Please enter a valid mode : CBC, ECB, OFB or CTR" )
        else :
            self.mode = mode

        if size != 128 and size != 192 and size != 256 :
            raise ValueError("The key should be of either 128 , 192 or 256 bits")
        else :
            self.keySize = size

        if ptsize%16 != 0:
            raise ValueError("Please enter value as a multiple of 16 for the text size")
        else:
            self.textSize = ptsize

        # This generates an empty instance of the required fields
        self.key = b''
        self.iv = b''
        self.ctr = b''
        self.plaintext = b''

        #This calls the functions which gives an initial value to all the fields
        self.genKey()
        self.genPlainText()
        self.genCtr()
        self.genIV()

    # Generate functions
    # Four different functions used as calling them requires no
    # argument to be passed and hence can be done much faster
    def genKey(self):
        ''' Generates a random key of the given key size'''
        self.key=get_random_bytes(int(self.keySize/8))

    def genPlainText(self):
        ''' Generates a random key of the given plain text size'''
        self.plaintext=get_random_bytes(self.textSize)

    def genIV(self):
        ''' Generates a random IV'''
        self.iv = get_random_bytes(16)

    def genCtr(self):
        ''' Generates a random Control'''
        self.ctr = get_random_bytes(8)

    # A single generate function
    # Given as an option if not wanting to use four different functions

    '''
    def gen(self,prop):
        if prop == "Key" :
            self.key=get_random_bytes(int(self.keySize/8))
        elif prop == "Plain Text" :
            self.plaintext=get_random_bytes(self.textSize)
        elif prop == "iv" :
            self.iv = get_random_bytes(16)
        elif prop == "Ctr" :
            self.ctr = get_random_bytes(8)
    '''

    # Print functions
    # Four different functions used as calling them requires no
    # argument to be passed and hence can be done much faster
    def printKey(self):
        ''' Prints the key in hex form which is readable'''
        retStr = printReadable(self.key.hex(),8)
        return retStr

    def printPt(self):
        ''' Prints the plain text in hex form which is readable'''
        string = self.plaintext.hex()
        length = 8
        retStr = ""
        for j in range(int(self.textSize/16)):
            retStr += (' '.join(string[i:i+length] for i in range(32*j,32*(j+1),length))) + "\n"

        return retStr

    def printCtr(self):
        ''' Prints the control in hex form which is readable'''
        retStr = printReadable(self.ctr.hex(),8)
        return retStr

    def printIV(self):
        ''' Prints the IV in hex form which is readable'''
        retStr = printReadable(self.iv.hex(),8)
        return retStr

    # Single print function
    # Given as an option if not wanting to use four different functions
    '''
    def gen(self,prop):
        if prop == "Key" :
            print(printReadable(self.key.hex(),8))
        elif prop == "Plain Text" :
            string = self.plaintext.hex()
            length = 8
            for j in range(int(self.textSize/16)):
                print(' '.join(string[i:i+length] for i in range(32*j,32*(j+1),length)))
        elif prop == "Ctr" :
                print(printReadable(self.ctr.hex(),8))
        elif prop == "iv" :
             print(printReadable(self.iv.hex(),8))
    '''

    def encrypt(self):
        ''' This function encrypts the given plaintext'''
        if self.mode == "ECB" :
            # ECB is an inbuilt function in pycrypto, hence just applying it
            encObj = AES.new(self.key,AES.MODE_ECB)
            return encObj.encrypt(self.plaintext)

        elif self.mode == "CBC" :
            # CBC is an inbuilt function in pycrypto, hence just applying it
            encObj = AES.new(self.key,AES.MODE_CBC,self.iv)
            return encObj.encrypt(self.plaintext)

        elif self.mode == "OFB" :
            # OFB is not an inbuilt function, hence applying the algorithm to get the encryption
            # Encrypting each block of data seperately, so using ECB
            # for each one of them as ECB for one block of code is just AES applied to it
            obfObj = AES.new(self.key,AES.MODE_ECB)
            tempText = obfObj.encrypt(self.iv)

            # This stores all the encrypted iv by the equation C_i = f(C_(i-1))
            cArray = np.array([tempText])
            for i in range(int(self.textSize/16) - 1) :
                temptext = obfObj.encrypt(cArray[-1])
                cArray = np.append(cArray,temptext)

            # This array stores the XOR of the plain text and the encrypted iv
            # The data is converted to its hex form to be able to XOR it
            xorArr = np.array([])
            for i in range(int(self.textSize/16)):
                xorArr = np.append(xorArr,xor(cArray[i].hex(),self.plaintext[16*i:16*(i+1)].hex()))

            # This string combines all of the encrypted data in a single byte string
            encStr = b''
            for i in range(len(xorArr)):
                encStr+=bytes.fromhex(xorArr[i])
            return encStr

        elif self.mode == "CTR" :
            # CTR is not an inbuilt function, hence applying the algorithm to get the encryption
            # Encrypting each block of data seperately, so using ECB
            # for each one of them as ECB for one block of code is just AES applied to it
            ctrObj = AES.new(self.key,AES.MODE_ECB)

            # The ctrStr stores the concatenation of the Counter and number
            # Thus effectively being ctrStr[i] = ctr + i
            ctrStr = np.array([])
            for i in range(int(self.textSize/16)):
                appendStr = "00000000"
                # The number in ites entirety must be of length 8, hence mutating it so that it remains of length 8
                try :
                    appendStr = appendStr[:len(appendStr) - len(str(i))]
                except :
                    raise ValueError("Please enter text of smaller size")
                ctrStr = np.append(ctrStr,self.ctr + (appendStr + str(i)).encode('ascii'))

            # This string combines all of the encrypted data in a single byte string
            encArr = b''
            for i in range(int(self.textSize/16)):
                encArr += ctrObj.encrypt(ctrStr[i])
            return encArr

        else :
            # If none of the given methods are entered
            raise ValueError("Enter a proper method : ECB, CBC, OFB or CTR")
