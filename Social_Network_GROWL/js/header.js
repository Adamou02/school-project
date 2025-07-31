var settingMenu = document.querySelector(".setting-menu");
var closeFriends = document.querySelector(".close-friends");

function settingMenuOpen(){
    
    if (closeFriends == null) {
        settingMenu.classList.toggle("setting-menu-height");
    }

    if(settingMenu.id == "close"){
        closeFriends.style.transitionDelay = "0s";
        closeFriends.style.margin = "280px 0 0 0 ";
        settingMenu.id="open";
    }else{
        closeFriends.style.transitionDelay = "0.18s";
        closeFriends.style.margin = "0 0 0 0 ";
        settingMenu.id="close";
    }
    settingMenu.classList.toggle("setting-menu-height");
}


const searchInput = document.getElementById('search-input');
const suggestionsList = document.querySelector('.suggestion');


searchInput.addEventListener('input', function() {
  suggestionsList.style.display = 'block';
  suggestionsList.innerHTML = "";
  if(searchInput.value != "") {
    searchProfil(searchInput.value);
    displayResultKeyWord();
  }
});


function displayResult(nbrUser, tabUser){

   for(var i = 0 ; i < nbrUser;i++){
    
        var div = document.createElement("div");
        div.setAttribute('class','divSuggestion')
        div.setAttribute('onclick','submitFormProfilSerarch('+i+')');

        var form = document.createElement("form");
        form.setAttribute('id','profilSearch'+i);
        form.setAttribute('method','GET');
        form.setAttribute('action','./profil.php');

        var input = document.createElement("input");
        input.setAttribute('type','hidden');
        input.setAttribute('name','user');
        input.setAttribute('id','userSearch'+i);
        input.value = tabUser[i][1];

        form.appendChild(input);

        var img = document.createElement("img");
        img.setAttribute('src',tabUser[i][2]);

        var op = document.createElement("p");
        op.innerHTML = tabUser[i][1];
        div.appendChild(form);
        div.appendChild(img);
        div.appendChild(op);
        suggestionsList.appendChild(div);
   }
}

function displayResultKeyWord(){

       var div = document.createElement("div");
       div.setAttribute('class','divSuggestion')
       div.setAttribute('onclick','submitFormKeyWordsSerarch()');

       var form = document.createElement("form");
       form.setAttribute('id','keyWordsSearch');
       form.setAttribute('method','GET');
       form.setAttribute('action','./index.php');

       var input = document.createElement("input");
       input.setAttribute('type','hidden');
       input.setAttribute('name','searchBar');
       var i = document.getElementById('search-input').value;
       input.value = i;

       form.appendChild(input);

       var op = document.createElement("p");
       op.innerHTML = "#"+i;
       div.appendChild(form);
       div.appendChild(op);
       suggestionsList.appendChild(div);

}

function submitFormProfilSerarch(form_no){
    document.getElementById("profilSearch" + form_no).submit();
}

function submitFormKeyWordsSerarch(){
  document.getElementById("keyWordsSearch").submit();
}

document.addEventListener('click', function(event) {
    if ((event.target !== searchInput && event.target !== suggestionsList) || searchInput.value == "") {
      suggestionsList.style.display = 'none';
    }
  });