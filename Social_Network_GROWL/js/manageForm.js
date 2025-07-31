// fonction verifiant la validiter d'une date qui doit être avant un délai avant aujourd'hui (date de nassance avec un age minimum)
function testBirthDate(inputDate, marginYears){
    let today = new Date;
    let minAge = '';
    if ((today.getMonth()+1) > 9){
        minAge = (today.getFullYear()-marginYears) + '-' + (today.getMonth()+1) + '-' + today.getDate() ;
    }
    else{
        minAge = (today.getFullYear()-marginYears) + '-0' + (today.getMonth()+1) + '-' + today.getDate() ;
    }

    if(inputDate == ""){
        return false;
    }
    else if(Date.parse(inputDate) > Date.parse(today)){
        return false;
    }
    else if(Date.parse(inputDate) > Date.parse(minAge)){
        return false;
    }
    else{
        return true;
    }
}

function ucwords(str)
{
    strUC = str.toLowerCase().replace(/^[\u00C0-\u1FFF\u2C00-\uD7FF\w]|\s[\u00C0-\u1FFF\u2C00-\uD7FF\w]/g, function(letter) {
        return letter.toUpperCase();
    });
    return strUC;
}

// fonction pour verifier la validiter des boutons radio pour le choix du sexe
function checkSexRadio(sexElement)
{
    let nbCheck = 0;
    for (let i = 0; i < sexElement.length; i++) {
        if (sexElement[i].checked && (sexElement[i].value === "Man" || sexElement[i].value === "Woman" || sexElement[i].value === "Other")) 
        {
           nbCheck++;
        }
    }
    if(nbCheck === 1){return true;}else{return false;}
}

// fonction verifiant la validité d'une entré de formulaire selon un pattern
function checkWithPattern(input, pattern, dataName, allowedCharacter, errorMessageElement)
{
    data = input.value.trim();
    let usedPattern = new RegExp(pattern);
    if(!(usedPattern.test(data)))
    {
        errorMessageElement.innerHTML = ucwords(dataName)+" incorrect. Les caracteres autorisés sont "+allowedCharacter+".";
        input.className += "invalidInput";
        return 1;
    }
    else
    {        
        return 0;
    }
}

function checkingForm(formName)
{
    if(formName === "registration")
    {
        //console.log("test");
        let keySet = formName+"Keys";

        // définition des noms des entrées possible pour chaque formulaire
        let registrationKeys = ["userName", "name", "firstName", "sex", "birthDate", "mail", "confirmationMail", "password", 
            "confirmationPassword", "country", "city", "phoneNumber"];

        var accentedCharacters = "àèìòùÀÈÌÒÙáéíóúýÁÉÍÓÚÝâêîôûÂÊÎÔÛãñõÃÑÕäëïöüÿÄËÏÖÜŸçÇßØøÅåÆæœ";

        // définition des tableaux des champs pouvant être verifier avec une expression regulière
        let checkWithPatternKeys = ["userName", "name", "firstName", "mail", "password", "country", "city", "phoneNumber"];
        let patterns = {"userName": "^[a-zA-Z0-9"+accentedCharacters+"\\s']{1,32}$", 
            "name": "^[a-zA-Z"+accentedCharacters+"' \\-]{1,32}$", 
            "firstName": "^[a-zA-Z"+accentedCharacters+"' \\-]{1,32}$",
            "mail" : "^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\\.[a-zA-Z0-9-]+)*$", 
            "password": "^(?=.*\\d)(?=.*[A-Z])(?=.*[-!@#$%_])(?=.*[a-z])[0-9A-Za-z!@#$%\-_]{8,30}$", 
            "country": "^[a-zA-Z"+accentedCharacters+"' \\-]{1,32}$", 
            "city": "^[a-zA-Z"+accentedCharacters+"' \\-]{1,32}$",
            "phoneNumber": "^0\\d{9}$", 
        };

        // définition des tableaux permettant de génerer une message d'erreur différent selon l'entrée
        let allDataName = {
            "userName" : "nom d'utilisateur", "name": "nom", "firstName": "prenom", "sex": "sexe", "birthDate": "date de naissance", "mail": "mail", 
            "confirmationMail": "mail de confirmation",  "password": "mot de passe", "confirmationPassword": "mot de passe de confirmation", 
            "country": "pays", "city": "ville", "phoneNumber": "numéro de téléphone",
        };

        let allAllowedCharacter = {
            "userName" : "les lettres, les chiffres", "name": "les lettres, -", "firstName": "les lettres, -",
            "password": "les minuscules, majuscules, chiffres, -!@#$%_, avec un de chaque minimum 8 caracter",
            "country": "les lettres, -", "city": "les lettres, -'", "phoneNumber": "10 chiffes dont le premier est 0", 
        }

        var errorNumber = 0;

        var formInputs = {};
        for(const nameInput of eval(keySet))
        {
            formInputs[nameInput] = document.forms["form-"+formName][nameInput];
        }

        // boucle sur le tableau concerné par la verification grace à un nom de variable variable (grace à eval)
        for(const nameInput of eval(keySet))
        {
            errorMessageElement = document.getElementById("errorMessage-"+formName+"-"+nameInput);
            errorMessageElement.textContent = "";

            if(nameInput !== "sex" && formInputs["name"].value === "") // verification si le champ est vide et génération d'un message d'erreur si c'est la cas
            {
                console.log("test");
                errorMessageElement.textContent = "Veuillez remplir votre "+allDataName[nameInput]+"."+formInputs[nameInput].value+"1";
                errorNumber++;
            }
            else
            {
                if(checkWithPatternKeys.includes(nameInput)) // verification pour tous les champs se verifiant à l'aide d'un pattern
                {
                    errorNumber += checkWithPattern(formInputs[nameInput], patterns[nameInput], allDataName[nameInput], allAllowedCharacter[nameInput], errorMessageElement);
                    console.log("test1");
                }
                // verification des autres champs devant être faite individuellement 
                else if(nameInput === "sex")
                {
                    if(!(checkSexRadio(formInputs[nameInput]))) // verification du sexe
                    {
                        errorMessageElement.textContent = "Veuillez indiquer votre sexe.";
                        errorNumber++;
                        console.log("test2");
                    }
                    
                }
                else if(nameInput === "birthDate")
                {
                    if(!(testBirthDate(formInputs[nameInput].value, 12)))  // verification de la date de naissance
                    {
                        errorMessageElement.textContent = "Vous n'avez pas correctement indiqué votre date de naissance. \nVous devez avoir au minimum 12 ans.";
                        errorNumber++;
                        console.log("test3");
                    }
                }
                else if(formName === "registration" && nameInput === "confirmationMail")
                {
                    let usedPattern = new RegExp(patterns["mail"]);
                    if(!usedPattern.test(formInputs[nameInput].value.trim()))  // verification du mail de confirmation avec une expression régulière
                    {
                        errorMessageElement.textContent = "Veuillez indiquer une adresse email valide.";
                        errorNumber++;
                        console.log("test4");
                    }
                    else
                    {   
                        if(formInputs["mail"].value.trim() !== formInputs["confirmationMail"].value.trim()) // verification de l'égalité entre le mail et le mail de confirmation
                        {
                            errorMessageElement.textContent = "Les deux adresses email ne correspondent pas.";
                            errorNumber++;
                            console.log("test5");
                        }
                    }
                }
                else if(formName === "registration" && nameInput === "confirmationPassword")
                {
                    let usedPattern = new RegExp(patterns["password"]);
                    if(!usedPattern.test(formInputs[nameInput].value.trim()))  // verification du mot de passe de confirmation avec une expression regulière
                    {
                        errorMessageElement.textContent = "Veuillez indiquer un mot de passe valide.";
                        errorNumber++;
                        console.log("test6");
                    }
                    else
                    {        
                        if(formInputs["password"].value.trim() !== formInputs["confirmationPassword"].value.trim())  // verification de l'égalité entre le mot de passe et le mot de passe de confirmation
                        {
                            errorMessageElement.textContent = "Les deux mots de passe ne correspondent pas.";
                            errorNumber++;
                            console.log("test7");
                        }
                    }
                }
                                
            }
        }
        if(errorNumber === 0)
        {
            return true;
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
