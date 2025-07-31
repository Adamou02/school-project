function getXhr()//cree objetXHR
{
    if (window.XMLHttpRequest) // Pour la majorité des navigateurs
        return new XMLHttpRequest() ;
    else if(window.ActiveXObject){ // Anciens navigateurs (IE<7)
        try {
            return new ActiveXObject("Msxml2.XMLHTTP") ;
        } catch (e) {
            return new ActiveXObject("Microsoft.XMLHTTP") ;
        }
    }
    else { // XMLHttpRequest non supporté par le navigateur
        alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest...") ; 
    }
    return NULL ;
}

/*Fonction d'envoie de requetes Ajax*/

function AddNewPost(){
    var requestCartA= getXhr();
    requestCartA.open("POST","./php/ajaxRequest.php",true);
    requestCartA.onreadystatechange = function(){
        if(requestCartA.readyState == 4 && requestCartA.status == 200){
            var reponse=requestCartA.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split(";");
        }
    }
    requestCartA.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestCartA.send('fct=AddNP');
    return 0;    
}

function addNewMessage(){
    var content = document.getElementById("actual_writen_message").value
    var requestNewM= getXhr();
    requestNewM.open("POST","./php/ajaxRequest.php",true);
    requestNewM.onreadystatechange = function(){
        if(requestNewM.readyState == 4 && requestNewM.status == 200){
            var reponse=requestNewM.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split(";");
        }
    }
    requestNewM.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestNewM.send('fct=AddNM'+ '&content=' + content + '&UsernameReceiver=' + userNameReceiver);
    return 0;    
}

function changeConversation(username_friend){
    var requestChangeC= getXhr();
    requestChangeC.open("POST","./php/ajaxRequest.php",true);
    requestChangeC.onreadystatechange = function(){
        if(requestChangeC.readyState == 4 && requestChangeC.status == 200){
            var reponse=requestChangeC.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split("***");
            var number_messages = (res.length-2)/6;
            let all_messages = [];
            let data = [res[0],res[1]];//variable contenant les informations de l'ami dont la fenetre de discussion est ouverte avec un 0 son username et en 1 sa photo 
            if(res.length >4 ){
                for(var j=0;j<(number_messages);j++){
                    all_messages[j] = []; // tableau de la taille du nombre de message
                    for(var k = 0;k<6;k++){
                        all_messages[j][k] = res[6*j+2+k]// dans le tableau on y met un tableau contenant toutes les infos du message
                    }
                }
            } else {
                all_messages[0] = [];
                all_messages[0][0] = "";
            }
            updateConvMessage(data,all_messages);
        }
    }
    requestChangeC.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestChangeC.send('fct=chngCV ' + '&usernameFriend=' + username_friend);
    return 0;    
}

function sendMessageIntoDB(content, type){
    encodeURI(content);  
    var username_friend = document.getElementById('current_speaking').innerHTML;
    username_friend = username_friend.trim();
    var requestsendMIDB= getXhr();
    requestsendMIDB.open("POST","./php/ajaxRequest.php",true);
    requestsendMIDB.onreadystatechange = function(){
        if(requestsendMIDB.readyState == 4 && requestsendMIDB.status == 200){
            var reponse=requestsendMIDB.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split(";");
            //updateFriendsOrder(res[1]);
        }
    }
    requestsendMIDB.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestsendMIDB.send('fct=sendMIDB '+ '&usernameFriend=' + username_friend + '&content=' + content + '&type=' + type);
    return 0;   
}

function searchProfil(inputValue){
    var requestSP= getXhr();
    requestSP.open("POST","./php/ajaxRequest.php",false); //j'ai passer la requete en synchrone pour evité les double réponse
    
    requestSP.onreadystatechange = function(){
        if(requestSP.readyState == 4 && requestSP.status == 200){
            var reponse=requestSP.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split(";;;");
            res[0] = res[0].replace(' \r\n\r\n\r\n\r\n\r\n','');
            var tmp=[];
            for(var i = 0 ; i< res.length; i++){
                tmp[i] = [];
                tmp[i]=res[i].split("***");
            }
            displayResult(tmp.length, tmp)
        }
    }
    requestSP.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestSP.send('fct=SP '+ '&inputValue=' + inputValue);
}

//Fonction qui crée le commentaire lorsque l'utilisateur clique sur l'icone commentaire du post
function createComments(post_id){
    var requestCCM= getXhr();
    requestCCM.open("POST","./php/ajaxRequest.php",true);
    requestCCM.onreadystatechange = function(){
        if(requestCCM.readyState == 4 && requestCCM.status == 200){
            var reponse=requestCCM.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split("***");
            res[0] = res[0].replace(' \r\n\r\n\r\n\r\n\r\n','');
            var number_comments = res.length/6;
            let comments = [];
            let comments_id_list = [];
            for(var i=0; i<number_comments;i++){ 
                comments[i]=[];
                if(i==0) res[0] = res[0].trim(); //Bug apparu sur la branche dev qui n'etait pas la su ma branche perso
                comments[i][0] = res[i*6];
                comments_id_list[i] = res[i*6];
                comments[i][1] = res[i*6+1];
                comments[i][2] = res[i*6+2];
                comments[i][3] = res[i*6+3];
                comments[i][4] = res[i*6+4];
                comments[i][5] = res[i*6+5];
            }
            createBulleComments(comments, post_id);
            createAnswers(comments_id_list, post_id);
        }
    }
    requestCCM.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestCCM.send('fct=CCM '+ '&postID=' + post_id);
}

//Fonction qui crée le commentaire lorsque l'utilisateur écrit un commentaire dans la bulle input de l'espace commentaire
function createCommentsFromWeb(post_id, comment){
    var requestCMFW= getXhr();
    requestCMFW.open("POST","./php/ajaxRequest.php",true);
    requestCMFW.onreadystatechange = function(){
        if(requestCMFW.readyState == 4 && requestCMFW.status == 200){
            var reponse=requestCMFW.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split("***");
            res[0] = res[0].replace(' \r\n\r\n\r\n\r\n\r\n','');
            sendComment(res[1], res[2], res[3], res[4], res[5], res[6]); //respectivement : comment_id, content, user_id, post_id, username, pp
        }
    }
    requestCMFW.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestCMFW.send('fct=newCMFW '+ '&postID=' + post_id + '&content=' + comment);
}

function createAnswers(comment_id_list, post_id){
    var requestgA= getXhr();
    requestgA.open("POST","./php/ajaxRequest.php",true);
    requestgA.onreadystatechange = function(){
        if(requestgA.readyState == 4 && requestgA.status == 200){
            var reponse=requestgA.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split("***");
            
            res[0] = res[0].replace(' \r\n\r\n\r\n\r\n\r\n','');
            //Enleve le dernier element qui est nul a cause du separateur ajax ***
            res.pop()
            var number_answers = res.length/5;
            for(var i=0; i<number_answers;i++){
                createBulleAnswer(res[i*5], res[i*5+1], res[i*5+2], res[i*5+3], res[i*5+4]);
            }
            //On scroll l'espace commentaire vers le bas
            let comment_section = document.getElementById("close" + post_id);
            comment_section.scrollTop = comment_section.scrollHeight;
        }
    }
    requestgA.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestgA.send('fct=cA '+ '&commentIDlist=' + comment_id_list);
    return 0;   
}

//Fonction qui crée le commentaire lorsque l'utilisateur écrit un commentaire dans la bulle input de l'espace commentaire
function createAnswerFromWeb(comment_id, answerContent){
    var requestCMFW= getXhr();
    requestCMFW.open("POST","./php/ajaxRequest.php",true);
    requestCMFW.onreadystatechange = function(){
        if(requestCMFW.readyState == 4 && requestCMFW.status == 200){
            var reponse=requestCMFW.responseText;
            if(reponse==0){
                return 0;
            }
            var res=reponse.split("***");
            res[0] = res[0].replace(' \r\n\r\n\r\n\r\n\r\n','');
            createBulleAnswer(res[2], res[3], res[5], res[6], res[7]);
            input_answer = document.getElementById(res[5] + "_answer_input");
            removeInput(input_answer.parentNode);
        }
    }
    requestCMFW.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestCMFW.send('fct=newAFW '+ '&commentID=' + comment_id + '&content=' + answerContent);
}

function LikePostRequest(postId, action) {
    var fct;
    if(action == 1) //like post 
        fct = "LikeP";
    else            //Unlike post
        fct = "UnlikeP";
    var requestLP= getXhr();
    requestLP.open("POST","./php/ajaxRequest.php",false);
    requestLP.onreadystatechange = function(){
        if(requestLP.readyState == 4 && requestLP.status == 200){
            var reponse=requestLP.responseText;
            updateLikeCount(reponse.split("***")[1], fct); // return 1 si le like / le unlike est successfull, 0 sinon
        }
    }
    requestLP.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestLP.send('fct=' + fct + '&postID=' + postId); 
}

function displayMorePosts(postsDisplayed, postToPrint, maxDatetime, mode, username, formCount, keyWord){
    var namebtn;
    var namediv;
    switch (mode) {
        case 'index':
            namebtn = 'addMorePost';
            namediv = 'middle-content';
        break;
        case 'prof_liked':
            namebtn = 'addMorePostLikedPost';
            namediv = 'content2';
        break;
        case 'prof_shared':
            namebtn = 'addMorePostSharedPost';
            namediv = 'content3';
        break;
        case 'prof_all':
            namebtn = 'addMorePostAllPost';
            namediv = 'content1';
        break;
        default:
            console.log("pas bon : " + mode);
            break;
    }
    if (keyWord == null)
        keyWord = '***';
    var nbInfosForPosts = 11;
    var requestDMP= getXhr();
    requestDMP.open("POST","./php/ajaxRequest.php",false);
    requestDMP.onreadystatechange = function(){
        if(requestDMP.readyState == 4 && requestDMP.status == 200){
            var reponse=requestDMP.responseText;
            if(reponse==0){
                return 0;
            }            
            var res=reponse.split("***");
            document.getElementById(namebtn).remove();
            var totalPostNotDisplayed = res[0].split('**;**')[0].replace(' ', '');
            var postAdd = parseInt(res[0].split('**;**')[1]) - postsDisplayed;
            var post = [];
            var decalageImage = 0;
            for (var i=0; i<postAdd; i++){
                post[i] = [];
                post[i][0] = res[i* nbInfosForPosts +1 + decalageImage]; //id du post
                post[i][1] = res[i* nbInfosForPosts +2+ decalageImage]; //date du post
                post[i][2] = res[i* nbInfosForPosts +3+ decalageImage]; // le nombre de like
                post[i][3] = res[i* nbInfosForPosts +4+ decalageImage]; // le nombre de partage
                if(parseInt(res[i* nbInfosForPosts +5+ decalageImage]) > 0){
                    post[i][4] = [];
                    for(var j = 0; j<res[i* nbInfosForPosts +5+ decalageImage]; j++){
                        post[i][4][j] = res[i* nbInfosForPosts +5+ decalageImage + j+1];
                    }
                    decalageImage = decalageImage + parseInt(res[i* nbInfosForPosts +5 + decalageImage]);
                } else {
                    post[i][4] = res[i* nbInfosForPosts +5+ decalageImage];
                }
                post[i][5] = res[i* nbInfosForPosts +6+ decalageImage]; //le contenu text
                post[i][6] = res[i* nbInfosForPosts +7+ decalageImage]; // la pp de l'envoyeur
                post[i][7] = res[i* nbInfosForPosts +8+ decalageImage]; // le nom de l'envoyeur
                post[i][8] = res[i* nbInfosForPosts +9+ decalageImage]; // le nombre de commentaire 
                post[i][9] = res[i* nbInfosForPosts +10+ decalageImage]; // savoir si le post est like par le user connecte
                post[i][10] = res[i* nbInfosForPosts +11+ decalageImage]; // savoir si le post est partage par le user connecte
            }       
            printPost(post, namediv, formCount);
            formCount += post.length;
            if(parseInt(totalPostNotDisplayed) > 0){
                var middle = (mode == 'index') ? document.getElementsByClassName(namediv)[0] : document.getElementById(namediv) ;
                var inputMore = document.createElement('input');
                inputMore.className = "btn-loadMore";
                inputMore.id = namebtn;
                inputMore.type = 'button';
                inputMore.value = 'Load more';
                inputMore.setAttribute("onclick", "displayMorePosts("+ parseInt(res[0].split('**;**')[1])+", "+ postToPrint +", '" + maxDatetime +"', '" + mode + "', '" + username + "'," + formCount + ", '" + keyWord + "')");   
                middle.appendChild(inputMore); 

                if(mode == 'prof_liked' || mode == 'prof_shared' || mode == 'prof_all') {
                    var addMorePostAllPost = document.getElementById('addMorePostAllPost');
                    if (addMorePostAllPost) {
                        addMorePostAllPost.setAttribute("onclick", "displayMorePosts("+ parseInt(res[0].split('**;**')[1])+", "+ postToPrint +", '" + maxDatetime +"', '" + "prof_all" + "', '" + username + "'," + formCount + ", '" + keyWord + "')");
                    }

                    var addMorePostLikedPost = document.getElementById('addMorePostLikedPost');
                    if (addMorePostLikedPost) {
                        addMorePostLikedPost.setAttribute("onclick", "displayMorePosts("+ parseInt(res[0].split('**;**')[1])+", "+ postToPrint +", '" + maxDatetime +"', '" + "prof_liked" + "', '" + username + "'," + formCount + ", '" + keyWord + "')");
                    }

                    var addMorePostSharedPost = document.getElementById('addMorePostSharedPost');
                    if (addMorePostSharedPost) {
                        addMorePostSharedPost.setAttribute("onclick", "displayMorePosts("+ parseInt(res[0].split('**;**')[1])+", "+ postToPrint +", '" + maxDatetime +"', '" + "prof_shared" + "', '" + username + "'," + formCount + ", '" + keyWord + "')");
                    }

                } 
            }
        }
    }
    requestDMP.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestDMP.send('fct=DMP '+ '&PDisplayed=' + postsDisplayed + '&postToPrint=' + postToPrint + '&keyWord=' + keyWord + '&mdt=' + maxDatetime + '&mode=' + mode + '&username=' + username );
}

//fonction ajax pour setup le SESSION darkMode 

function SessionDarkModUpdate(action) {
    var fct = action;
    var requestDM= getXhr();
    requestDM.open("POST","./php/ajaxRequest.php",false);
    requestDM.onreadystatechange = function(){
        if(requestDM.readyState == 4 && requestDM.status == 200){
            var reponse=requestDM.responseText;
        }
    }
    requestDM.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=utf-8');
    requestDM.send('fct=' + fct); 
}


//fonction réaction au ajax

function changeFormatDate(date_complete, id, have_to_whrite) {    
    var tableauMois = new Array('janvier','février','mars','avril','mai','juin','juillet','août','septembre','octobre','novembre','décembre');
    var date_split = date_complete.split('\u0020');
    var day = date_split[0].split("-");
    var hour = date_split[1].split("\u003A");
    var final_date = hour[0] + ":" + hour[1] + " - " + day[2] + " " + tableauMois[Number(day[1])-1];
    if(have_to_whrite){
        var text_zone = document.getElementById(id);
        text_zone.innerHTML = final_date;
    }
    
    return final_date;
}


function createBulbleMessage(name_friend, text_message, base_media, type_media, date_message, im_speaker,div_one_message){  
    var number_message = document.getElementsByClassName('bulle');
    var bulle_message = document.createElement('div');
    if(im_speaker == 1){
        bulle_message.className = 'bulle my_bulle_message';
    }else{
        bulle_message.className = 'bulle friend_bulle_message';
    }    

    var speaker = document.createElement('span');
    if(im_speaker == 1){
        speaker.className = 'message_info';
        speaker.innerHTML = "Me";
    } else {
        speaker.className = 'message_info friend_name_message';
        speaker.innerHTML = name_friend;
    }
    bulle_message.appendChild(speaker);                

    if(text_message.length != 0){
        var text = document.createElement('span');
        text.className = 'text_message';
        text.innerHTML = decodeURI(text_message);
        bulle_message.appendChild(text);
    } else if(type_media.length != 0){
        content = document.createElement("img");
        base_media = decodeURI(base_media);
        content.src = "data:"+type_media+";base64,"+base_media;
        content.id = "image_message";
        content.className = "text_message";
        bulle_message.appendChild(content);
    }

    var date_message_buble = document.createElement('span');
    date_message_buble.id = number_message.length + 1;
    date_message_buble.className = 'message_info date_message';
    date = changeFormatDate(date_message, number_message.length + 1, 0);
    date_message_buble.innerHTML = date;
    bulle_message.appendChild(date_message_buble);

    div_one_message.appendChild(bulle_message);
}


function updateConvMessage(data, messages){
    var zone_message = document.getElementById('conv');
    zone_message.innerHTML="";
    var number_messages = messages.length;
    document.getElementById('current_speaking').innerHTML = data[0];
    document.getElementById('current_speaking_date_last_message').innerHTML = "";
    if(messages[0][0] == "") //Aucun message
        return;
    document.getElementById('current_speaking_date_last_message').innerHTML = changeFormatDate(messages[number_messages-1][4], 'current_speaking_date_last_message');
    for(var i=number_messages-1; i>=0;i--){
        var div_one_message = document.createElement('div');
        if(i>0){
            var space_between_message = document.createElement('div');
            space_between_message.className = 'my-empty-conv';
            zone_message.appendChild(space_between_message);
        }
        messages[i][2] = messages[i][2].replace(/\+/g, ' ');
        if((messages[i][0]) == data[1]){
            createBulbleMessage(data[0], messages[i][2],messages[i][3], messages[i][5],messages[i][4],"1", div_one_message);
        } else {
            createBulbleMessage(data[0], messages[i][2],messages[i][3], messages[i][5],messages[i][4],"0", div_one_message);               
        }   
        zone_message.appendChild(div_one_message );
    }
}

function updateFriendsOrder(friend_name) {
    friend_name = friend_name.replace('\r\n         </script>\r\n      ', '');
    var recent_one = document.getElementsByName(friend_name);
    recent_one = recent_one[0].id;
    if(recent_one == "friend1"){
        return 0;
    }
    var test = document.createElement("p")
    test.innerHTML = 'test';
    // var number_friend = document.getElementsByClassName('friends_list');
    // console.log(number_friend.length)
    var parent = document.getElementsByClassName('close-friends');
    console.log(parent[0].firstChild);
    parent.insertBefore(test,parent.firstChild);
}

function printPost(tabPosts, namediv, formCount){
    for(var i=0; i<tabPosts.length; i++){
        createPostContainer(tabPosts[i][6],tabPosts[i][7], tabPosts[i][1], tabPosts[i][5], tabPosts[i][4], tabPosts[i][2], formCount + i, tabPosts[i][9], tabPosts[i][0], tabPosts[i][8], tabPosts[i][10], tabPosts[i][3], namediv)
    }
}
