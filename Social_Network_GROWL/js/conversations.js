function selectDiscussion(number_friend) {
    let actualselectedFriend = document.getElementsByClassName("selected_friends");
    let selectedFriend = document.getElementById('user'+number_friend);
	let nameSelectedFriend = document.getElementsByClassName('userName'+number_friend)[0].innerHTML;
    changeConversation(nameSelectedFriend);
    actualselectedFriend[0].classList.toggle("selected_friends");
    selectedFriend.classList.toggle("selected_friends");
}

function getfile(){
    document.getElementById('hiddenfile').click();
}

function previewPicture(e){
    var maxSize = 500000;
    var error = document.getElementById("error-size-image");
    error.innerHTML = "";
    error.style.display = "none";
    if(e.files[0].size>maxSize){
        error.innerHTML = 'The file is too large and was not added. Maximum size: 500 KB.';
        error.style.color = 'red';
        error.style.display = "";
        e.files = null;
        return;
    }
    var boxmessages =  document.getElementsByClassName("box_message")[0];
    var textzone = document.getElementsByClassName("send_menu_message")[0];
    if(!document.getElementById("new-post-images")){
        var divImages = document.createElement("div");
        divImages.id= "new-post-images";
    } else {
        var divImages = document.getElementById("new-post-images");
        divImages.innerHTML ="";
    }
    
        Array.from(e.files).forEach(element => {

            if (element) {
                var oImg = document.createElement("img");
                oImg.setAttribute('src', URL.createObjectURL(element));
                oImg.setAttribute('accept', 'image/jpeg, image/jpg, image/png');
                oImg.setAttribute('alt', 'na');
                oImg.setAttribute('class', 'post-input-images');

                // Créer un bouton de suppression pour cette image
                var deleteBtn = document.createElement("button");
                deleteBtn.innerHTML = "X";
                deleteBtn.addEventListener("click", function() {
                    document.getElementById("hiddenfile").value = "";
                    divImages.removeChild(oImg);
                    divImages.removeChild(deleteBtn);
                    boxmessages.removeChild(divImages);
                });
                
                fetch(oImg.src) .then((res) => res.blob()) .then((blob) => {
                    // Read the Blob as DataURL using the FileReader API
                    const reader = new FileReader();
                    reader.onloadend = () => {
                        oImg.src = reader.result;
                       
                    };
                    reader.readAsDataURL(blob);
                });
                
                divImages.appendChild(oImg);
                divImages.appendChild(deleteBtn);
                boxmessages.appendChild(divImages);
                boxmessages.insertBefore(textzone, divImages.nextSibling)
            }
        })
}


function sendMessage() {
	let now = new Date();
	var tableauMois = new Array('janvier','février','mars','mai','juillet','septembre','novembre','décembre');
    let message = [];
    //On récupère le message qui est écrit dans le champ message
    if(!document.getElementsByClassName("post-input-images").length == '0'){
        var img = document.getElementsByClassName("post-input-images")[0].src;
        message[0] = img.split("base64,")[1];
        message[1] = img.split(";")[0].split("data:")[1];
    } else{
        message[0] = document.getElementById("actual_writen_message").value;
        if(message == 0){
            return;
        }
        message[1]=null;
    }
    //On récupère la div conversation pour y ajouter la nouvelle bulle message
    let conversation = document.getElementById("conv");
	
    //On crée la nouvelle bulle avec la bonne classe
    let new_bulle = document.createElement("div");
    new_bulle.className = "bulle my_bulle_message";
    var speaker = document.createElement('span');
    speaker.className = 'message_info';
    speaker.innerHTML = "Me";
    var content;
	
    if(message[1] != null){ // cas ou on envoie une image
        content = document.createElement("img");
        content.src = "data:"+message[1]+";base64,"+message[0];
        content.id = "image_message";
        content.className = "text_message";
        var delete_preview_image = document.getElementById("new-post-images");
        delete_preview_image.innerHTML = "";
        delete_preview_image.remove();

    }else { // cas ou on envoie du texte
        //Cette bulle doit contenir le contenu du message et les informations annexes avec les bonnes classes css
        content = document.createElement("span");
        content.textContent = message[0];
        content.className = "text_message";
    }
	
    let info_message = document.createElement("span");
    info_message.className = "message_info date_message";
    var minutes = now.getMinutes()
    if(minutes<10)
    minutes = "0" + minutes;
    date = now.getHours() + ":" + minutes + " - " + ('0'+now.getDate()).slice(-2) + " " + tableauMois[now.getMonth()];
	info_message.textContent = date;
    //Pour la mise en forme, il faut une div vide qui centre à droite la bulle
    let empty_div = document.createElement("div");
    empty_div.className = "my-empty-conv"
    //Le tout doit être mit dans une div qui prend 100% de la taille du champ conversation
    let mother_div = document.createElement("div");

    new_bulle.append(speaker);
    new_bulle.append(content);
    new_bulle.append(info_message);

    mother_div.append(empty_div);
    mother_div.append(new_bulle);

    conversation.prepend(mother_div);
    document.getElementById("actual_writen_message").value = "";
    sendMessageIntoDB(message[0],message[1]);
    document.getElementById('current_speaking_date_last_message').innerHTML = date;
}
