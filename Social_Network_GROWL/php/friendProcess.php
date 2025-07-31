<?php
   
    if(file_exists("./required.php"))
        require_once("./required.php");
    else
        require_once("./php/required.php");
    
    
    if(isset($_POST)) {
        $tabdataform = $_POST;
        /*ACCEPT A FRIEND REQUEST*/
        if(isset($tabdataform["UsernameFuturFriend"]) && isset($_SESSION["connected"])) { 
            $FFid = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["UsernameFuturFriend"]."'", "0"]])[0][0];
            if(in_array(array($FFid), db_getFriendRequest($_SESSION["connected"]))) //double check that there is a Friend Request of this user
                db_updateColumns("friends", ["Accepted" => '1'], ["UserID_1" => ["LIKE", "'".$FFid."'", "1"], "UserID_2" => ["LIKE", "'".$_SESSION["connected"]."'", "0"] ]);
        }
        /* CANCEL A FRIEND REQUEST*/
        if(isset($tabdataform["UsernameCancelRequest"]) && isset($_SESSION["connected"])) { 
            $FFid = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["UsernameCancelRequest"]."'", "0"]])[0][0];
            if(in_array(array($FFid), db_getFriendRequest($_SESSION["connected"]))) //double check that there is a Friend Request of this user
                db_deleteRows("friends", ["UserID_1" => ["LIKE", "'".$FFid."'", "1"], "UserID_2" => ["LIKE", "'".$_SESSION["connected"]."'", "0"] ]);
        }
        /*SEND A FRIEND REQUEST*/ 
        if(isset($tabdataform["SendReqUser"]) && isset($_SESSION["connected"])) {
            $SUid = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["SendReqUser"]."'", "0"]])[0][0];
            if( 
                //CHECK That there is not already a friend request for these 2 futur friend or that there are not already friend
                !in_array(array($SUid), db_getFriendRequest($_SESSION["connected"])) 
                && !in_array(array($_SESSION["connected"]), db_getFriendRequest($SUid))
                &&  !in_array(array($SUid), db_getFriends($_SESSION["connected"])) 
            ) {
                db_newRow('friends', ["UserID_1" => $_SESSION["connected"], "UserID_2" => $SUid, "Accepted" => '0']);
            }
            redirect(ROOT.PROFIL."?user=".$tabdataform["SendReqUser"]);
        }
        
    } 
    redirect(ROOT.INDEX);
    
?>
