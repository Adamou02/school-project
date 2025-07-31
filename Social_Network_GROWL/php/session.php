<?php
     define('SESSION_INCLUDED','1');
     if(file_exists("./required.php"))
       require_once("./required.php");
     else
       require_once("./php/required.php");
   

    function s_isConnected(){
        return isset($_SESSION['connected']);
    }

    function s_disconnect() {
        if(s_isConnected()) { //si l'utilisateur est connecté, on le déconnecte
            unset($_SESSION['connected']);
        }
    }

    function s_connect(string $userID) { //connecte l'utilisateur
        s_disconnect();
        $_SESSION['connected'] = $userID; 
    }    

    if(isset($_GET["action"]) && $_GET["action"] === "disconnection") {
        s_disconnect();
        redirect(ROOT.INDEX);
    }
    
?> 