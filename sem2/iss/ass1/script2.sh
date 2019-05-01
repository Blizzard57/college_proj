cp file1.csv cash.csv
cp file2.csv casy.csv
cat cash.csv >> casy.csv
mv casy.csv target_file.csv
rm cash.csv
echo "Age,workclass,fnlwgt,education,education-num,marital-status,occupation,relationship,race,sex,capital-gain,capital-loss,hours-per-week,native-country,class" > header.csv
cat target_file.csv >> header.csv
rm target_file.csv
mv header.csv target_file.csv
sed -i 's/?/2018113003/g' target_file.csv
