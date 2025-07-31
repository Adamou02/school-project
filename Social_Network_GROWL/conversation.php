<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Your Conversation | GROWL</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css">
    <link rel="icon" type="image/ico" href="./images/growl_ico.ico">
    <link rel="stylesheet" href="css/conversations.css">
    <script src="https://unpkg.com/sweetalert/dist/sweetalert.min.js"></script>
</head>

    <body>

        <?php 
            require_once("./php/constant.php");
            include_once(HEADER); 
            if(!s_isConnected())
                redirect(INDEX);

            if(isset($_GET["user_conv"])  && db_alreadyExist('user', 'Username', "'".$_GET["user_conv"]."'")) { // on récupère l'id de l personne à qui on souhaite parler
                $user_selected = db_selectColumns('user',['UserID'], ['Username' => ['LIKE', "'".$_GET["user_conv"]."'", '0']])[0][0];
            }

            $friends_id = db_order_lastConversation($_SESSION['connected']);

            if(count($friends_id) == 0) {
                ?><script>
                    swal({
                        title: "You don't have any friends, you can't converse with anyone. Try to get new friends on the website",
                        button: false,
                        allowOutsideClick: false
                    }).then((result) => {
                        window.location.replace('<?= INDEX ?>')
                    });
                 </script><?php
            }

            if(isset($user_selected)){ // il y a un ami en get, on le sélectionne
                $last_communicate_friend = db_getUserData($user_selected);
                $conversation = db_getConversation($user_selected,$_SESSION['connected']);
            } else {
                $last_communicate_friend = db_getUserData($friends_id[0]);
                $conversation = db_getConversation($friends_id[0],$_SESSION['connected']);
            }
            
            if($conversation == 0){
                $number_message = 0;
            }else{
                $number_message = count($conversation);
            }

        ?>
        
        <main class="main">

            <!-- Left Content -->
                <?php include_once(ASIDE) ?>
            <!-- Middle Content -->
            
             <div class="middle-content middle-message">
                <div class="box_message">

                    <div class="title_message">
                        <div class="username_receiver_message">
                            <h3 id="current_speaking"><?= $last_communicate_friend[0]; ?></h3>
                        </div>
                        <div class="date_last_message">
                            <span id="current_speaking_date_last_message"><?php if($number_message !=0) echo "<script> changeFormatDate('".$conversation[$number_message-1][5]."', 'current_speaking_date_last_message', 1)</script> ";?></span>
                        </div>
                    </div>

                    <div id="conv" class="conv_message">

                    <?php if($number_message > 0)
                        for($i=$number_message-1;$i>=0; $i--){?>
                    <div>
                        <div class=" <?php 
                            if($i>0){echo "my-empty-conv";}?>">                            
                        </div>
                        <div class="bulle <?php 
                            if($conversation[$i][1]==$_SESSION['connected']){echo "my_bulle_message";}
                            else{echo "friend_bulle_message";}?>">
                            <span class=" <?php 
                                if($conversation[$i][1]==$_SESSION['connected']){echo "message_info";}
                                else{echo "message_info friend_name_message";}?>">
                                <?php 
                                if($conversation[$i][1]==$_SESSION['connected']){echo "Me";}
                                else{echo $last_communicate_friend[0];}?>
                            </span>
                            <?php if($conversation[$i][4] != NULL){
                                $media = db_selectColumns(
                                    table_name:'media',
                                    columns:['Base64', 'Type'], 
                                    filters:['MediaID' => ['LIKE', '"'.$conversation[$i][4].'"','0']]
                                 );
                                 $base = $media[0][0];
                                 $type = $media [0][1]; ?>
                                 <img src="data:<?=$type ?>;base64,<?=$base ?>" alt="marche po" id ="image_message" class="text_message">
                                 <?php
                                 } else {?>
                            <span class="text_message"><?php echo urldecode($conversation[$i][3]);?></span>
                            <?php
                                 }?>
                            <span id="<?=$i;?>" class="message_info date_message" ><script>changeFormatDate('<?=$conversation[$i][5]?>', '<?=$i?>', '1')</script></span>  
                        </div>
                    </div>
                    <?php } ?>     
                    </div>

                    <div class="send_menu_message">
                        <div class="message_image_file">
                        <input type="file" name="picture" id="hiddenfile" onchange="previewPicture(this)"  accept=".jpeg, .jpg, .png"  style="display:none">
                            <ion-icon name='images' onclick="getfile()" ></ion-icon>
                        </div>

                        <input id="actual_writen_message" type="text" class="form-control" placeholder="Write message..."  onkeypress="if (event.keyCode == 13) sendMessage()">
                        <div class="send_icon_message" onclick="sendMessage()">
                            <ion-icon name="send"></ion-icon>
                        </div>
                        
                    </div>
                    <p id="error-size-image"></p>
                </div>        
            </div>
            <!-- Right Content -->
            <?php 
                define('ARRAYFRIEND','1');
                if(isset($_GET["user_conv"])){
                    define('SELECTEDFRIEND','1');
                }                 
                $onclickfct = 'selectDiscussion';
                include_once(LISTFRIEND);
            ?>           
        </div>


        </main>

        <?php include_once(FOOTER); ?> 
        
    </body>
    <script rel="stylesheet" src="js/conversations.js"></script>
    <!-- les autres script on été déplacé dans le footer adam, si jamais tu te pose la question -->
</html>
