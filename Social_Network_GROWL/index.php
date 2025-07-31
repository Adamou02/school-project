<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home | GROWL</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css">
    <link rel="icon" type="image/ico" href="./images/growl_ico.ico">
    <link rel="stylesheet" href="css/index.css">
</head>

<body>

    <?php 
          require_once("./php/constant.php");
          include_once(HEADER);
    ?>

    <main>
        <!-- Left Content -->
        <?php include_once(ASIDE); ?>
        <!-- Middle Content -->

        <div class="middle-content">
            <div class="write-post">
                <div class="user-profil">
                    <img src="<?= $userData[9] ?>">
                    <div>
                        <p><?= $userData[0] ?></p>
                        <small><?php echo date('Y-m-d')." , ".$userData[5] ?></small>
                    </div>
                </div>
                <form method="post" name="new-post-form" onsubmit="return checkPost()" action="<?= PHP.POST_PRO ?>">

                    <div class="post-input">
                        <div class="content-input">
                            <input class="text-area" type="textarea" name="text_input"
                                placeholder="What do you want to tell about today ?" />

                            <div class="add-post">
                                <div id="new-post-images">

                                </div>
                            </div>
                            <div class="bottom-input">
                                <div> <input type="file" name="picture" id="hiddenfile" onchange="previewPicture(this)"style="display:none" multiple>
                                <ion-icon name='camera' onclick="getfile()"></ion-icon>Add Photos/Videos</div>
                                <input id="submit-post" type="submit" value="Submit" class="submit-post" name ="isPost"/>
                                </div>
                            </div>
                        <p id="error-size-image"></p>
                    </div>
                </form>
            </div>
            <!-- Posts -->
            <?php 
            if (isset($_GET['searchBar'])){
                $posts = db_selectColumns("post", ["*"], ["KeyWords" => ["LIKE", "'%".$_GET['searchBar']."%'", "0"]], order_by:["Posted_DateTime"], suffix:" DESC"); // changer ici pour la politique de confidentialité des posts
                $toLoad = $_GET['searchBar'];
            }else{
                $posts = db_selectColumns('post', ['*'], order_by:["Posted_DateTime"], suffix:" DESC"); // changer ici pour la politique de confidentialité des posts
                $toLoad = null;
            }
                $maxDateTime = $posts[0][1];
                $number_print_posts = min(count($posts), POSTS_DISPLAYED);
                for ($i= 0 ; $i < $number_print_posts ; $i++) {
                    $postData = $posts[$i]; 
                    $postUserData = db_getUserData($postData[7]);
                    $postData[6] = urldecode($postData[6]);
                    $postData[5] = urldecode($postData[5]);
                    if($postData[4] > 0 && $postData[4] < 5){
                        $postMediasSrc = db_getPostMedias($postData[0]);
                    }   
                    if($postData[7] != $_SESSION['connected']){
                        if($postUserData[11] == 1 && !in_array(array($_SESSION['connected']), db_getFriends($postData[7]))){
                            $i++;
                            if($i < $number_print_posts){
                                $postData = $posts[$i]; 
                                $postUserData = db_getUserData($postData[7]);
                                $postData[6] = urldecode($postData[6]);
                                $postData[5] = urldecode($postData[5]);
                                if($postData[4] > 0 && $postData[4] < 5){
                                    $postMediasSrc = db_getPostMedias($postData[0]);
                                } 
                            } else {
                                break;
                            }
                        }
                        if($postUserData[11] == 0 ) {
                            $i++;
                            if($i < $number_print_posts){
                                $postData = $posts[$i]; 
                                $postUserData = db_getUserData($postData[7]);
                                $postData[6] = urldecode($postData[6]);
                                $postData[5] = urldecode($postData[5]);
                                if($postData[4] > 0 && $postData[4] < 5){
                                    $postMediasSrc = db_getPostMedias($postData[0]);
                                } 
                            } else {
                                break;
                            }
                        }
                    }
            ?>
            <div class="post-container <?php if(isset($_SESSION['postCreated']) && $_SESSION['postCreated'] == $postData[0]) { echo 'just-created-post'; unset($_SESSION['postCreated']);} ?>">
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
                            <ion-icon name="heart" onclick="LikePost('<?= $postData[0] ?>', this, <?=$i?>)"
                                <?php if(count(db_selectColumns("liked_post", ["*"], ["UserID" => ["LIKE", "'".$_SESSION["connected"]."'", "1"],
                                                                                    "PostID" => ["LIKE", "'".$postData[0]."'", "0"]]))
                                        > 0) {
                                            ?> style = "color: red" <?php
                                        }
                                ?>
                            >
                            </ion-icon>
                            <small id="likeCount<?=$i?>"><?= $postData[2] ?></small>
                        </div>
                        <?php 
                            $postComments = db_selectColumns('comment', ['*'], ['ReplyTo_PostID' => ['=', "'".$postData[0]."'", '0']]);
                            $nbComments = count($postComments);                            
                        ?>
                    <div>
                            <ion-icon id="CommentSection<?=$postData[0]?>" name="chatbox-ellipses" onclick="CommentSectionCall(this.id)"></ion-icon>
                            <small><?= $nbComments ?></small>
                        </div>
                        <!-- Comments. Ils sont générés en ajax ici -->
                        
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
            if(count($posts) > POSTS_DISPLAYED){ ?>
                <input class="btn-loadMore" id="addMorePost" type="button" onclick="displayMorePosts(<?= POSTS_DISPLAYED ?>, <?= POSTS_TO_PRINT ?>,'<?= $maxDateTime ?>', 'index', '<?= $userData[0] ?>' , <?= $number_print_posts ?>, <?= $toLoad ?>)" value="Load more">
            <?php }  ?>
        </div>
        
        <!-- Right Content -->
        <?php define('CONVERSIONABLE','1'); 
        include_once(LISTFRIEND); ?>
        
    </main>
    <?php include_once(FOOTER); ?>
</body>
<script rel="stylesheet" src="js/index.js"></script>
<script rel="stylesheet" src="js/post.js"></script>
<script src="https://html2canvas.hertzen.com/dist/html2canvas.min.js"></script>
</html>
