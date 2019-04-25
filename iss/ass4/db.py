from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:////tmp/try.db'
db = SQLAlchemy(app)

class Quiz(db.Model):
    number = db.Column(db.Integer, primary_key=True)
    answer = db.Column(db.Integer)

    def __init__(self, answer):
        self.answer = answer
        self.email = email

    def __repr__(self):
        return '<Question %r>' % self.answer

@app.route("/quiz/create", methods=["POST"])
def addQuiz():

    answer=request.form['answer']
    db.create_all()
    new_quiz=Quiz(answer)
    db.session.add(new_quiz)
    db.session.commit()

    temp ={}
    temp['status']=(type(new_quiz)==Quiz)
    return jsonify(temp)

@app.route("/quiz/", methods=["GET"])
def QuizFetch():
    db.create_all()
    allQuiz=Quiz.query.all()
    print('here', allStudents)
    a = {'Quiz':[]}
    for quiz in allQuiz:
        temp = {}
        temp['answer'] = quiz.answer
        temp['number'] = quiz.number
        a['Quiz'].append(temp)

    return jsonify(a)

@app.route("/quiz/delete", methods=["POST"])
def quizDelete():
    db.create_all()
    rollno=request.form['rollno']
    stud = Student.query.filter_by(rollnumber=rollno).first()
    if(stud):
        db.session.delete(stud)
        db.session.commit()
        temp = {}
        temp['status'] = True
        return jsonify(temp)

    else:
        temp = {}
        temp['status'] = False
        return jsonify(temp)
