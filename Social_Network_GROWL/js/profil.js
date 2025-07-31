var box1 = document.getElementById("box1");
var box2 = document.getElementById("box2");
var box3 = document.getElementById("box3");

var content1 = document.getElementById("content1");
var content2 = document.getElementById("content2");
var content3 = document.getElementById("content3");


box1.addEventListener("click", function() {
  content1.style.display = "block";
  content1.style.backgroundColor = "";
  content2.style.display = "none";
  content3.style.display = "none";
  box1.classList.remove("btn-unactive-profil");
  box1.classList.add("btn-active-profil");
  box2.classList.remove("btn-active-profil");
  box2.classList.add("btn-unactive-profil");
  box3.classList.remove("btn-active-profil");
  box3.classList.add("btn-unactive-profil");
});

box2.addEventListener("click", function() {
  content1.style.display = "none";
  content2.style.display = "block";
  content3.style.display = "none";
  box1.classList.remove("btn-active-profil");
  box1.classList.add("btn-unactive-profil");
  box2.classList.add("btn-active-profil");
  box2.classList.remove("btn-unactive-profil");
  box3.classList.remove("btn-active-profil");
  box3.classList.add("btn-unactive-profil");
});

box3.addEventListener("click", function() {
  content1.style.display = "none";
  content2.style.display = "none";
  content3.style.display = "block";
  box1.classList.remove("btn-active-profil");
  box1.classList.add("btn-unactive-profil");
  box2.classList.remove("btn-active-profil");
  box2.classList.add("btn-unactive-profil");
  box3.classList.add("btn-active-profil");
  box3.classList.remove("btn-unactive-profil");
});

function submitFormConvLinkProfil() {
    document.getElementById("form-conversation-link-profil").submit();
}

function submitFormSendFriendReq() {
  document.getElementById("form-send-f-req").submit();
}