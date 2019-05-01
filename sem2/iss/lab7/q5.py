import sys
inputFile = sys.argv[1]
outputFile = sys.argv[2]
stream_input = open(inputFile, 'r')
stream_output = open(outputFile, 'w')
original = stream_input.read()
original=original[1:-1]
original=original[:-1]
original=original.lower()
noQuotations = ''.join(original.split('"'))
noMultipleSpaceAndSplChar = ' '.join(noQuotations.split())
noCommas = ''.join(noMultipleSpaceAndSplChar.split(','))
noPeriods = ''.join(noCommas.split('.'))
noColon = ''.join(noPeriods.split(':'))
noSemiColon = ''.join(noColon.split(';'))
noExclamation = ''.join(noSemiColon.split('!'))
noQuestionMarks = ''.join(noExclamation.split('?'))
noQuotations = ''.join(noQuestionMarks.split('"'))
noLParentheses = ''.join(noQuotations.split('('))
noParentheses = ''.join(noLParentheses.split(')'))
finalList = (noParentheses.split())
storeDictionary = {}
for word in finalList:
    if word in storeDictionary:
        storeDictionary[word] += 1
    else:
        storeDictionary[word] = 1
for word in finalList:
    print(f'{word}: {storeDictionary[word]}', file=stream_output)
stream_input.close()
stream_output.close()
