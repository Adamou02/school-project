<?php
    if(file_exists("./required.php"))
        require_once("./required.php");
    else
        require_once("./php/required.php");
    require_once(M_FORMS);
    
    
    if(isset($_POST["submitRegistration"]))
    {
        $errorNumber = checkingForm("registration", $_POST);
        if($errorNumber === 0)
        {
            $tabDataForm = $_POST;
                switch($tabDataForm["sex"]){
                    case "Man" :
                        $tabDataForm["sex"] = 1;
                        break;
                    case "Woman" :
                        $tabDataForm["sex"] = 0;
                        break;
                    case "Other" :
                        $tabDataForm["sex"] = 2;
                        break;
                    default :
                        $tabDataForm["sex"] = -1;
                        break;
                }

                $passwordHash = password_hash($tabDataForm["password"], PASSWORD_DEFAULT);
                $newUserTab = array("Username" => $tabDataForm["userName"],
                                    "Name" => $tabDataForm["name"],
                                    "Firstname" => $tabDataForm["firstName"],                                    
                                    "Sex" => $tabDataForm["sex"],
                                    "BirthDate" => $tabDataForm["birthDate"],
                                    "Mail" => $tabDataForm["mail"],
                                    "Country" => $tabDataForm["country"],
                                    "City" => $tabDataForm["city"],
                                    "PhoneNumber" => $tabDataForm["phoneNumber"],
                                );                
                $dbUser = db_newUser($newUserTab, $passwordHash);
                if($dbUser != 1) {
                    switch ($dbUser) {
                        case 'mail':
                            $err = "This email address is already taken."; break;
                        case 'userName':
                            $err = "This username is already taken."; break;
                        default : $err = "erreur"; break;
                    }                    
                    unset($_SESSION["errorMessageRegistration"]);
                    $_SESSION['errorMessageRegistration'][$dbUser] = $err;
                    $_SESSION['error'] = "true";
                    redirect(ROOT.ACCOUNT);
                }
                
                s_connect(db_selectColumns('user', ['UserID'], ['Username' => ['=', "'".$tabDataForm["userName"]."'", "0"]])[0][0]);
                redirect(ROOT.INDEX);
        }
        else
        {
            $_SESSION['error'] = "true";
            redirect(ROOT.ACCOUNT);
        }
    }
    else
    {
        $_SESSION['errorMessageRegistration']['submitRegistration'] = "Please fill out your registration form completely.";
        $_SESSION['error'] = "true";
        redirect(ROOT.ACCOUNT);
    }
?>
