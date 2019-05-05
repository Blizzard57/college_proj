from flask import Flask, render_template, jsonify, request #Basic requirement for the python script to work as a flask App
from aesLib import * #This is where the algorithm required for all the calculations is calculated
from Crypto.Cipher import AES #For local encryptions
from flask_sqlalchemy import SQLAlchemy #For the database

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///Quiz.db'
## Having a default object when no method is selected in the Experiment
aes_obj = aesMeth()
key = 128

#Making a database to store all the answers of the Quiz
db = SQLAlchemy(app)
class students(db.Model):
    id = db.Column('student_id', db.Integer, primary_key = True)
    A1 = db.Column(db.String(1))
    A2 = db.Column(db.String(1))
    A3 = db.Column(db.String(1))
    A4 = db.Column(db.String(100))
    A5 = db.Column(db.String(100))
    A6 = db.Column(db.String(100))
    A7 = db.Column(db.String(100))

    def __init__(self,A1,A2,A3,A4,A5,A6,A7):
        self.A1 = A1
        self.A2 = A2
        self.A3 = A3
        self.A4 = A4
        self.A5 = A5
        self.A6 = A6
        self.A7 = A7

db.create_all()

#Rendering of pages for linking to work
@app.route("/")
def introduction():
    return render_template('Introduction.html', topic ='Introduction')

@app.route("/experiment")
def experiment():
    return render_template('Experiment.html', topic ='Experiment')

@app.route("/manual")
def manual():
    return render_template('Manual.html', topic ='Manual')

@app.route("/theory")
def theory():
    return render_template('Theory.html', topic ='Theory')

@app.route("/objective")
def objective():
    return render_template('Objective.html', topic ='Objective')

@app.route("/quiz")
def quiz():
    return render_template('Quiz.html', topic ='Quiz')

@app.route("/feedback")
def feedback():
    return render_template('Feedback.html', topic ='Feedback')

@app.route("/procedure")
def procedure():
    return render_template('Procedure.html', topic ='Procedure')

@app.route("/further")
def further():
    return render_template('Further.html', topic ='Further Readings')

#This request allows the object aes_obj to change its mode of operation
@app.route("/experiment/selectMode", methods=['POST'])
def selectMode():
    data = request.get_json()
    if data == 'ecb':
        aes_obj.mode = 'ECB'
    elif data == 'cbc':
        aes_obj.mode = 'CBC'
    elif data == 'ofb':
        aes_obj.mode = 'OFB'
    elif data == 'ctr':
        aes_obj.mode = 'CTR'

@app.route("/experiment/selectKey", methods=['POST'])
def selectKey():
    data = request.get_json()
    if data == "128":
        aes_obj.keySize = 128
        key = 128
    elif data == '192':
        aes_obj.keySize = 192
        key = 192
    elif data == '256':
        aes_obj.keySize = 256
        key = 256

@app.route("/experiment/nextplaintext", methods=['GET'])
def nextplaintext():
    #Generates a new plaintext before storing it 
    aes_obj.genPlainText()

    info = {
                "plainarea": aes_obj.printPt()
    }

    return jsonify(info)


@app.route("/experiment/nextkey", methods=['GET'])
def nextkey():
        aes_obj.genKey()

        info = {
            "key": aes_obj.printKey()
        }

        return jsonify(info)

@app.route("/experiment/nextIV", methods=['GET'])
def nextIV():
        aes_obj.genIV()

        info = {
            "iv": aes_obj.printIV()
        }

        return jsonify(info)

@app.route("/experiment/nextctr", methods=['GET'])
def nextctr():
    aes_obj.genCtr()

    info = {
        "ctr": aes_obj.printCtr()
    }

    return jsonify(info)

@app.route("/experiment/answer", methods=['GET','POST'])
def answer():
    data = request.get_json()
    one = str(data.get('one'))
    two = str(data.get('two'))

    #If the text has some spaces it wont be taken into consideration
    oneEdit = one.split(" ")
    one = ""
    for i in oneEdit:
        one+=i
    twoEdit = two.split(" ")
    two = ""
    for i in twoEdit:
        two+=i

    xor_value = printReadable(xor(one,two),8)
    print(xor_value)
    return jsonify(xor_value)

@app.route("/experiment/encrypt", methods=['GET','POST'])
def encrypt():
    data = request.get_json()
    one = str(data.get('one'))
    two = str(data.get('two'))

    #If the text has some spaces it wont be taken into consideration
    oneEdit = one.split(" ")
    one = ""
    for i in oneEdit:
        one+=i
    twoEdit = two.split(" ")
    two = ""
    for i in twoEdit:
        two+=i

    aes_new = AES.new(bytes.fromhex(one),AES.MODE_ECB)
    enc = aes_new.encrypt(bytes.fromhex(two))
    A = printReadable(enc.hex(),8)
    return jsonify(A)

@app.route("/experiment/decrypt", methods=['GET','POST'])
def decrypt():
    data = request.get_json()
    one = str(data.get('one'))
    two = str(data.get('two'))

    #If the text has some spaces it wont be taken into consideration
    oneEdit = one.split(" ")
    one = ""
    for i in oneEdit:
        one+=i
    twoEdit = two.split(" ")
    two = ""
    for i in twoEdit:
        two+=i

    aes_new = AES.new(bytes.fromhex(one),AES.MODE_ECB)
    dec = aes_new.decrypt(bytes.fromhex(two))
    A = printReadable(dec.hex(),8)
    return jsonify(A)

@app.route("/experiment/check", methods=['GET','POST'])
def checkAns():
    one = request.get_json()

    #If the text has some spaces it wont be taken into consideration
    oneEdit = one.split(" ")
    one = ""
    for i in oneEdit:
        one+=i

    if one == aes_obj.encrypt().hex():
        ret = "True"
    else:
        ret = "False"
    return jsonify(ret)

@app.route("/experiment/showans", methods=['GET'])
def showans():

    info = {
        "ans": printReadable(aes_obj.encrypt().hex(),8)
    }

    return jsonify(info)

@app.route('/quiz', methods = ['GET', 'POST'])
def new():
   if request.method == 'POST':
         student = students(request.form['A1'], request.form['A2'],
            request.form['A3'], request.form['A4'] , request.form['A5'], request.form['A6'], request.form['A7'])
         print("Answer for first is " + request.form['A1'])
         db.session.add(student)
         db.session.commit()

   return render_template('Data.html',students = students.query.all())

if __name__ == '__main__':
    app.run(debug = True)
