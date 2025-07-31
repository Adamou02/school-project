<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Profil | GROWL</title>
        <link rel="stylesheet" href="css/profil.css">
        <link rel="icon" type="image/ico" href="./images/growl_ico.ico">
        <script src="https://unpkg.com/sweetalert/dist/sweetalert.min.js"></script>   
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css">      
    </head>

    <body>
        <?php 
            require_once("./php/constant.php");
            include_once(HEADER);
            if(isset($_GET["user"])  && db_alreadyExist('user', 'Username', "'".$_GET["user"]."'")) {
                $vieweduser_id = db_selectColumns('user',['UserID'], ['Username' => ['LIKE', "'".$_GET["user"]."'", '0']])[0][0];
                $vieweduserData = db_getUserData($vieweduser_id);

            } else {
                $vieweduser_id = $_SESSION['connected'];
                $vieweduserData = $userData;
            }

            $who = ($vieweduser_id == $_SESSION['connected']) ? "You have" : $vieweduserData[0]." has";

            if($vieweduser_id != $_SESSION['connected']) {
                switch ($vieweduserData[10]) {
                    case 1: //profils confidentialité only friends
                        if(!in_array(array($_SESSION['connected']), db_getFriends($vieweduser_id))) {
                            ?><script>
                                swal({
                                    title: 'This user only allow friend to visit his/her profil',
                                    button: false,
                                    allowOutsideClick: false
                                }).then((result) => {
                                    window.location.replace('<?= INDEX ?>')
                                });
                             </script><?php
                        }
                        break;
                    case 0: //profils confidentialité no one 
                        ?><script>
                            swal({
                                title: 'This user doesnt allow anyone to visit his/her profil',
                                button: false,
                                allowOutsideClick: false
                            }).then((result) => {
                                window.location.replace('<?= INDEX ?>')
                            });
                            
                        </script><?php
                    break;
                    default:
                        break;
                }
            }
        ?>
        <main>
            <?php include_once(ASIDE); ?>
            
            <div class="central">
                <div class="top-profil">

                    <div class="pic-profil">
                        <img src="<?= $vieweduserData[9] ?>" id="pic">
                    </div>

                    <div class="number-profil">
                        <div class="username-profil">
                            <div><?= $vieweduserData[2] ?> <?= $vieweduserData[1] ?></div>
                            <?php if($vieweduser_id == $_SESSION['connected']) { ?>
                            <a href="<?= SETTINGS ?>">
                                <ion-icon name="settings"></ion-icon>
                            </a>
                            <?php }else if(in_array(array($vieweduser_id), db_getFriends($_SESSION['connected']))){ ?>

                                <button id="send-messages" class="button_profil" onclick="submitFormConvLinkProfil()">
                                    Send Messages
                                </button>
                                <form id="form-conversation-link-profil" method="GET" action="<?= CONVERSATION ?>">
                                    <input type="hidden" name="user_conv" value="<?= $vieweduserData[0] ?>">
                                </form>

                            <?php } else if(!in_array(array($vieweduser_id), db_getFriendRequest($_SESSION['connected']))
                                        && !in_array(array($_SESSION['connected']), db_getFriendRequest($vieweduser_id))){ ?>

                                <button id="send-f-request" class="button_profil" onclick="submitFormSendFriendReq()">
                                    Send Friend Request
                                </button>
                                <form id="form-send-f-req" method="POST" action="<?= PHP.FRIEND_PRO ?>">
                                    <input type="hidden" name="SendReqUser" value="<?= $vieweduserData[0] ?>">
                                </form>

                            <?php } ?>
                        </div>
                        <div class="statistique-profil">
                            <?php 
                                $postLikes = db_selectColumns('post',['NumberOfLikes'],['PostedBy_UserID' => ['=', "'".$vieweduser_id."'", '0']]);
                                $nbPosts = count($postLikes);
                                $nbFriends = count(db_selectColumns('friends',['UserID_1'],
                                    ['UserID_1' => ['=', "'".$vieweduser_id."'", '2'],
                                    'UserID_2' => ['=', "'".$vieweduser_id."'", '0'] ]));
                                $nbLikes = 0;
                                for ($i=0; $i < $nbPosts; $i++) { 
                                    $nbLikes += $postLikes[$i][0];
                                }
                            ?>
                            <div class="posts case-number">
                                Posts
                                <p><?= $nbPosts ?></p>
                            </div>
                            <div class="following case-number">
                                Friends
                                <p><?= $nbFriends ?></p>
                            </div>
                            <div class="followers case-number">
                                Likes
                                <p><?= $nbLikes ?></p>
                            </div>
                        </div>
                    </div>
                </div>
                <hr><br>
                <div class="bottom-profil">
                    
                    <div class="container-btn-post">
                        <btn id="box1" class="btn-active-profil"><?php if($vieweduser_id != $_SESSION['connected']) { echo "Posts of ".$vieweduserData[0]; } else { echo "My Posts"; } ?></btn>
                        <btn id="box2"  class="btn-unactive-profil">Liked Posts</btn>
                        <btn id="box3"  class="btn-unactive-profil">Shared Posts</btn>
                    </div>

                    <div class="content-posts">
                        <?php 
                            $AllPosts = db_selectColumns("post", ["*"], ["PostedBy_UserID" => ["LIKE", "'".$vieweduser_id."'","0"]], order_by:["Posted_DateTime"], suffix:" DESC");
                            $LikedPostsId = db_selectColumns("liked_post", ["PostID"], ["UserID" => ["LIKE", "'".$vieweduser_id."'","0"]], order_by:["Liked_DateTime"], suffix:" DESC");
                            $SharedPostsId = db_selectColumns("shared_post", ["PostID"], ["UserID" => ["LIKE", "'".$vieweduser_id."'","0"]], order_by:["Shared_DateTime"], suffix:" DESC");
                            $formCount = 0;
                            $toLoad = 0;
                        ?>
                        <div id="content1" >
                            <?php 
                            if(count($AllPosts) > 0) {
                                $number_print_posts = min(count($AllPosts), POSTS_DISPLAYED);
                                for ($i= 0 ; $i < $number_print_posts ; $i++) {
                                    $formCount++;
                                    $postData = $AllPosts[$i]; 
                                    $postUserData = db_getUserData($postData[7]);
                                    $postData[6] = urldecode($postData[6]);
                                    $postData[5] = urldecode($postData[5]);
                                    if($postData[4] > 0 && $postData[4] < 5){
                                        $postMediasSrc = db_getPostMedias($postData[0]);
                                    }                
                                    ?>
                                    <div class="post-container">
                                        <div class="user-profil">
                                            <img src="<?= $postUserData[9] ?>">
                                            <div>
                                                <p id = "userName_Post"><?= $postUserData[0] ?></p>
                                                <span><?= $postData[1] ?></span>
                                            </div>
                                        </div>
                                        <p class="post-text"><?= $postData[6] ?></p>
                                        <div class="post-media">
                                            <div class="post-images">
                                                <?php if($postData[4] > 0 && $postData[4] < 5) {
                                                    for($k = 0; $k < count($postMediasSrc); $k++){ ?>                        
                                                        <img src="<?= $postMediasSrc[$k] ?>" alt="Img Media <?=$k?>" class="post-img" 
                                                        <?php if($postData[4] == 1) { ?>
                                                            style="width: 200%; height:auto"
                                                        <?php } ?>
                                                        >
                                                    <?php } 
                                                } ?>
                                            </div>
                                            <div class="post-reactions" <?php if($postData[4] == 0) echo 'style="flex-direction:row;"'?>>
                                                <div>
                                                    <ion-icon name="heart" onclick="LikePost('<?= $postData[0] ?>', this, <?=$formCount?>)"
                                                        <?php if(count(db_selectColumns("liked_post", ["*"], ["UserID" => ["LIKE", "'".$_SESSION["connected"]."'", "1"],
                                                                                                                "PostID" => ["LIKE", "'".$postData[0]."'", "0"]]))
                                                                    > 0) {
                                                                    ?> style = "color: red" <?php
                                                                    }
                                                        ?>
                                                    >
                                                    </ion-icon>
                                                    <small id="likeCount<?=$formCount?>"><?= $postData[2] ?></small>
                                                </div>
                                                <?php 
                                                    $postComments = db_selectColumns('comment', ['*'], ['ReplyTo_PostID' => ['=', "'".$postData[0]."'", '0']]);
                                                    $nbComments = count($postComments);                            
                                                ?>
                                                <div>
                                                    <ion-icon id="CommentSection<?=$postData[0]?>" name="chatbox-ellipses" onclick="CommentSectionCall(this.id)"></ion-icon>
                                                    <small><?= $nbComments ?></small>
                                                </div>
                                                <!-- Comments Here-->
                                                <div>
                                                    <ion-icon name="share-social" onclick="shareSocial(this)"
                                                    <?php if(count(db_selectColumns("shared_post", ["*"], ["UserID" => ["LIKE", "'".$_SESSION["connected"]."'", "1"],
                                                                                                                "PostID" => ["LIKE", "'".$postData[0]."'", "0"]]))
                                                            > 0) {
                                                                ?> style = "color: blue" <?php
                                                            }
                                                    ?>>
                                                    </ion-icon>
                                                    <small><?= $postData[3] ?></small>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                <?php }
                                if(count($AllPosts) > POSTS_DISPLAYED){ ?>
                                    <input class="btn-loadMore" id="addMorePostAllPost" type="button" onclick="displayMorePosts(<?= POSTS_DISPLAYED ?>, <?= POSTS_TO_PRINT ?>, '<?= $AllPosts[0][1] ?>'  ,'prof_all', '<?= $vieweduserData[0] ?>', <?= 3*POSTS_DISPLAYED+1 ?>, <?= $toLoad ?>)" value="Load more">
                                <?php }  
                            } else { 
                                echo "<span>".$who." never posted anything yet"."</span>";
                            }?>
                        </div>
                        <div id="content2" style="display:none;">
                            <?php
                                if(count($LikedPostsId) > 0) {
                                    $number_print_posts = min(count($LikedPostsId), POSTS_DISPLAYED);
                                    for ($i=0; $i < $number_print_posts; $i++) { 
                                        
                                        $formCount++;
                                        $postData = db_selectColumns("post", ["*"], ["PostID"=> ["LIKE", "'".$LikedPostsId[$i][0]."'", "0"]])[0] ;
                                        if($i == 0)
                                            $likedFirstDateTime = $postData[1];
                                        $postUserData = db_getUserData($postData[7]);
                                        $postData[6] = urldecode($postData[6]);
                                        $postData[5] = urldecode($postData[5]);
                                        if($postData[4] > 0 && $postData[4] < 5){
                                            $postMediasSrc = db_getPostMedias($postData[0]);
                                        }                
                                        ?>
                                        <div class="post-container">
                                            <div class="user-profil">
                                                <img src="<?= $postUserData[9] ?>">
                                                <div>
                                                    <p id = "userName_Post"><?= $postUserData[0] ?></p>
                                                    <span><?= $postData[1] ?></span>
                                                </div>
                                            </div>
                                            <p class="post-text"><?= $postData[6] ?></p>
                                            <div class="post-media">
                                                <div class="post-images">
                                                    <?php if($postData[4] > 0 && $postData[4] < 5) {
                                                        for($k = 0; $k < count($postMediasSrc); $k++){ ?>                        
                                                            <img src="<?= $postMediasSrc[$k] ?>" alt="Img Media <?=$k?>" class="post-img" 
                                                            <?php if($postData[4] == 1) { ?>
                                                                style="width: 200%; height:auto"
                                                            <?php } ?>
                                                            >
                                                        <?php } 
                                                    } ?>
                                                </div>
                                                <div class="post-reactions" <?php if($postData[4] == 0) echo 'style="flex-direction:row;"'?>>
                                                    <div>
                                                        <ion-icon name="heart" onclick="LikePost('<?= $postData[0] ?>', this, <?=$formCount?>)"
                                                            <?php if(count(db_selectColumns("liked_post", ["*"], ["UserID" => ["LIKE", "'".$_SESSION["connected"]."'", "1"],
                                                                                                                "PostID" => ["LIKE", "'".$postData[0]."'", "0"]]))
                                                                    > 0) {
                                                                        ?> style = "color: red" <?php
                                                                    }
                                                            ?>
                                                        >
                                                        </ion-icon>
                                                        <small id="likeCount<?=$formCount?>"><?= $postData[2] ?></small>
                                                    </div>
                                                    <?php 
                                                        $postComments = db_selectColumns('comment', ['*'], ['ReplyTo_PostID' => ['=', "'".$postData[0]."'", '0']]);
                                                        $nbComments = count($postComments);                            
                                                    ?>
                                                    <div>
                                                        <ion-icon id="CommentSection<?=$postData[0]?>" name="chatbox-ellipses" onclick="CommentSectionCall(this.id)"></ion-icon>
                                                        <small><?= $nbComments ?></small>
                                                    </div>
                                                                                                
                                                    <div>
                                                        <ion-icon name="share-social" onclick="shareSocial(this)"
                                                        <?php if(count(db_selectColumns("shared_post", ["*"], ["UserID" => ["LIKE", "'".$_SESSION["connected"]."'", "1"],
                                                                                                                "PostID" => ["LIKE", "'".$postData[0]."'", "0"]]))
                                                                > 0) {
                                                                    ?> style = "color: blue" <?php
                                                                }
                                                        ?>>
                                                        </ion-icon>
                                                        <small><?= $postData[3] ?></small>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    <?php }
                                if(count($LikedPostsId) > POSTS_DISPLAYED){ ?>
                                    <input class="btn-loadMore" id="addMorePostLikedPost" type="button" onclick="displayMorePosts(<?= POSTS_DISPLAYED ?>, <?= POSTS_TO_PRINT ?>,'<?= $likedFirstDateTime ?>' ,'prof_liked', '<?= $vieweduserData[0] ?>', <?= 3*POSTS_DISPLAYED+1 ?>, <?= $toLoad ?>)" value="Load more">
                                <?php } 
                            } else { 
                                echo "<span>".$who." never liked any post yet"."</span>";
                            }?>
                        </div>
                        <div id="content3" style="display:none;">
                            <?php
                                if(count($SharedPostsId) > 0) {
                                    $number_print_posts = min(count($SharedPostsId), POSTS_DISPLAYED);
                                    for ($i=0; $i < $number_print_posts; $i++) { 
                                        
                                        $formCount++;
                                        $postData = db_selectColumns("post", ["*"], ["PostID"=> ["LIKE", "'".$SharedPostsId[$i][0]."'", "0"]])[0] ;
                                        if($i == 0)
                                            $sharedFirstDateTime = $postData[1];
                                        $postUserData = db_getUserData($postData[7]);
                                        $postData[6] = urldecode($postData[6]);
                                        $postData[5] = urldecode($postData[5]);
                                        if($postData[4] > 0 && $postData[4] < 5){
                                            $postMediasSrc = db_getPostMedias($postData[0]);
                                        }                
                                        ?>
                                        <div class="post-container">
                                            <div class="user-profil">
                                                <img src="<?= $postUserData[9] ?>">
                                                <div>
                                                    <p id = "userName_Post"><?= $postUserData[0] ?></p>
                                                    <span><?= $postData[1] ?></span>
                                                </div>
                                            </div>
                                            <p class="post-text"><?= $postData[6] ?></p>
                                            <div class="post-media">
                                                <div class="post-images">
                                                    <?php if($postData[4] > 0 && $postData[4] < 5) {
                                                        for($k = 0; $k < count($postMediasSrc); $k++){ ?>                        
                                                            <img src="<?= $postMediasSrc[$k] ?>" alt="Img Media <?=$k?>" class="post-img" 
                                                            <?php if($postData[4] == 1) { ?>
                                                                style="width: 200%; height:auto"
                                                            <?php } ?>
                                                            >
                                                        <?php } 
                                                    } ?>
                                                </div>
                                                <div class="post-reactions" <?php if($postData[4] == 0) echo 'style="flex-direction:row;"'?>>
                                                    <div>
                                                        <ion-icon name="heart" onclick="LikePost('<?= $postData[0] ?>', this, <?=$formCount?>)"
                                                            <?php if(count(db_selectColumns("liked_post", ["*"], ["UserID" => ["LIKE", "'".$_SESSION["connected"]."'", "1"],
                                                                                                                "PostID" => ["LIKE", "'".$postData[0]."'", "0"]]))
                                                                    > 0) {
                                                                        ?> style = "color: red" <?php
                                                                    }
                                                            ?>
                                                        >
                                                        </ion-icon>
                                                        <small id="likeCount<?=$formCount?>"><?= $postData[2] ?></small>
                                                    </div>
                                                    <?php 
                                                        $postComments = db_selectColumns('comment', ['*'], ['ReplyTo_PostID' => ['=', "'".$postData[0]."'", '0']]);
                                                        $nbComments = count($postComments);                            
                                                    ?>
                                                    <div>
                                                        <ion-icon id="CommentSection<?=$postData[0]?>" name="chatbox-ellipses" onclick="CommentSectionCall(this.id)"></ion-icon>
                                                        <small><?= $nbComments ?></small>
                                                    </div>
                                                    <!-- Comment here -->
                                                    <div>
                                                        <ion-icon name="share-social" onclick="shareSocial(this)"
                                                        <?php if(count(db_selectColumns("shared_post", ["*"], ["UserID" => ["LIKE", "'".$_SESSION["connected"]."'", "1"],
                                                                                                                "PostID" => ["LIKE", "'".$postData[0]."'", "0"]]))
                                                                > 0) {
                                                                    ?> style = "color: blue" <?php
                                                                }
                                                        ?>>
                                                        </ion-icon>
                                                        <small><?= $postData[3] ?></small>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    <?php }
                                if(count($SharedPostsId) > POSTS_DISPLAYED){ ?>
                                    <input class="btn-loadMore" id="addMorePostSharedPost" type="button" onclick="displayMorePosts(<?= POSTS_DISPLAYED ?>, <?= POSTS_TO_PRINT ?>,'<?= $sharedFirstDateTime ?>', 'prof_shared', '<?= $vieweduserData[0] ?>', <?= 3*POSTS_DISPLAYED+1 ?>, <?= $toLoad ?>)" value="Load more">
                                <?php }  
                            } else { 
                                echo "<span>".$who." never shared any post yet"."</span>";
                            }?> 
                        </div>
                    </div>  
                </div>
            </div>
            <!-- Right Content -->
            <?php 
                if($vieweduser_id == $_SESSION['connected'])
                    define('CONVERSIONABLE','1');          
                $friends_id = db_getFriends($vieweduser_id);
                define('ARRAYFRIEND','1');
                $onclickfct = 'submitFormProfilLink';
                include_once(LISTFRIEND);
            ?>    
            

        </div>
        </main>
        <?php include_once(FOOTER); ?>
    </body>
    <script type="text/javascript" src="./js/profil.js"></script>
    <script type="text/javascript" src="./js/post.js"></script>
    <script src="https://html2canvas.hertzen.com/dist/html2canvas.min.js"></script>

</html>
