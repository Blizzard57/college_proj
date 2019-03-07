window.onscroll = function() {Function()};
var navbar = document.getElementById("topnav");
var sticky = navbar.offsetTop;

function Function() {
  if (window.pageYOffset >= sticky) {
    navbar.classList.add("sticky")
  } else {
    navbar.classList.remove("sticky");
  }
}

function highlight(x){
    x.style.color = "#f2f2f2";
}

function nonhigh(x){
    x.style.color = "dimgrey";
}

function myFunction() {
  var x = document.getElementById("myTopnav");
  if (x.className === "topnav") {
    x.className += " responsive";
  } else {
    x.className = "topnav";
  }
}
