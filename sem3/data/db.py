import subprocess as sp
import pymysql
import pymysql.cursors

def fireAnEmployee():
    """
    Function to fire an employee
    """
    print("Not implemented")

def promoteEmployee():
    """
    Function performs one of three jobs
    1. Increases salary
    2. Makes employee a supervisor
    3. Makes employee a manager
    """
    print("Not implemented")


def employeeStatistics():
    """
    Function prints a report containing 
    the number of hours per week the employee works,
    hourly pay, projects employee works on and so on
    """
    print("Not implemented")


def hireAnEmployee():
    try:
        # Takes emplyee details as input
        row = {}
        print("Enter new employee's details: ")
        name = (input("Name (Fname Minit Lname): ")).split(' ')
        row["Fname"] = name[0]
        row["Minit"] = name[1]
        row["Lname"] = name[2]
        row["Ssn"] = input("SSN: ")
        row["Bdate"] = input("Birth Date (YYYY-MM-DD): ")
        row["Address"] = input("Address: ")
        row["Sex"] = input("Sex: ")
        row["Salary"] = float(input("Salary: "))
        row["Dno"] = int(input("Dno: "))

        """
        In addition to taking input, you are required to handle domain errors as well
        For example: the SSN should be only 9 characters long
        Sex should be only M or F
        If you choose to take Super_SSN, you need to make sure the foreign key constraint is satisfied
        HINT: Instead of handling all these errors yourself, you can make use of except clause to print the error returned to you by MySQL
        """

        query = "INSERT INTO EMPLOYEE(Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Dno) VALUES('%s', '%c', '%s', '%s', '%s', '%s', '%c', %f, %d)" %(row["Fname"], row["Minit"], row["Lname"], row["Ssn"], row["Bdate"], row["Address"], row["Sex"], row["Salary"], row["Dno"])

        print(query)
        cur.execute(query)
        con.commit()

        print("Inserted Into Database")

    except Exception as e:
        con.rollback()
        print("Failed to insert into database")
        print (">>>>>>>>>>>>>", e)
        
    return

def dispatch(ch):
    """
    Function that maps helper functions to option entered
    """

    if(ch==1): 
        hireAnEmployee()
    elif(ch==2):
        fireAnEmployee()
    elif(ch==3):
        promoteEmployee()
    elif(ch==4):
        employeeStatistics()
    else:
        print("Error: Invalid Option")

# Global
while(1):
    tmp = sp.call('clear',shell=True)
    username = input("Username: ")
    password = input("Password: ")

    try:
        con = pymysql.connect(host='localhost',
                user=username,
                password=password,
                db='COMPANY',
                cursorclass=pymysql.cursors.DictCursor)
        tmp = sp.call('clear',shell=True)

        if(con.open):
            print("Connected")
        else:
            print("Failed to connect")
        tmp = input("Enter any key to CONTINUE>")

        with con:
            cur = con.cursor()
            while(1):
                tmp = sp.call('clear',shell=True)
                print("1. Hire a new employee")
                print("2. Fire an employee")
                print("3. Promote an employee")
                print("4. Employee Statistics")
                print("5. Logout")
                ch = int(input("Enter choice> "))
                tmp = sp.call('clear',shell=True)
                if ch==5:
                    break
                else:
                    dispatch(ch)
                    tmp = input("Enter any key to CONTINUE>")


    except:
        tmp = sp.call('clear',shell=True)
        print("Connection Refused: Either username or password is incorrect or user doesn't have access to database")
        tmp = input("Enter any key to CONTINUE>")
    
   