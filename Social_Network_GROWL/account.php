<!DOCTYPE html>
<html lang="fr">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login / Register GROWNL</title>
    <link rel="stylesheet" href="css/account.css">
    <link rel="icon" type="image/ico" href="./images/growl_ico.ico">
</head>

<body>
    <?php 
        require_once("./php/constant.php");
        require_once("./php/required.php");
    ?>
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
    <main>
        <div id="logo"><img src="images/logo.png" class="logo"></div>

        <div class="form-box" id="form-box" style="display: flex;">
            <div class="form-value">
                <form id="submit_Login" action="<?= PHP.LOGIN_PRO ?>" method="post">
                    <h2>Login</h2>
                    <div class="inputbox">
                        <ion-icon name="mail-outline"></ion-icon>
                        <input type="texte" name="identifiant" id="identifiant" required
                            value="<?php if(isset($_SESSION['conservedLogin'])){echo $_SESSION['conservedLogin'];unset($_SESSION['conservedLogin']);}else{echo "";} ?>">
                        <label for="">Email/Username</label>
                    </div>
                    <p id="errorMessage-registration-log" class="errorMessage">
                        <?php if(isset($tab_errorMessage_log["log"])){echo $tab_errorMessage_log["log"];}else{echo "";} ?>
                    </p>
                    <div class="inputbox">
                        <ion-icon name="lock-closed-outline"></ion-icon>
                        <input type="password" type="password" name="password_log" id="password_log" required>
                        <label for="">Password</label>
                    </div>
                    <p id="errorMessage-registration-passwordLog" class="errorMessage">
                        <?php if(isset($tab_errorMessage_log["passwordLog"])){echo $tab_errorMessage_log["passwordLog"];}else{echo "";} ?>
                    </p>
                    <button class="button1" name="submitLogin">Log in</button>
                    <div class="register">
                        <p>Don't have a account <a href="#" onclick="switchPage()">Register</a></p>
                    </div>
                </form>
            </div>
        </div>

        <div class="register-box" id="register-box" style="display:none">
            <div class="form-value">
                <form id="form-registration" onsubmit="return (checkingForm('registration'))"
                    action="<?= PHP.ACCOUNT_PRO ?>" method="post">
                    <div class="register-all">


                        <div class="left-register">


                            <div class="register-input">
                                <input type="text" name="userName" id="userName" required
                                    placeholder="Nom d'utilisateur" size="32"
                                    value="<?php if(isset($tabCorrectInput["userName"])){echo $tabCorrectInput["userName"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-userName" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["userName"])){echo $tabErrorMessage["userName"];}else{echo "";} ?>
                                </p>
                            </div>


                            <div class="register-input">
                                <input type="text" name="name" id="name" required placeholder="Nom" size="32"
                                    value="<?php if(isset($tabCorrectInput["name"])){echo $tabCorrectInput["name"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-name" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["name"])){echo $tabErrorMessage["name"];}else{echo "";} ?>
                                </p>
                            </div>

                            <div class="register-input">
                                <input type="text" name="firstName" id="firstName" required placeholder="Prénom"
                                    size="32"
                                    value="<?php if(isset($tabCorrectInput["firstName"])){echo $tabCorrectInput["firstName"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-firstName" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["firstName"])){echo $tabErrorMessage["firstName"];}else{echo "";} ?>
                                </p>
                            </div>


                            <div class="register-input" style="display:flex;padding-top:10px;">
                                <label for="sexChoice" style="padding-left:5px;">Sexe</label>

                                <label for="sexMan">Homme</label>
                                <input type="radio" id="sexMan" name="sex" value="Man"
                                    <?php if(isset($tabCorrectInput["sex"]) && $tabCorrectInput["sex"] === "Man"){echo "checked";}else{echo "";} ?>>
                                

                                <label for="sexWoman">Femme</label>
                                <input type="radio" id="sexWoman" name="sex" value="Woman"
                                    <?php if(isset($tabCorrectInput["sex"]) && $tabCorrectInput["sex"] === "Woman"){echo "checked";}else{echo "";} ?>>
                                

                                <label for="sexOther">Autre</label>
                                <input type="radio" id="sexOther" name="sex" value="Other"
                                    <?php if(isset($tabCorrectInput["sex"]) && $tabCorrectInput["sex"] === "Other"){echo "checked";}else{echo "";} ?>>
                                

                                <p id="errorMessage-registration-sex" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["sex"])){echo $tabErrorMessage["sex"];}else{echo "";} ?>
                                </p>
                            </div>

                            <div class="register-input">
                                <input type="date" name="birthDate" id="birthDate" required
                                    value="<?php if(isset($tabCorrectInput["birthDate"])){echo $tabCorrectInput["birthDate"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-birthDate" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["birthDate"])){echo $tabErrorMessage["birthDate"];}else{echo "";} ?>
                                </p>
                            </div>

                            <div class="register-input">
                                <input type="tel" name="phoneNumber" id="phoneNumber" required placeholder="Téléphone"
                                    value="<?php if(isset($tabCorrectInput["phoneNumber"])){echo $tabCorrectInput["phoneNumber"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-phoneNumber" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["phoneNumber"])){echo $tabErrorMessage["phoneNumber"];}else{echo "";} ?>
                                </p>
                            </div>

                        </div>

                        <div class="right-register">

                            <div class="register-input">
                                <input type="email" name="mail" id="mail" placeholder="Adresse mail" required size="25"
                                    value="<?php if(isset($tabCorrectInput["mail"])){echo $tabCorrectInput["mail"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-mail" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["mail"])){echo $tabErrorMessage["mail"];}else{echo "";} ?>
                                </p>
                            </div>

                            <div class="register-input">
                                <input type="email" name="confirmationMail" id="confirmationMail"
                                    onpaste="return false;" required placeholder="Confirmation mail" size="25"
                                    value="<?php if(isset($tabCorrectInput["confirmationMail"])){echo $tabCorrectInput["confirmationMail"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-confirmationMail" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["confirmationMail"])){echo $tabErrorMessage["confirmationMail"];}else{echo "";} ?>
                                </p>
                            </div>

                            <div class="register-input">
                                <input type="password" name="password" id="password" required
                                    placeholder="Mot de passe">
                                <p id="errorMessage-registration-password" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["password"])){echo $tabErrorMessage["password"];}else{echo "";} ?>
                                </p>
                            </div>
                            <div class="register-input">
                                <input type="password" name="confirmationPassword" id="confirmationPassword"
                                    onpaste="return false;" required placeholder="Confirmation mot de passe">
                                <p id="errorMessage-registration-confirmationPassword" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["confirmationPassword"])){echo $tabErrorMessage["confirmationPassword"];}else{echo "";} ?>
                                </p>
                            </div>



                            <div class="register-input">
                                <input class="country" name="country" id="country" placeholder="Pays" required rows="3"
                                    value="<?php if(isset($tabCorrectInput["country"])){echo $tabCorrectInput["country"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-country" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["country"])){echo $tabErrorMessage["country"];}else{echo "";} ?>
                                </p>
                            </div>

                            <div class="register-input">
                                <input type="text" name="city" id="city" placeholder="Ville" required
                                    value="<?php if(isset($tabCorrectInput["city"])){echo $tabCorrectInput["city"];}else{echo "";} ?>">
                                <p id="errorMessage-registration-city" class="errorMessage">
                                    <?php if(isset($tabErrorMessage["city"])){echo $tabErrorMessage["city"];}else{echo "";} ?>
                                </p>
                            </div>

                        </div>
                    </div>


                <div class="register-btn">
                <button class="button2" name="submitRegistration">Confirm Register</button>
                <button class="button2" name="Reset" onclick="document.location.href='<?= ACCOUNT ?>'">Cancel</button>
                    <!--<input type="submit" class="btn bottom_btn" name="submitRegistration"
                                value="Valider inscription">
                      
                            <input type="reset" class="btn bottom_btn" name="Reset" value="Annuler">-->
                </div>
                
            </div>
            </form>
        </div>
        </div>

    </main>
    <script type="module" src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.esm.js"></script>
    <script nomodule src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.js"></script>
    <script type="text/javascript" src="./js/manage_form.js"></script>
    <script type="text/javascript" src="./js/account.js"></script>
    <?php 
    if(isset($_SESSION['error']) && $_SESSION['error'] == "true"){
        unset($_SESSION['error']);
        echo "<script> switchPage() </script>";
    } ?>
</body>

</html>
