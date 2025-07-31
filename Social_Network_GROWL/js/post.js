
//Regarde si la box commentaire a déjà été crée, et appelle les fonctions selon ce test
function CommentSectionCall(menu_id) {
    menu_id = menu_id.replace('CommentSection', '');
    let existCommentSection = document.getElementById("close" + menu_id);
    if(existCommentSection == null){
        CommentSectionCreate(menu_id);
    }
    else{
        CommentSectionOpen(menu_id);
    }
}

//Crée la bulle commentaire avec Ajax lors du premier clique sur la commentSection. Pour les clics suivants, ce sera la fonction CommentSectionOpen qui ouvrira/fermera la section commentaire
function CommentSectionCreate(menu_id) {
    createComments(menu_id);
}

//Cherche le deuxième enfant de la div qui contient l'image commentaire. Le deuxième enfant est la div 'bulle commentaire' qui apparait et disparait quand on clique sur la div mère
function CommentSectionOpen(menu_id){
    selected_comment_menu = document.getElementById("close" + menu_id);
    selected_comment_menu.classList.toggle("comment-menu-height");
}


//Fonction qui envoie le commentaire écrit dans le champ input texte
function sendComment(comment_id, content, user_id, post_id, username, PP) {
	let now = new Date();

    //On recupere la page commentaire pour scroll vers le bas quand l'utilisateur poste un commentaire 
    let comment_section = document.getElementById("close" + post_id);

    //On récupère la div conversation pour y ajouter la nouvelle bulle message
    let comment_list = document.getElementById(post_id + "_comments_list");

    //On crée un container de bulle nécessaire pour le bon affichage des elements flex dans un flex grand-parent
    let shadow_bulle_container = document.createElement("div")

    //On crée la nouvelle bulle avec la bonne classe
    let new_bulle = document.createElement("div");
    new_bulle.className = "comment-pseudo-text";

    //Cette bulle doit contenir le contenu du message et les informations annexes avec les bonnes classes css
    let username_message = document.createElement("a")
    username_message.textContent = username;
    username_message.className = "comment-pseudo"

    let text_message = document.createElement("p");
    text_message.textContent = content;
    text_message.className = "comment-text";

    //On crée la div qui va contenir les infos liés au commentaire
    let info_message = document.createElement("div");
    info_message.className = "comment-reaction";

    //On crée la balise qui contient la date du message et le bouton Answer
    let date_message = document.createElement("p")
    date_message.className = "comment-info"
	date_message.textContent = now.getFullYear() + "-" + ('0' + (now.getMonth() + 1)).slice(-2) + "-" + ('0'+now.getDate()).slice(-2) + " " + now.getHours() + ":" + now.getMinutes() + ":" + now.getSeconds();
    
    let repondre_btn = document.createElement("p")
    repondre_btn.id = comment_id;
    repondre_btn.className = "comment-react comment-info"
    repondre_btn.onclick = function () {
        CreateInputTexte(this.id);
    };
    repondre_btn.textContent = "Answer"

    //On crée la balise image de l'user qui envoie le message
    let img_user = document.createElement("img");
    img_user.src = PP;
    
    //Chaque ensemble doit être mis dans une div de mise en forme
    let mother_div = document.createElement("div");
    mother_div.className = "user-profil comment-box";

    let answer_div = document.createElement("div");
    answer_div.className = "answers_div";
    answer_div.id = comment_id + "_answer_section";

    new_bulle.append(username_message);
    new_bulle.append(text_message);

    info_message.append(repondre_btn)
    info_message.append(date_message)

    shadow_bulle_container.append(new_bulle);
    shadow_bulle_container.append(info_message);

    mother_div.append(img_user)
    mother_div.append(shadow_bulle_container);

    if(content != "") {
        comment_list.append(mother_div); //devra être comment_list[i] quand il y aura plusieurs posts ? ou alors créer des id pour chaque comment_list selon l'id du post
        comment_list.append(answer_div);
    }
    document.getElementById("actual_writen_message").value = "";

    //On scroll vers le bas quand on ajoute un message
    comment_section.scrollTop = comment_section.scrollHeight;

    //S'il y a deja un champ de réponse à un commentaire, alors on le supprime quand l'utilisateur envoie un commentaire
    let inputs_text_area = document.getElementsByClassName("comment-input");
    if(inputs_text_area.length == 2) {
        inputs_text_area[0].parentNode.remove();
    }
}

//Fonction qui crée la bulle comments selon la database chargé en ajax lors du clique sur l'icone commentaire
function createBulleComments(comments, post_id) {
    let div_comments = document.createElement("div");
    div_comments.className = "comment-menu comment-menu-height";
    div_comments.id = "close" + post_id;
    let comment_icon = document.getElementById("CommentSection" + post_id).parentNode;
    let comments_list = document.createElement("div");
    comments_list.id = post_id + "_comments_list";
    comments_list.className = "comments-list";
    
    if(comments[0][0] != "empty"){
        for(i=0; i<comments.length; i++) {

            let comment_box = document.createElement("div");
            comment_box.className = "user-profil comment-box"

            let user_image_comments = document.createElement("img");
            user_image_comments.src = comments[i][5];

            let shadow_comment_div = document.createElement("div"); //Necessaire pour la mise en forme

            let comment_pseudo_text_div = document.createElement("div");
            comment_pseudo_text_div.className = "comment-pseudo-text";

            let pseudo = document.createElement("a");
            pseudo.className = "comment-pseudo";
            pseudo.innerHTML = comments[i][4];

            let text = document.createElement("p");
            text.className = "comment-text";
            text.innerHTML = comments[i][2];
            
            let reactions_div = document.createElement("div");
            reactions_div.className = "comment-reaction";

            let repondre_btn = document.createElement("p");
            repondre_btn.id = comments[i][0];
            repondre_btn.className = "comment-react comment-info";
            repondre_btn.onclick = function () {
                CreateInputTexte(this.id);
            };
            repondre_btn.innerHTML = "Answer";

            let comment_date = document.createElement("p");
            comment_date.className = "comment-info";
            comment_date.innerHTML = comments[i][1];

            let answer_section = document.createElement("div");
            answer_section.id = comments[i][0] + "_answer_section";
            answer_section.className = "answers_div";
            

            comment_pseudo_text_div.append(pseudo);
            comment_pseudo_text_div.append(text);
            reactions_div.append(repondre_btn);
            reactions_div.append(comment_date);
            shadow_comment_div.append(comment_pseudo_text_div);
            shadow_comment_div.append(reactions_div);
            comment_box.append(user_image_comments);
            comment_box.append(shadow_comment_div);
            comments_list.append(comment_box);
            comments_list.append(answer_section);
        }
    }

    let input_comment_message = document.createElement("input");
    input_comment_message.id = "actual_writen_message";
    input_comment_message.type = "text";
    input_comment_message.className = "form-control comment-input";
    input_comment_message.placeholder = "Write your comment";
    input_comment_message.onkeydown = function() {
    if (event.keyCode == 13) createCommentsFromWeb(post_id, this.value) //Ce n'est pas pas deprecated, bug IDE*
    };

    let comment_send_icon = document.createElement("ion-icon");
    comment_send_icon.name = "send";

    let div_send_comment = document.createElement("div");
    div_send_comment.className = "send_menu_comment";

    let div_comment_send_icon = document.createElement("div");
    div_comment_send_icon.className = "send_icon_message";
    div_comment_send_icon.onclick = function () {
        createCommentsFromWeb(post_id, input_comment_message.value);
    };

    div_comments.append(comments_list);
    div_send_comment.append(input_comment_message);
    div_comment_send_icon.append(comment_send_icon);
    div_send_comment.append(div_comment_send_icon);
    div_comments.append(div_send_comment);
    comment_icon.after(div_comments);
}

//Fonction qui crée un champ input texte pour la réponse à un commentaire
function CreateInputTexte(commentID) {

    //S'il y a deja un champ de réponse à un commentaire, alors on le supprime
    let inputs_text_area = document.getElementsByClassName("comment-input");
    if(inputs_text_area.length == 2) {
        inputs_text_area[0].parentNode.remove();
    }

    let trash_icon = document.createElement("ion-icon");
    trash_icon.name = "trash";

    let div_trash_icon = document.createElement("div");
    div_trash_icon.className = "send_icon_message";
    div_trash_icon.onclick = function () {
        removeInput(this.parentNode);
    };

    let send_icon = document.createElement("ion-icon");
    send_icon.name = "send";

    let input_answer = document.createElement("input");
    input_answer.id = commentID + "_answer_input";
    input_answer.type = "text";
    input_answer.className = "form-control comment-input";
    input_answer.placeholder = "Write your answer";
    input_answer.onkeydown = function() {
        if (event.keyCode == 13) createAnswerFromWeb(commentID, input_answer.value) //Ce n'est pas pas deprecated, bug IDE*
    };

    let div_send_icon = document.createElement("div");
    div_send_icon.className = "send_icon_message";
    div_send_icon.onclick = function () {
        createAnswerFromWeb(commentID, input_answer.value);
    };
    

    let answer_sender = document.createElement("div");
    answer_sender.className = "send_menu_answer"

    div_trash_icon.append(trash_icon);

    div_send_icon.append(send_icon);

    answer_sender.append(div_trash_icon);
    answer_sender.append(input_answer);
    answer_sender.append(div_send_icon);

    answer_section_id = commentID + "_answer_section";
    let answer_section = document.getElementById(answer_section_id);
    answer_section.append(answer_sender);
    //object.parentNode.parentNode.parentNode.parentNode.append(answer_sender); a sup après

    //Donne le focus sur le input_answer fraichement créé
    input_answer.focus();
}

//Fonction qui crée les bulles answers selon la database chargé en ajax lors du clique sur l'icone commentaire
function createBulleAnswer(answerDate, answerContent, commentID, userName, userPP) { //0: AnswersId ; 1: AnswersDate ; 2: AnswersContent ; 3: UserID ; 4: CommentID ; 5: Username ; 6: PP



    //On récupère la div conversation pour y ajouter la nouvelle bulle message
    answers_section_id = commentID + "_answer_section";
    let answers_section = document.getElementById(answers_section_id);

    //On crée un container de bulle nécessaire pour le bon affichage des elements flex dans un flex grand-parent
    let shadow_bulle_container = document.createElement("div");

    //On crée la nouvelle bulle avec la bonne classe
    let new_bulle = document.createElement("div");
    new_bulle.className = "comment-pseudo-text";

    //Cette bulle doit contenir le contenu du message et les informations annexes avec les bonnes classes css
    let username_message = document.createElement("a");
    username_message.textContent = userName;
    username_message.className = "comment-pseudo";

    let text_message = document.createElement("p");
    text_message.textContent = answerContent;
    text_message.className = "comment-text";

    //On crée la div qui va contenir les infos liés au commentaire
    let info_message = document.createElement("div");
    info_message.className = "comment-reaction";

    //On crée la balise qui contient la date du message et le bouton Answer
    let date_message = document.createElement("p");
    date_message.className = "comment-info";
    date_message.textContent = answerDate;
    
    let repondre_btn = document.createElement("p");
    repondre_btn.id = commentID; //et non pas du db answer
    repondre_btn.className = "comment-react comment-info";
    repondre_btn.onclick = function () {
        CreateInputTexte(this.id); 
    };
    repondre_btn.textContent = "Answer";
    
    //Pour la mise en forme, il faut une div vide qui centre à droite la bulle
    //Le tout doit être mit dans une div qui prend 100% de la taille du champ conversation
    let mother_div = document.createElement("div");
    mother_div.className = "user-profil comment-box"

    //On crée la balise image de l'user qui envoie le message
    let img_user = document.createElement("img");
    img_user.src = userPP;

    new_bulle.append(username_message);
    new_bulle.append(text_message);

    info_message.append(repondre_btn)
    info_message.append(date_message)

    shadow_bulle_container.append(new_bulle);
    shadow_bulle_container.append(info_message);

    mother_div.append(img_user)
    mother_div.append(shadow_bulle_container);

    answers_section.appendChild(mother_div);
}

//A sup
//Fonction qui écrit la réponse à un commentaire du post puis supprime le input_answer
function sendAnswer(input_answer, comment_id) {

    let now = new Date();

    //On récupère le message qui est écrit dans le champ message
    let message = document.getElementById(comment_id + "_answer_input").value;

    //On récupère la div conversation pour y ajouter la nouvelle bulle message
    answers_section_id = comment_id + "_answer_section";
    let answers_section = document.getElementById(answers_section_id);

    //On crée un container de bulle nécessaire pour le bon affichage des elements flex dans un flex grand-parent
    let shadow_bulle_container = document.createElement("div")

    //On crée la nouvelle bulle avec la bonne classe
    let new_bulle = document.createElement("div");
    new_bulle.className = "comment-pseudo-text";

    //Cette bulle doit contenir le contenu du message et les informations annexes avec les bonnes classes css
    let username_message = document.createElement("a")
    username_message.textContent = "username_from_db"
    username_message.className = "comment-pseudo"

    let text_message = document.createElement("p");
    text_message.textContent = message;
    text_message.className = "comment-text";

    //On crée la div qui va contenir les infos liés au commentaire
    let info_message = document.createElement("div");
    info_message.className = "comment-reaction";

    //On crée la balise qui contient la date du message et le bouton Answer
    let date_message = document.createElement("p")
    date_message.className = "comment-info"
	date_message.textContent = now.getFullYear() + "-" + ('0' + (now.getMonth() + 1)).slice(-2) + "-" + ('0'+now.getDate()).slice(-2) + " " + now.getHours() + ":" + now.getMinutes() + ":" + now.getSeconds();
    
    let repondre_btn = document.createElement("p")
    repondre_btn.id = comment_id; //et non pas du db answer
    repondre_btn.className = "comment-react comment-info"
    repondre_btn.onclick = function () {
        CreateInputTexte(this.id); 
    };
    repondre_btn.textContent = "Answer"
    
    //Pour la mise en forme, il faut une div vide qui centre à droite la bulle
    //Le tout doit être mit dans une div qui prend 100% de la taille du champ conversation
    let mother_div = document.createElement("div");
    mother_div.className = "user-profil comment-box"

    //On crée la balise image de l'user qui envoie le message
    let img_user = document.createElement("img");
    img_user.src = "./images/user-3-pic.jpg"

    new_bulle.append(username_message);
    new_bulle.append(text_message);

    info_message.append(repondre_btn)
    info_message.append(date_message)

    shadow_bulle_container.append(new_bulle);
    shadow_bulle_container.append(info_message);

    mother_div.append(img_user)
    mother_div.append(shadow_bulle_container);

    if(message != "") {
        answers_section.append(mother_div);
    }
    document.getElementById(comment_id + "_answer_input").value = "";

    //ce qui est plus haut est remplacé par l'appel ajax
    createAnswer(comment_id); //appel fonction ajax 
    removeInput(input_answer);
}

//Fonction qui supprime le input_answer
function removeInput(input_answer) {
    input_answer.remove();
}

function LikePost(postId, elmtHeart, heartNo) {
    elmtLikeCount = document.getElementById("likeCount"+heartNo);
    if(elmtHeart.style.color == "red"){
        elmtHeart.style.color = "gray";
        LikePostRequest(postId, 0);
    } else {
        elmtHeart.style.color = "red";
        LikePostRequest(postId, 1);
    }
}

function updateLikeCount(res, mode) {
    if(res == 1) {
        if(mode == "LikeP") {
            elmtLikeCount.innerHTML = parseInt(elmtLikeCount.innerHTML) + 1;
        } else if(mode == "UnlikeP") {
            elmtLikeCount.innerHTML = parseInt(elmtLikeCount.innerHTML) - 1;
        }
    }
}

//Fonction qui partage un post
function shareSocial(e) {
    if(e.style.color == "blue")
    return;
    // On récupère la div qui contient l'ensemble du post
    var postToShare = e.parentNode.parentNode.parentNode.parentNode;
    var userName = postToShare.querySelector("#userName_Post").innerHTML;
    postToShare.style.border = "1.5px solid black";
    var id = postToShare.children[2].children[1].children[1].children[0].id;
    id = "P" + id.split("P")[1];
      
    // On utilise la bibliothèque html2canvas pour créer une capture d'écran de la div
    html2canvas(postToShare).then(function(canvas) {
        postToShare.style.border = "none";
      
        // On récupère l'image au format base64
        var postBase64 = canvas.toDataURL();
        var base = (postBase64).split("base64,")[1];
        var type = (postBase64).split(";")[0].split("data:")[1];

        // On crée une div pour contenir le formulaire de partage
        var shareDiv = document.createElement("div");
        shareDiv.className = "share-div";
        shareDiv.style = "position : absolute; margin-left: 400px; margin-top: 100px; border-radius: 8px; width : 300px; background-color : #fff; transition: 0.4s ease; text-align : center;";
      
        // On crée un formulaire pour envoyer l'image au serveur
        var form = document.createElement("form");
        form.method = "POST";
        form.name = "sharePost";
        form.action = "php/postProcess.php"
  
        // On crée des champs cachés pour envoyer les données de l'image
        var baseShare = document.createElement("input")
        baseShare.name = "baseShare";
        baseShare.value = base;
        baseShare.type = "hidden";
  
        var typeShare = document.createElement("input")
        typeShare.name = "typeShare";
        typeShare.value = type;
        typeShare.type = "hidden";
        shareDiv.style.zIndex = "9";
  
        var idPost = document.createElement("input")
        idPost.name = "idPost";
        idPost.value = id;
        idPost.type = "hidden";

        var isShare = document.createElement("input");
        isShare.name = "isShare";
        isShare.value = "Regardez ce post de "+userName;
        isShare.type = "text";
        isShare.className = "form-control comment-input";
  
        var submit = document.createElement("input")
        submit.type = "submit";
        submit.className = "submit-post"
        submit.style ="margin-bottom : 8px;";
        submit.value = "Share";
  
        var cancel = document.createElement("button");
        cancel.type = "button";
        cancel.className = "cancel-post";
        cancel.innerHTML = "Cancel";
        cancel.className = "submit-post"
        cancel.style = " margin-left: 30px; margin-bottom: 8px";
        cancel.addEventListener("click", function() {
            shareDiv.remove();
        });
  
        // On ajoute les champs cachés et les boutons au formulaire
        form.appendChild(baseShare);
        form.appendChild(typeShare);
        form.appendChild(isShare);
        form.appendChild(idPost);
        form.appendChild(submit);
        form.appendChild(cancel);
        shareDiv.appendChild(form);
        
  
        e.parentNode.parentNode.appendChild(shareDiv);
        // On ajoute un écouteur d'événement pour détecter les clics en dehors de la div "shareDiv"
        document.addEventListener("click", function(event) {
            if (!event.target.closest(".share-div")) {
                // Si l'élément cliqué ne se trouve pas dans la div "shareDiv" ou dans cette div elle-même, on supprime la div "shareDiv"
                var shareDiv = document.querySelector(".share-div");
                if (shareDiv) {
                    shareDiv.remove();
                }
            }
        });
  
        isShare.focus();
    });
}

function createPostContainer(profilPic, userName, postTime, textContent, tabPicturesContent, numberOfLike, placePost, isLikedPost, postID, nbComments, isShared, nbShare, namediv) {
    // création de la div post-container
    var postContainerDiv = document.createElement("div");
    postContainerDiv.className = "post-container";
  
    // création de la div user-profil
    var userProfilDiv = document.createElement("div");
    userProfilDiv.className ="user-profil";
    postContainerDiv.appendChild(userProfilDiv);
  
    // ajout de l'image de profil
    var profilImg = document.createElement("img");
    profilImg.src = profilPic;
    userProfilDiv.appendChild(profilImg);
  
    // création de la div avec le nom d'utilisateur et le timestamp
    var userNameAndTimeDiv = document.createElement("div");
    userProfilDiv.appendChild(userNameAndTimeDiv);
  
    // ajout du nom d'utilisateur
    var userNamePost = document.createElement("p");
    userNamePost.id = "userName_Post";
    userNamePost.innerText = userName;
    userNameAndTimeDiv.appendChild(userNamePost);
  
    // ajout de la date de publication
    var timestampSpan = document.createElement("span");
    timestampSpan.innerText = postTime;
    userNameAndTimeDiv.appendChild(timestampSpan);
  
    // ajout du texte du post
    var postTextP = document.createElement("p");
    postTextP.className ="post-text";
    postTextP.innerText = textContent;
    postContainerDiv.appendChild(postTextP);
  
    // création de la div post-media
    var postMediaDiv = document.createElement("div");
    postMediaDiv.className ="post-media";
    postContainerDiv.appendChild(postMediaDiv);
  
    // création de la div post-images
    var postImagesDiv = document.createElement("div");
    postImagesDiv.className = "post-images";
    postMediaDiv.appendChild(postImagesDiv);
  
    // ajout des images du post
    if(Array.isArray(tabPicturesContent)){
        if (tabPicturesContent.length > 0 && tabPicturesContent.length < 5) {
            for (let k = 0; k < tabPicturesContent.length; k++) {
                var postImg = document.createElement("img");
                postImg.src = tabPicturesContent[k];
                postImg.alt = 'Img Media' + k;
                postImg.className ="post-img";
        
                // vérification si le post a une seule image pour modifier la taille
                if (tabPicturesContent.length == 1) {
                postImg.style.width = "200%";
                postImg.style.height = "auto";
                }
        
                postImagesDiv.appendChild(postImg);
            }
        }
    }
  
    // création de la div post-reactions
    var postReactionsDiv = document.createElement("div");
    postReactionsDiv.className ="post-reactions";
    if(!Array.isArray(tabPicturesContent)){
        postReactionsDiv.style = "flex-direction:row";
    } 
    postMediaDiv.appendChild(postReactionsDiv);

    // Création du bouton like
    var likeButtonDiv = document.createElement("div");
    var likeButton = document.createElement("ion-icon");
    likeButton.setAttribute("name", "heart");
    likeButton.setAttribute("onclick", "LikePost('"+ postID + "', this, '"+ placePost+"')");
    if (isLikedPost > 0) {
        likeButton.style.color = "red";
    }
    var likeCount = document.createElement("small");
    likeCount.setAttribute("id", `likeCount` + placePost);
    likeCount.innerHTML = numberOfLike;
    likeButtonDiv.appendChild(likeButton);
    likeButtonDiv.appendChild(likeCount);
    postReactionsDiv.appendChild(likeButtonDiv);

    // Création du bouton commentaire
    var commentButtonDiv = document.createElement("div");
    var commentButton = document.createElement("ion-icon");
    commentButton.setAttribute("name", "chatbox-ellipses");
    commentButton.id = 'CommentSection'+postID;
    commentButton.setAttribute("onclick", 'CommentSectionCall(this.id)');
    var commentCount = document.createElement("small");
    commentCount.innerHTML = nbComments;
    commentButtonDiv.appendChild(commentButton);
    commentButtonDiv.appendChild(commentCount);
    postReactionsDiv.appendChild(commentButtonDiv);

    // Création du bouton de partage
    var shareButtonDiv = document.createElement("div");
    var shareButton = document.createElement("ion-icon");
    shareButton.setAttribute("name", "share-social");
    shareButton.setAttribute("onclick", `shareSocial(this)`);
    if (isShared > 0) {
        shareButton.style.color = "blue";
    }
    var shareCount = document.createElement("small");
    shareCount.innerHTML = nbShare;
    shareButtonDiv.appendChild(shareButton);
    shareButtonDiv.appendChild(shareCount);
    postReactionsDiv.appendChild(shareButtonDiv);

    //On ajoute le post a la page
    var middle = (namediv == 'middle-content') ? document.getElementsByClassName(namediv)[0] : document.getElementById(namediv) ;
    middle.appendChild(postContainerDiv);
}
    