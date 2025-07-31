let openBtn = document.querySelector(".nav-open");
let closeBtn = document.querySelector(".nav-close");
let navLaterral = document.querySelector(".nav-laterral");
let midContent = document.getElementsByClassName('middle-content')[0];

function openNav(){
    navLaterral.style.left ="0";
    openBtn.style.display ="none";
    midContent.style.padding = "0 0 0 70px";
}

function closeNav(){
    navLaterral.style.left ="-271px";
    openBtn.style.display ="block";
    midContent.style.left = "0px";
    midContent.style.padding = "0 0 0 0";
}

openBtn.addEventListener("click", openNav);
closeBtn.addEventListener("click",closeNav);