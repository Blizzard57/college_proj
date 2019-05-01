def isLeap(x):
    if x%4!=0 :
        return 0
    elif x%100!=0 :
        return 1
    elif x%400!=0 :
        return 0
    return 1
print(" The Year is 1900")
print(isLeap(1900))
