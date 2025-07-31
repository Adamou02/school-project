
<link rel="stylesheet" href="css/listFriend.css">

<div class="right-content">
    <?php 
        if(!defined('ARRAYFRIEND')) {
            $friends_id = db_getFriends($_SESSION['connected']);
            $onclickfct = 'submitFormProfilLink';
        }
        if(is_string($friends_id[0])) {
            for($j = 0; $j <count($friends_id); $j++) {
                $friends_id[$j] = array($friends_id[$j]);
            } 
        }
    ?>
    <div id="list_friend" class="close-friends">
        <?php  
            if(count($friends_id) != 0) {
                if(defined('ARRAYFRIEND') && !defined('CONVERSIONABLE') && isset($vieweduser_id)) {
                    ?><b><?=$vieweduserData[0]?>'s Friends</b><?php 
                } else {
                        ?><b>Your Friends</b><?php 
                }
            }
       
            for ($i=0; $i < count($friends_id); $i++) { 
                $friendData = db_getUserData($friends_id[$i][0]);
        ?>
        <!-- FRIEND LISTE -->
        <div class="close-f friends_list  
            <?php  
            $compteurform;
            if(!defined('SELECTEDFRIEND')) {
                if($i==0){ echo 'selected_friends'; }
                } else if($friendData[0] == $last_communicate_friend[0]) { echo 'selected_friends'; }
            ?>"
            id="user<?=$i?>" <?php if(!defined('CONVERSIONABLE')) {  ?>onclick='<?php echo $onclickfct ?>(<?=$i?>);'<?php ; } ?>
        >  
            <div class="friend-profil-link"  onclick='<?php echo $onclickfct ?>(<?=$i?>);'>
                <img src="<?= $friendData[9] ?>" <?php if( $onclickfct == 'selectDiscussion'){echo "onclick = 'submitFormProfilLink($i)'";}?>>
                <div>
                     <p id="pseudo-close-f-display<?=$i?>" class="userName<?=$i?>"><?= $friendData[0] ?></p>
                </div>
                <form id="form-profil-link<?=$i?>" method="GET" action="<?= PROFIL ?>">
                    <input type="hidden" name="user" id="user<?=$i?>" value="<?= $friendData[0] ?>">
                </form>
            </div>
            <div class="close-message">
                <!-- Converser avec un ami -->
                <?php  if(defined('CONVERSIONABLE')) { ?>
                <ion-icon name="paper-plane" onclick = 'submitFormConvLink(<?=$i?>)'>
                    <form id="form-conversation-link<?=$i?>" method="GET" action="<?= CONVERSATION ?>">
                        <input type="hidden" name="user_conv" value="<?= $friendData[0] ?>">
                    </form>
                </ion-icon>
                <?php } ?>
                <?php  if(defined('TRASHABLE')) { ?>
                <ion-icon name="trash" onclick="delete_friend(<?=$i?>)"></ion-icon>
                <!-- Supprimer un ami -->
                <form id="form-delete-friend<?=$i?>" action="<?= PHP.SETTINGS_PRO ?>" method="post">
                    <input type="hidden" name="friendDelete_username" id="friendDelete_username" value="<?= $friendData[0]?>">
                    <input type="hidden" name="userDelete_username" id="userDelete_username" value="<?= $userData[0]?>">
                </form>
                <?php }  ?>
            </div>
        </div>
        <?php $compteurform = $i; } ?>
        <!-- FRIEND REQUEST -->
        <?php 
            $friend_requests = db_getFriendRequest($_SESSION['connected']);
            if(defined('CONVERSIONABLE') && count($friend_requests) > 0) { 
        ?>
        <b>Friend Requests</b>
        <div id="div_friend_requests" class="close-friends">
            <?php 
               
                for ($i=0; $i < count($friend_requests) ; $i++) {
                    $compteurform++;
                    $friendReqData = db_getUserData($friend_requests[$i][0]);
                    ?>
                    <div class="close-f">
                        <div class="friend-profil-link" onclick="submitFormProfilLink(<?=$compteurform?>)">
                            <img src='<?= $friendReqData[9]?>'></img>
                            <span id='friend_req<?= $friendReqData[0]?>'><?= $friendReqData[0]?></span>
                        </div>
                        <div class="friend-req-buttons">
                            <ion-icon name="checkmark" onclick="submitFormAcceptFReq(<?=$compteurform?>)"></ion-icon>
                            <ion-icon name="close-outline" onclick="submitFormCancelFReq(<?=$compteurform?>)"></ion-icon>
                            <form id="form-profil-link<?=$compteurform?>" method="GET" action="<?= PROFIL ?>">
                                <input type="hidden" name="user" id="user<?=$i?>" value="<?= $friendReqData[0] ?>">
                            </form>
                            <form id="form-f-req-accept<?=$compteurform?>" method="POST" action="<?= PHP.FRIEND_PRO ?>">
                                <input type="hidden" name="UsernameFuturFriend" id="user<?=$compteurform?>" value="<?= $friendReqData[0] ?>">
                            </form>
                            <form id="form-f-req-cancel<?=$compteurform?>" method="POST" action="<?= PHP.FRIEND_PRO ?>">
                                <input type="hidden" name="UsernameCancelRequest" id="user<?=$compteurform?>" value="<?= $friendReqData[0] ?>">
                            </form>
                        </div>
                    </div>
                    <?php
                }
            ?>
        </div>
    <?php } ?>
    </div>
    
   
</div>
