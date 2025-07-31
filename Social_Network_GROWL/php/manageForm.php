<?php    
    // fonction  permettant de securiser les informations reçu par un formulaire
    function valid_data(string $data){
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }

    // fonction verifiant la validiter d'une date qui doit être avant un délai avant aujourd'hui (date de nassance avec un age minimum)
    function valid_date_inf(string $inputDate, int $minimumYears){
        $date = $inputDate;
        if(strtotime($date))
        {
            if(strpos($date,'-') !== false) 
            {
                list($year, $month, $day) = explode('-', $date);
                //return checkdate($month, $day, $year);
                if(checkdate($month, $day, $year) !== false) 
                {
                    $dateAgeMaxTab = explode('-', date("Y-m-d"));
                    $dateAgeMaxTab[0] -= $minimumYears;
                    $dateAgeMax = implode('-', $dateAgeMaxTab);
                    $dateAgeMin = '1900-01-01';

                    if($date < $dateAgeMax && $date > $dateAgeMin)
                    {
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    // fonction verifiant la validité d'une entré de formulaire selon un pattern
    function checkWithPattern(string $nameInput,string $data,string $pattern, string $dataName, string $allowedCharacter, string $errorSessionName, string $correctInputSessionName)
    {
        if(preg_match($pattern, $data) === 0)
        {
            $_SESSION[$errorSessionName][$nameInput] = "The authorized characters are: ".$allowedCharacter.".";
            return 1;
        }
        else
        {
            $_SESSION[$correctInputSessionName][$nameInput] = $data;
            return 0;
        }
    }


    /*
        Fonction de verification de formulaire qui fonctionne pour tous les formulaires
    */
    function checkingForm(string $formName, array $formInputs)
    {
        if(!empty($formName) && !empty($formInputs) && $formName === "registration" )   //verification du nom de formulaire entré
        {
            $keySet = $formName."Keys";

            // définition des nom des entrées possible pour chaque formulaire
            $registrationKeys = ["userName", "name", "firstName", "sex", "birthDate", "mail", "confirmationMail", "password", 
                "confirmationPassword", "country", "city", "phoneNumber"];

            $accentedCharacters = "àèìòùÀÈÌÒÙáéíóúýÁÉÍÓÚÝâêîôûÂÊÎÔÛãñõÃÑÕäëïöüÿÄËÏÖÜŸçÇßØøÅåÆæœ";

            // définition des tableaux des champs pouvant être verifier avec une expression regulière
            $checkWithPatternKeys = ["userName", "name", "firstName", "password", "country", "city", "phoneNumber"];
            $patterns = ["userName" => "/^[\p{L}$accentedCharacters\d\s]{1,32}$/u", "name" => "/^[\p{L}\-]{1,32}$/u", "firstName" => "/^[\p{L}\-]{1,32}$/u",
                    "password" => "/^(?=.*\d)(?=.*[A-Z])(?=.*[-!@#$%_])(?=.*[a-z])[0-9A-Za-z!@#$%_\-]{8,30}$/", 
                    "country" => "/^[\p{L}\-]{1,32}$/u",
                    "city" => "/^[\p{L}\-]{1,32}$/u", "phoneNumber" => "/^0\d{9}$/", 
            ];

            // définition des tableaux permettant de génerer une message d'erreur différent selon l'entrée
            $allDataName = ["userName" => "nom d'utilisateur",
                "name" => "nom", "firstName" => "prénom", "sex" => "sexe", "birthDate" => "date de naissance", "mail" => "mail", 
                "confirmationMail" => "mail de confirmation",  "password" => "mot de passe", "confirmationPassword" => "mot de passe de confirmation", 
                "address" => "adresse", "country" => "pays", "city" => "ville", "phoneNumber" => "numéro de téléphone"
            ];

            $allAllowedCharacter = ["userName" => "les lettres, les chiffres",
                "name" => "les lettres, -", "firstName" => "les lettres, -", 
                "password" => "les minuscules, majuscules, chiffres, -!@#$%_, avec un de chaque minimum 7 caracter",
                "country" => "les lettres, -", "city" => "les lettres, -'", "phoneNumber" => "10 chiffes dont le premier est 0", 
            ];

            $formNameUC = ucwords($formName);

            $errorSessionName = "errorMessage".$formNameUC;
            $submitKey = "submit".$formNameUC;
            $_SESSION[$errorSessionName] = [$submitKey => "", "allEmptyField" => ""];
            $correctInputSessionName = "correctInput".$formNameUC;
            unset($formInputs[$submitKey]);

            $errorNumber = 0;
            
            // boucle sur le tableau concerné par la verification grace à un nom de variable variable
            foreach($$keySet as $nameInput)
            {
                $_SESSION[$errorSessionName][$nameInput] = "";
                if(isset($formInputs[$nameInput])) // verification si le champ est set et génération d'un message d'erreur si ce n'est pas le cas
                {  
                    if($nameInput !== "sex" && $formInputs[$nameInput] === "") // verification si le champ est vide et génération d'un message d'erreur si c'est le cas
                    {
                        $_SESSION[$errorSessionName][$nameInput] = "Please indicate your gender.";
                        $errorNumber += 1;
                    }
                    else
                    {
                        $dataValueValid = valid_data($formInputs[$nameInput]);
                        if($dataValueValid !== $formInputs[$nameInput]) // verification de la validité de l'entré notament les caractères html
                        {
                            unset( $_SESSION[$errorSessionName]);
                            $_SESSION[$errorSessionName][$submitKey] = "The data sent through the form is not compliant.";
                            $errorNumber += 1;
                            break;
                        }
                        else
                        {
                            $formInputs[$nameInput] = trim($dataValueValid);

                            if(in_array($nameInput, $checkWithPatternKeys, true)) // verification pour tous les champs se verifiant à l'aide d'un pattern
                            {
                                $errorNumber += checkWithPattern($nameInput, $formInputs[$nameInput], $patterns[$nameInput], $allDataName[$nameInput], $allAllowedCharacter[$nameInput], $errorSessionName, $correctInputSessionName);
                            }
                            // verification des autres champs devant être faite individuellement 
                            else if($nameInput === "sex")
                            {
                                if(!($formInputs[$nameInput] === "Man" || $formInputs[$nameInput] === "Woman" || $formInputs[$nameInput] === "Other"))
                                {
                                    $_SESSION[$errorSessionName][$nameInput] = "Please indicate your gender.";
                                    $errorNumber += 1;
                                }
                                else
                                {
                                    $_SESSION[$correctInputSessionName][$nameInput] = $formInputs[$nameInput];
                                }
                            }
                            else if($nameInput === "birthDate")
                            {
                                if(!(valid_date_inf($formInputs[$nameInput], 12))) //verification de la date de naissance
                                {
                                    $_SESSION[$errorSessionName][$nameInput] = "You have not correctly indicated your date of birth or you are under 12 years old/were born before 1900.";
                                    $errorNumber += 1;
                                }
                                else
                                {
                                    $_SESSION[$correctInputSessionName][$nameInput] = $formInputs[$nameInput];
                                }
                            }
                            else if($nameInput === "mail")
                            {
                                if(!filter_var($formInputs[$nameInput], FILTER_VALIDATE_EMAIL)) // verification du mail faite avec un filtre
                                {
                                    $_SESSION[$errorSessionName][$nameInput] = "Please provide a valid email address.";
                                    $errorNumber += 1;
                                }
                                else
                                {
                                    $_SESSION[$correctInputSessionName][$nameInput] = $formInputs[$nameInput];
                                }
                            }
                            else if($formName === "registration"  && $nameInput === "confirmationMail")
                            {
                                if(!filter_var($formInputs[$nameInput], FILTER_VALIDATE_EMAIL)) // verification du mail de confirmation avec le filtre
                                {
                                    $_SESSION[$errorSessionName][$nameInput] = "Please provide a valid email address.";
                                    $errorNumber += 1;
                                }
                                else
                                {
                                    $_SESSION[$correctInputSessionName][$nameInput] = $formInputs[$nameInput];
                    
                                    if(!(isset($formInputs["mail"]) && $formInputs["mail"] === $formInputs["confirmationMail"])) // verification de l'égalité entre le mail et le mail de confirmation
                                    {
                                        $_SESSION[$errorSessionName][$nameInput] = "The two email addresses do not match.";
                                        $errorNumber += 1;
                                    }
                                }
                            }
                            else if($formName === "registration" && $nameInput === "confirmationPassword")
                            {
                                if(!preg_match($patterns["password"], $formInputs[$nameInput]) === 0) // verification du mot de passe de confirmation avec une expression regulière
                                {
                                    $_SESSION[$errorSessionName][$nameInput] = "Please enter a valid password.";
                                    $errorNumber += 1;
                                }
                                else
                                {
                                    $_SESSION[$correctInputSessionName][$nameInput] = $formInputs[$nameInput];
                    
                                    if(!(isset($formInputs["password"]) && $formInputs["password"] === $formInputs["confirmationPassword"])) // verification de l'égalité entre le mot de passe et le mot de passe de confirmation
                                    {
                                        $_SESSION[$errorSessionName][$nameInput] = "The two passwords do not match.ss";
                                        $errorNumber += 1;
                                    }
                                }
                            }
                        }
                        
                    }
                }
                else
                {
                    /* l'entrée sex est traitée differement car vu que c'est un bouton radio, contrairement au champs textuels 
                    qui même non rempli sont quant même set avec des valeur vide, l'input radio n'est pas set s'il n'est pas 
                    rempli */
                    if($nameInput === "sex")
                    {
                        $_SESSION[$errorSessionName][$nameInput] = "Please indicate your gender.";
                        $errorNumber += 1;
                    }
                    else{
                        $_SESSION[$errorSessionName][$submitKey] = "There was an error sending the form.";
                        $errorNumber += 1;
                    }
                }
            }
            return $errorNumber;
        }
        else
        {
            return -1;
        }

    }
?>
