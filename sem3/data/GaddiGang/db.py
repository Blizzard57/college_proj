import subprocess as sp
import pymysql
import pymysql.cursors
from datetime import datetime, date

def addARestaurant():
    try:
        # Takes emplyee details as input
        row = {}
        print("Enter new restaurant's details: ")
        row["name"] = input("Name : ")
        row["Address"] = input("Address (Area): ")
        row["Surplus"] = int(input("Amount of Surplus: "))
        row["Collection"] = input("Collection Time : ").split(" ")
        
        timing = set(row["Collection"])
        mor = bool("Morning" in timing)
        after = bool("Evening" in timing)
        night = bool("Night" in timing)

        query = "INSERT INTO RESTAURANT(NAME,ADDRESS,AMOUNT_OF_SURPLUS) VALUES('%s', '%s', '%d')" %(row["name"], row["Address"], row["Surplus"])

        print(query)
        cur.execute(query)
        con.commit()

        query = "SELECT RESTAURANT_ID FROM RESTAURANT A WHERE A.NAME = '%s'" %row["name"]
        cur.execute(query)
        for i in cur:
            #print(i["ORGANISATION_ID"])
            query = "INSERT INTO TIME_OF_COLLECTION(RESTAURANT_ID, MORNING, EVENING, NIGHT) VALUES('%d', '%d', '%d', '%d')" %(i["RESTAURANT_ID"], mor, after, night)
            print(query)
            cur.execute(query)
            con.commit()

        print("Inserted Into Database")

    except Exception as e:
        con.rollback()
        print("Failed to insert into database")
        print (">>>>>>>>>>>>>", e)
        
    return

def hireVolunteer():
    try:
        # Takes emplyee details as input
        row = {}
        print("Enter new volunteer's details: ")
        row["name"] = input("Name : ")
        row["timeSlot"] = input("Time Slot : ")
        row["DOB"] = input("Date of Birth (YYYY-MM-DD): ")
        row["Address"] = input("Address (Area): ")

        #Calculating Age
        today = date.today()
        born = datetime.strptime(row["DOB"],"%Y-%m-%d")
        row["age"] = int(today.year - born.year - ((today.month, today.day) < (born.month, born.day)))

        query = "INSERT INTO VOLUNTEER(VOLUNTEER_NAME,TIME_SLOT,AGE, BIRTH_DATE, ADDRESS) VALUES('%s', '%s', '%d', '%s', '%s')" %(row["name"], row["timeSlot"], row["age"], row["DOB"], row["Address"])

        print(query)
        cur.execute(query)
        con.commit()

        print("Inserted Into Database")

    except Exception as e:
        con.rollback()
        print("Failed to insert into database")
        print (">>>>>>>>>>>>>", e)
        
    return

def addFIO():
    try:
        # Takes emplyee details as input
        row = {}
        print("Enter new organization's details: ")
        row["name"] = input("Name : ")
        row["feed"] = int(input("Number of People to Feed : "))
        row["veg"] = int(input("Number of Vegetarians : "))
        row["nveg"] = int(row["feed"] - row["veg"])
        row["Address"] = input("Address (Area): ")
        row["meal"] = int(input("Id of the Preffered meal: "))
        row["volunteer"] = int(input("Number of Volunteers : "))
        row["timing"] = input("Preffered time for Meal : ").split(" ")
        
        timing = set(row["timing"])
        mor = bool("Morning" in timing)
        after = bool("Evening" in timing)
        night = bool("Night" in timing)

        query = "INSERT INTO FOOD_INTENSIVE_ORGANISATION(NAME,NO_OF_PEOPLE_TO_FEED,NO_OF_VEGETARIANS, NO_OF_NON_VEGETARIANS, ADDRESS, MEAL_PREFERENCE, NO_OF_VOLUNTEERS) VALUES('%s', '%d', '%d', '%d', '%s', '%d', '%d')" %(row["name"], row["feed"], row["veg"], row["nveg"], row["Address"], row["meal"], row["volunteer"])
        print(query)
        cur.execute(query)
        con.commit()

        query = "SELECT ORGANISATION_ID FROM FOOD_INTENSIVE_ORGANISATION A WHERE A.NAME = '%s'" %row["name"]
        cur.execute(query)
        for i in cur:
            #print(i["ORGANISATION_ID"])
            query = "INSERT INTO MEAL_TIMINGS(ORGANISATION_ID, MORNING, EVENING, NIGHT) VALUES('%d', '%d', '%d', '%d')" %(i["ORGANISATION_ID"], mor, after, night)
            print(query)
            cur.execute(query)
            con.commit()

        print("Inserted Into Database")

    except Exception as e:
        con.rollback()
        print("Failed to insert into database")
        print (">>>>>>>>>>>>>", e)
        
    return

def meal():
    try:
        # Takes emplyee details as input
        row = {}
        print("Enter new food's details: ")
        row["state"] = input("State of the food (Solid,Liquid) : ")
        row["expire"] = input("Expiration Date (YYYY-MM-DD) : ")
        row["name"] = input("Name of the Meal : ")
        row["pref"] = int(input("Preference (1 --> Non Veg 0 --> Veg): "))
        row["size"] = int(input("Serving size : "))
        row["making"] = input("Time of Making (HH:MM:SS) : ")
        row["resid"] = int(input("Restaurant Id : "))

        query = "INSERT INTO FOOD(STATE_OF_FOOD, EXPIRATION_DATE, MEAL_NAME, PREFERENCE, SERVING_SIZE, TIME_OF_MAKING, RESTAURANT_ID) VALUES('%s', '%s', '%s', '%d', '%s', '%s', '%d')" %(row["state"], row["expire"], row["name"], row["pref"], row["size"], row["making"], row["resid"])

        print(query)
        cur.execute(query)
        con.commit()

        print("Inserted Into Database")

    except Exception as e:
        con.rollback()
        print("Failed to insert into database")
        print (">>>>>>>>>>>>>", e)
        
    return

def addDonation():
    try:
        # Takes emplyee details as input
        row = {}
        print("Enter new food's details: ")
        row["benId"] = input("FIO to Donate to : ")
        row["amount"] = int(input("Donation Amount : "))
        
        query = "INSERT INTO FOOD(BENEFACTOR_ID, DONATION_ID) VALUES('%s', '%d')" %(row["benId"], row["amount"])

        print(query)
        cur.execute(query)
        con.commit()

        print("Inserted Into Database")

    except Exception as e:
        con.rollback()
        print("Failed to insert into database")
        print (">>>>>>>>>>>>>", e)
        
    return

def printTable(myDict, colList=None):
   if not colList: colList = list(myDict[0].keys() if myDict else [])
   myList = [colList] # 1st row = header
   for item in myDict: myList.append([str(item[col] if item[col] is not None else '') for col in colList])
   colSize = [max(map(len,col)) for col in zip(*myList)]
   formatStr = ' | '.join(["{{:<{}}}".format(i) for i in colSize])
   myList.insert(1, ['-' * i for i in colSize]) # Seperating line
   for item in myList: print(formatStr.format(*item))

def display(tablename):
    try:
        query = "SELECT * FROM %s" %(tablename)
        cur.execute(query)
        print("Executed the Query")
        for i in cur:
            print(i)
        #print(dict)

    except Exception as e:
        con.rollback()
        print("Failed to insert into database")
        print (">>>>>>>>>>>>>", e)
        
    return

def removal(tablename):
   try:
    #tablename=input("Enter table name for deletion: ")
    if(tablename == 'RESTAURANT'):
        field='RESTAURANT_ID'
    elif(tablename == 'FOOD_INTENSIVE_ORGANISATION'):
        field='ORGANISATION_ID'
    elif(tablename == 'FOOD'):
        field='MEAL_ID'
    elif(tablename == 'DONATION'):
        field='DONATION_ID'
    elif(tablename == 'VOLUNTEER'):
        field='VOLUNTEER_ID'
    else:
        #incorrect table name,throw the error
        raise Exception('incorrect tablename given')
    
    display(tablename)
    id=int(input("Enter the private key id of the row to delete: "))
    if (field=='ORGANISATION_ID'):
        query="DELETE FROM %s WHERE %s = %d;"%("MEAL_TIMINGS",field,id)
        #print(query)
        cur.execute(query)
        con.commit()
    elif (field=='RESTAURANT_ID'):
        query="DELETE FROM %s WHERE %s = %d;"%("TIME_OF_COLLECTION",field,id)
        #print(query)
        cur.execute(query)
        con.commit()
    query="DELETE FROM %s WHERE %s = %d;"%(tablename,field,id)
    #print(query)
    cur.execute(query)
    con.commit()
    print("Deletion of field completed")

   except Exception as e:
        con.rollback()
        print("Failed to delete row in database")
        print (">>>>>>>>>>>>>", e)

   return

def updater(tablename):
   try:
    #tablename= input("Enter table name for updation: ")
    display(tablename)
    fields= list(input("Enter the list of fields to update: ").split(' '))
    newvals=list(input("Enter the list of new values for the fields: ").split(' '))
    clause_c=list(input("Enter the list of fields for value conditioning: ").split(' '))
    clause_v=list(input("Enter the list of values for the field to condition on: ").split(' '))
    query="UPDATE %s SET "%(tablename)

    for i, (f,n) in enumerate(zip(fields,newvals)):
        #add comma to the end if this is not the start of the loop
        if i != 0:
            query=query+", "

        query=query+f+" = '"+n+"' "

    query=query + "WHERE " #add the where

    for i,(c,v) in enumerate(zip(clause_c,clause_v)): #add the conditions
        #add AND to the end if this is not the start of the loop
        if i!=0:
            query=query+"AND "

        query=query+c+" =   '"+v+"' "

    query=query+";"

    #print(query)
    cur.execute(query)
    con.commit()
    print("Updation of field completed")

   except Exception as e:
        con.rollback()
        print("Failed to update fields in database")
        print (">>>>>>>>>>>>>", e)

   return
   
def report1():
    try:
        query = "SELECT RES.NAME, COUNT(*) PREFERENCE_COUNT FROM FOOD_INTENSIVE_ORGANISATION FIO, RESTAURANT RES WHERE FIO.MEAL_PREFERENCE=RES.RESTAURANT_ID GROUP BY FIO.MEAL_PREFERENCE ORDER BY COUNT(MEAL_PREFERENCE) DESC;"
        cur.execute(query)
        print("Executed the Query")
        for i in cur:
            print(i)
        #print(dict)

    except Exception as e:
        con.rollback()
        print("Failed to insert into database")
        print (">>>>>>>>>>>>>", e)
        
    return

def report2():
    try:
        query = "SELECT RES.NAME, RES.AMOUNT_OF_SURPLUS, RES.AMOUNT_OF_SURPLUS-DATA.FOOD_USED DELTA_OF_FOOD  FROM (SELECT RES.RESTAURANT_ID ,SUM(FIO.NO_OF_PEOPLE_TO_FEED) FOOD_USED FROM FOOD_INTENSIVE_ORGANISATION FIO, RESTAURANT RES WHERE FIO.MEAL_PREFERENCE=RES.RESTAURANT_ID GROUP BY FIO.MEAL_PREFERENCE) DATA, RESTAURANT RES WHERE DATA.RESTAURANT_ID=RES.RESTAURANT_ID;"
        cur.execute(query)
        print("Executed the Query")
        for i in cur:
            print(i)
        #print(dict)

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
        addARestaurant()
    elif(ch==2):
        hireVolunteer()
    elif(ch==3):
        addFIO()
    elif(ch==4):
        meal()
    elif(ch==5):
        addDonation()
    elif(ch==6):
        removal('RESTAURANT')
    elif(ch==7):
        removal('VOLUNTEER')
    elif(ch==8):
        removal('FOOD_INTENSIVE_ORGANISATION')
    elif(ch==9):
        removal('FOOD')
    elif(ch==10):
        removal('DONATION')
    elif(ch==11):
        updater('RESTAURANT')
    elif(ch==12):
        updater('VOLUNTEER')
    elif(ch==13):
        updater('FOOD_INTENSIVE_ORGANISATION')
    elif(ch==14):
        updater('FOOD')
    elif(ch==15):
        updater('DONATION')
    elif(ch==16):
        report1()
    elif(ch==17):
        report2()
        
    else:
        print("Error: Invalid Option")

# Global
while(1):
    tmp = sp.call('clear',shell=True)
    print("CRTL + D to Exit")
    username = input("Username: ")
    password = input("Password: ")  

    try:
        con = pymysql.connect(host='localhost',
                user=username,
                password=password,
                db='company',
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
                print("1. Add a new restaurant")
                print("2. Hire a new volunteer")
                print("3. Add a new FIO")
                print("4. Add a meal")
                print("5. Add a donation")
                print("6. Remove a restaurant")
                print("7. Fire a volunteer")
                print("8. Remove an FIO")
                print("9. Remove a meal")
                print("10. Remove a donation")
                print("11. Update a restaurant")
                print("12. Update volunteer details")
                print("13. Update a FIO")
                print("14. Update a meal")
                print("15. Update a donation")
                print("16. Report on stats for improvement")
                print("17. Efficiency report")
                print("18. Logout")
                ch = int(input("Enter choice> "))
                tmp = sp.call('clear',shell=True)
                if ch==18:
                    break
                else:
                    dispatch(ch)
                    tmp = input("Enter any key to CONTINUE>")


    except:
        tmp = sp.call('clear',shell=True)
        print("Connection Refused: Either username or password is incorrect or user doesn't have access to database")
        tmp = input("Enter any key to CONTINUE>")
    
   