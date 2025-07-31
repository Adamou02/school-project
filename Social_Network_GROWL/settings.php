<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Settings | GROWL</title>
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css">
        <link rel="stylesheet" href="css/settings.css">
        <link rel="icon" type="image/ico" href="./images/growl_ico.ico">
    </head>

    <body>
        <?php 
            require_once("./php/constant.php");
            include_once(HEADER);
            if(!s_isConnected()){
                redirect(ACCOUNT);
            }
        ?>
        <script rel="stylesheet" src="js/header.js"></script>
        <?php 
        session_start();
        if(!empty($_SESSION['errorMessageRegistration']))
        {   
            $tabErrorMessage = [];
            foreach($_SESSION['errorMessageRegistration'] as $errorKey => $error) {
                $tabErrorMessage[$errorKey] = $error;
            }
            unset($_SESSION['errorMessageRegistration']);
        }

        if(!empty($_SESSION["correctInputRegistration"]))
        {
            $tabCorrectInput = [];
            foreach($_SESSION['correctInputRegistration'] as $inputName => $input) {
                $tabCorrectInput[$inputName] = $input;
            }
            unset($_SESSION["correctInputRegistration"]);
        }
        if(!empty($_SESSION['errorMessageLogin']))
        {
            $tab_errorMessage_log = [];
            foreach($_SESSION['errorMessageLogin'] as $errorKey => $error) {
                $tab_errorMessage_log[$errorKey] = $error;
            }
            unset($_SESSION['errorMessageLogin']);
        }
        ?>

        <div class="main">
            <!-- Left Content -->
            <?php include_once(ASIDE); ?>
            <script rel="stylesheet" src="js/aside.js"></script>
            <!-- Middle Content -->
            <div class="middle-content">
                <!--Section modification profil (username, photo de profil,  name, prénom, sexe, date de naissance, mail, password, pays, ville, telephone) -->
                <div class="settings-list" id="profile" name="Closed">
                    <ion-icon name="person-circle-outline"></ion-icon> Profile Settings<div class="menu-arrow"><ion-icon id="menu-arrow-profile" name="chevron-forward-outline"></ion-icon></div>
                </div>
                <div class="profile-disclosed">
                    <?php 
                        $user = db_getUserData($_SESSION['connected']);
                    ?>
                    <div class="settings-styles">
                        <form  id="form-registration" onsubmit="return (checkingForm('registration'))" action="<?= PHP.SETTINGS_PRO ?>" method="post">
                        <input type="hidden" name="src_username" id="src_username" value="<?= $userData[0]?>">
                        <div class="formulaire">
                            <table>
                                <tr>
                                    <td>
                                        <div class="input_label">
                                            <label for="userName">Username</label><br>
                                            <input type="text" name="userName" id="userName" size="32" value="<?php echo $user[0];?>">
                                            <p id="errorMessage-registration-userName" class="errorMessage"><?php if(isset($tabErrorMessage["userName"])){echo $tabErrorMessage["userName"];}else{echo "";} ?></p>
                                        </div> 
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <div class="input_label">
                                            <label for="name">Last Name</label><br>
                                            <input type="text" name="name" id="name" size="32" value="<?php echo $user[1];?>">
                                            <p id="errorMessage-registration-name" class="errorMessage"><?php if(isset($tabErrorMessage["name"])){echo $tabErrorMessage["name"];}else{echo "";} ?></p>
                                        </div> 
                                    </td>
                                    <td>
                                        <div class="input_label">
                                            <label for="firstName">First Name</label><br>
                                            <input type="text" name="firstName" id="firstName" size="32" value="<?php echo $user[2];?>">
                                            <p id="errorMessage-registration-firstName" class="errorMessage"><?php if(isset($tabErrorMessage["firstName"])){echo $tabErrorMessage["firstName"];}else{echo "";} ?></p>
                                        </div>
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <div class="input_label">
                                            <label for="sexChoice">Sex</label> 
                                            <div id="sexChoice">
                                                <input type="radio" id="sexMan" <?php if($user[8] == 1){echo "checked";}?> name="sex" value="Man" <?php if(isset($tabCorrectInput["sex"]) && $tabCorrectInput["sex"] === "Man"){echo "checked";}else{echo "";} ?>>
                                                <label for="sexMan">Man</label>
                                                <br>
                                                <input type="radio" id="sexWoman" <?php if($user[8] == 0){echo "checked";}?> name="sex" value="Woman" <?php if(isset($tabCorrectInput["sex"]) && $tabCorrectInput["sex"] === "Woman"){echo "checked";}else{echo "";} ?>>
                                                <label for="sexWoman">Woman</label>
                                                <br>
                                                <input type="radio" id="sexOther" <?php if($user[8] == 2){echo "checked";}?> name="sex" value="Other" <?php if(isset($tabCorrectInput["sex"]) && $tabCorrectInput["sex"] === "Other"){echo "checked";}else{echo "";} ?>>
                                                <label for="sexOther">Other</label>
                                            </div>  
                                            <p id="errorMessage-registration-sex" class="errorMessage"><?php if(isset($tabErrorMessage["sex"])){echo $tabErrorMessage["sex"];}else{echo "";} ?></p>
                                        </div>
                                    </td>
                                    <td>
                                        <div class="input_label">
                                            <label for="birthDate">Birth Date</label><br>
                                            <input type="date" name="birthDate" id="birthDate" value="<?php echo $user[6];?>">
                                            <p id="errorMessage-registration-birthDate" class="errorMessage"><?php if(isset($tabErrorMessage["birthDate"])){echo $tabErrorMessage["birthDate"];}else{echo "";} ?></p>
                                        </div>
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <div class="input_label">
                                            <label for="mail">Email Adress</label><br>
                                            <input type="email" name="mail" id="mail" size="25" value="<?php echo $user[3];?>">
                                            <p id="errorMessage-registration-mail" class="errorMessage"><?php if(isset($tabErrorMessage["mail"])){echo $tabErrorMessage["mail"];}else{echo "";} ?></p>
                                        </div>
                                    </td>
                                    <td>
                                        <div class="input_label">
                                            <label for="phoneNumber">Phone Number</label><br>
                                            <input type="tel" name="phoneNumber" id="phoneNumber" value="<?php echo $user[7];?>">
                                            <p id="errorMessage-registration-phoneNumber" class="errorMessage"><?php if(isset($tabErrorMessage["phoneNumber"])){echo $tabErrorMessage["phoneNumber"];}else{echo "";} ?></p>
                                        </div>
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <div class="input_label">
                                            <label for="country">Country</label><br>
                                            <input class="country" name="country" id="country" rows="3" value="<?php echo $user[4];?>">
                                            <p id="errorMessage-registration-country" class="errorMessage"><?php if(isset($tabErrorMessage["country"])){echo $tabErrorMessage["country"];}else{echo "";} ?></p>
                                        </div>
                                    </td>
                                    <td>
                                        <div class="input_label">
                                            <label for="city">City</label><br>
                                            <input type="text" name="city" id="city" value="<?php echo $user[5];?>">
                                            <p id="errorMessage-registration-city" class="errorMessage"><?php if(isset($tabErrorMessage["city"])){echo $tabErrorMessage["city"];}else{echo "";} ?></p>
                                        </div>
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <input type="submit" class="confirm" name="submitRegistration" value="Confirm changes">
                                    </td>    
                                    <td>
                                        <input type="reset" class="confirm" name="Reset" value="Cancel">
                                    </td>
                                </tr>
                            </table>
                        </div>
                        </form>
                    </div>
                    <div class="settings-styles">
                        <form method="post" name="profile_picture_update" id="profile_picture_update" action="<?= PHP.SETTINGS_PRO ?>">
                            <img id="profilePicture" src="<?= $userData[9]?>"><br>
                            <input type="file" accept=".png,.jpg" name="picture" id="hiddenfile" required onchange="previewPicture(this)">
                            <input type="hidden" name="srcPP_base64" id="srcPP_base64">
                            <input type="hidden" name="srcPP_type" id="srcPP_type">
                            <input type="hidden" name="srcPP_username" id="srcPP_username" value="<?= $userData[0]?>">
                            <!--<ion-icon name='camera' onclick="getfile()"></ion-icon>Add Photos/Videos -->
                            <input type="submit" name="submit_profile_picture_update" value="Submit" class="confirm" />
                        </form>
                    </div>
                </div>
                <!--Change Password-->
                <div class="settings-list" id="passwordChange" name="Closed">
                    <ion-icon name="lock-open-outline"></ion-icon> Change Password<div class="menu-arrow"><ion-icon id="menu-arrow-password" name="chevron-forward-outline"></ion-icon></div>
                </div>
                <div class="password-disclosed">
                    <div class="settings-styles">
                        <form  id="form-registration" onsubmit="return (checkingForm('registration'))" action="<?= PHP.SETTINGS_PRO ?>" method="post">
                        <div class="formulaire">
                            <input type="hidden" name="srcPass_username" id="srcPass_username" value="<?= $userData[0]?>">
                            <table>
                                <tr>
                                    <td>
                                        <div class="input_label">
                                            <label for="password">New Password</label><br>
                                            <input type="password" name="password" id="password" placeholder="New Password">
                                            <p id="errorMessage-registration-password" class="errorMessage"><?php if(isset($tabErrorMessage["password"])){echo $tabErrorMessage["password"];}else{echo "";} ?></p>
                                        </div>
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <input type="submit" class="confirm" name="submitRegistration" value="Confirm changes">
                                    </td>    
                                    <td>
                                        <input type="reset" class="confirm" name="Reset" value="Cancel">
                                    </td>
                                </tr>
                            </table>
                        </div>
                        </form>
                    </div>
                </div>
                <!--Thème O LIGHT 1 DARK-->
                <div class="settings-list" id="theme" name="Closed">
                    <ion-icon name="color-palette-outline"></ion-icon> Theme Settings<div class="menu-arrow"><ion-icon id="menu-arrow-theme" name="chevron-forward-outline"></ion-icon></div>
                </div>
                <div class="theme-disclosed">
                    <div class="settings-styles">
                        <form id="form-registration" onsubmit="return (checkingForm('registration'))" action="<?= PHP.SETTINGS_PRO ?>" method="post">
                            <input type="hidden" name="srcTheme_username" id="srcTheme_username" value="<?= $userData[0]?>">
                            <label for="themeSelect">Select your color theme</label><br>
                            <select id="themeSelect" name="themeSelect">
                                <option value="" disabled selected>Select your theme</option>
                                <option value="0">Light</option>
                                <option value="1">Dark</option>
                            </select><br>
                            <input type="submit" class="confirm" name="submitRegistration" value="Confirm changes">
                        </form>
                    </div>
                </div>
                <!--Niveau de confidentialité (profil/posts)-->
                <div class="settings-list" id="privacy" name="Closed">
                    <ion-icon name="bug-outline"></ion-icon> Privacy Settings<div class="menu-arrow"><ion-icon id="menu-arrow-privacy" name="chevron-forward-outline"></ion-icon></div>
                </div>
                <div class="privacy-disclosed">
                    <div class="settings-styles">
                        <form id="form-registration" onsubmit="return (checkingForm('registration'))" action="<?= PHP.SETTINGS_PRO ?>" method="post">
                            <input type="hidden" name="srcPrivacy_username" id="srcPrivacy_username" value="<?= $userData[0]?>">
                            <label for="profilePrivacy">These people can see your profile</label><br>
                            <select name="profilePrivacy">
                                <option value="" disabled selected><?php if($user[10] == 2){echo "Everyone";}elseif($user[10] == 1){echo "Friends";}elseif($user[10] == 0){echo "Nobody";}?></option>
                                <option value="2">Everyone</option>
                                <option value="1">Friends</option>
                                <option value="0">Nobody</option>
                            </select>
                            <br>
                            <label for="postPrivacy">These people can see your posts</label><br>
                            <select name="postPrivacy">
                                <option value="" disabled selected><?php if($user[11] == 2){echo "Everyone";}elseif($user[11] == 1){echo "Friends";}elseif($user[11] == 0){echo "Nobody";}?></option>
                                <option value="2">Everyone</option>
                                <option value="1">Friends</option>
                                <option value="0">Nobody</option>
                            </select>
                            <br>
                            <input type="submit" class="confirm" name="submitRegistration" value="Confirm changes">
                        </form>
                    </div>
                </div>
                <!--Supprimer le compte-->
                <div class="settings-list" id="delete" name="Closed">
                    <ion-icon name="trash-outline"></ion-icon> Delete Account<div class="menu-arrow"><ion-icon id="menu-arrow-delete" name="chevron-forward-outline"></ion-icon></div>
                </div>
                <div class="delete-disclosed">
                    <div class="settings-styles">
                        <form id="form-delete-account" action="<?= PHP.SETTINGS_PRO ?>" method="post">
                            <label for="delete-account">Delete Account<br><ion-icon name="warning-outline"></ion-icon>This action cannot be undone<ion-icon name="warning-outline"></ion-icon></label><br>
                            <input type="button" name="delete-account" value="Delete" id="delete-account" onclick="delete_account()">
                            <input type="hidden" name="srcDelete_username" id="srcDelete_username" value="<?= $userData[0]?>">
                        </form>
                    </div>    
                </div>
            </div>
            <!-- Right content -->
            <?php 
                define('CONVERSIONABLE','1');
                define('TRASHABLE','1');
                include_once(LISTFRIEND);
            ?>
        </div>
        <br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
        <?php 
            include_once(FOOTER);
        ?>
    </body>

    <script rel="stylesheet" src="js/settings.js"></script>
    <script src="https://unpkg.com/sweetalert/dist/sweetalert.min.js"></script>
    <script type="module" src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.esm.js"></script>
    <script nomodule src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.js"></script>
</html>
