git pull origin master
git add .
if [ $1 == ""]
then
    git commit -m "Small Changes"
else
    git commit -m $1
fi
git push origin master
