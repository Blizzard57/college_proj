function isPrime(p){
var flag=0
for (i=2; i<p; i++){
if(p%i==0){
flag=1;
break;
}
if(flag==0){
return 0;}
else{
return 1
}

function main(){
var i=1;
var j=1;
var k=1;
while(i<1500){
if(isPrime(i)==0){
console.log(i)
}
k=i;
i=i+j;
j=k;
}
}
main();
