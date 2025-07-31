
 function switchPage(){
    if (document.getElementById("form-box").style.display == "flex"){
        document.getElementById("form-box").style.display = "none"
        document.getElementById("register-box").style.display = "flex"
    }else{
        document.getElementById("form-box").style.display = "flex"
        document.getElementById("register-box").style.display = "none"
    }
 }
