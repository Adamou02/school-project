<?php
   
    if(file_exists("./required.php"))
        require_once("./required.php");
    else
        require_once("./php/required.php");
    if(isset($_POST)) {
        $tabdataform = $_POST;
        if(isset($tabdataform["srcPP_base64"]) && isset($tabdataform["srcPP_type"]) && isset($tabdataform["srcPP_username"]) ) {
            $PPid = db_selectColumns("user", ["ProfilPic"], ["Username" => ["LIKE", "'".$tabdataform["srcPP_username"]."'", "0"]])[0][0];
            if($PPid == 'M0'){
                $NewID = db_generateID("media");
                db_newRow("media", ["MediaID" => $NewID, "Base64" => $tabdataform["srcPP_base64"], "Type" => $tabdataform["srcPP_type"]]);
                db_updateColumns("user", ["ProfilPic" => $NewID], ["UserID" => ["LIKE", "'".$_SESSION['connected']."'","0"]]);
                echo "<script> window.location.replace('".ROOT.SETTINGS."') </script>";
                redirect(ROOT.ACCOUNT);
            }
            else{
                db_updateColumns("media", ["Base64" => $tabdataform["srcPP_base64"], "Type" => $tabdataform["srcPP_type"]], ["MediaID" => ["LIKE", "'".$PPid."'", "0"]]);
                echo "<script> window.location.replace('".ROOT.SETTINGS."') </script>";
                redirect(ROOT.ACCOUNT);
            }
        } 
        else if (
            isset($tabdataform["userName"]) && isset($tabdataform["name"]) && isset($tabdataform["firstName"]) && 
            ((isset($tabdataform["sex"]) && $tabdataform["sex"] === "Man") || 
            (isset($tabdataform["sex"]) && $tabdataform["sex"] === "Woman") || 
            (isset($tabdataform["sex"]) && $tabdataform["sex"] === "Other")) && 
            isset($tabdataform["birthDate"]) && isset($tabdataform["mail"]) && isset($tabdataform["country"]) && 
            isset($tabdataform["city"]) && isset($tabdataform["phoneNumber"])
        ){
            $User_id = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["src_username"]."'", "0"]])[0][0];
            switch ($tabdataform["sex"]) {
                case 'Man':
                    $Sex = '1';
                    break;
                case 'Woman':
                    $Sex = '0';
                    break;
                case 'Other':
                    $Sex = '2';
                    break;
                default:
                    $Sex = '2';
                    break;
            }
            db_updateColumns("user", ["Username" => $tabdataform["userName"], "Name" => $tabdataform["name"], "Firstname" => $tabdataform["firstName"], 
            "Mail" => $tabdataform["mail"], "Country" => $tabdataform["country"], "City" => $tabdataform["city"], 
            "BirthDate" => $tabdataform["birthDate"], "PhoneNumber" => $tabdataform["phoneNumber"], "Sex" => $Sex], ["UserID" => ["LIKE", "'".$User_id."'", "0"]]);
        }
        else if (isset($tabdataform["password"]) && isset($tabdataform["srcPass_username"])){
            $passwordHash = password_hash($tabdataform["password"], PASSWORD_DEFAULT);
            $User_id_pass = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["srcPass_username"]."'", "0"]])[0][0];
            db_updateColumns("password", ["EncrPwd" => $passwordHash], ["UserID" => ["LIKE", "'".$User_id_pass."'", "0"]]);
        }
        else if (isset($tabdataform["themeSelect"]) && isset($tabdataform["srcTheme_username"])){
            $User_id_theme = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["srcTheme_username"]."'", "0"]])[0][0];
            db_updateColumns("user", ["Theme" => $tabdataform["themeSelect"]], ["UserID" => ["LIKE", "'".$User_id_theme."'", "0"]]);
            if($tabdataform["themeSelect"] == "1") {
                $_SESSION['DarkMode'] = "Unable";
            } else {
                $_SESSION['DarkMode'] = "Disable";
            }
        }
        else if ((isset($tabdataform["profilePrivacy"]) || isset($tabdataform["postPrivacy"])) && isset($tabdataform["srcPrivacy_username"])){
            $User_id_privacy = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["srcPrivacy_username"]."'", "0"]])[0][0];
            if (isset($tabdataform["profilePrivacy"])){
                db_updateColumns("user", ["ProfilConfidentiality" => $tabdataform["profilePrivacy"]], ["UserID" => ["LIKE", "'".$User_id_privacy."'", "0"]]);
            }
            if (isset($tabdataform["postPrivacy"])){
                db_updateColumns("user", ["PostConfidentiality" => $tabdataform["postPrivacy"]], ["UserID" => ["LIKE", "'".$User_id_privacy."'", "0"]]);
            }
        }
        else if (isset($tabdataform["srcDelete_username"])){
            $User_id_delete = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["srcDelete_username"]."'", "0"]])[0][0];
            db_deleteRows("user", ["UserID" => ["LIKE", "'".$User_id_delete."'", "0"]]);
            echo "<script> window.location.replace('".ROOT.SETTINGS."') </script>";
            redirect(ROOT.ACCOUNT);
        }
        else if (isset($tabdataform["friendDelete_username"]) && isset($tabdataform["userDelete_username"])){
            $User_id_friend = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["friendDelete_username"]."'", "0"]])[0][0];
            $User_id_user = db_selectColumns("user", ["UserID"], ["Username" => ["LIKE", "'".$tabdataform["userDelete_username"]."'", "0"]])[0][0];
            $int_friend = preg_replace('/[^0-9]/', '', $User_id_friend);
            $int_user = preg_replace('/[^0-9]/', '', $User_id_user);
            if(intval($int_user) < intval($int_friend)){
                db_deleteRows("friends", ["UserID_1" => ["LIKE", "'".$User_id_user."'", "1"], "UserID_2" => ["LIKE", "'".$User_id_friend."'", "0"]]);
            }
            else{
                db_deleteRows("friends", ["UserID_1" => ["LIKE", "'".$User_id_friend."'", "1"], "UserID_2" => ["LIKE", "'".$User_id_user."'", "0"]]);
            }
        }
    }
    echo "<script> window.location.replace('".ROOT.SETTINGS."') </script>";
    redirect(ROOT.SETTINGS);
?>