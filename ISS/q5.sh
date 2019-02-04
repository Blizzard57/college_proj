touch 2018113003.txt
find > var.txt
find -printf %Ac > var2.txt
cat var2.txt | sed 's/IST/IST\n/g' > asw.txt
paste asw.txt var.txt > temp4.txt
#This is a comment
apropos lo | grep "^lo" >> 2018113003.txt
awk 'length > max_length { max_length = length; longest_line = $0 } END { print longest_line }' ./2018113003.txt
cat 2018113003.txt | wc -l
cat temp4.txt | sed 's/\t/ /g' > backup
cat 2018113003.txt | sed 's/function/method/g'
rm var.txt var2.txt asw.txt temp4.txt
