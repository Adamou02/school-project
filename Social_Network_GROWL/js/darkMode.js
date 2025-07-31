var darkBtn = document.getElementById("dark-mode-btn")

function toggleDarkMode() {
    darkBtn.classList.toggle("dark-mode-on");
    document.body.classList.toggle("dark-theme");
    if(darkBtn.classList.contains('dark-mode-on')) {
        console.log("unable");
        SessionDarkModUpdate("UnableDM");
    } else {
        console.log("disable");
        SessionDarkModUpdate("DisableDM");
    }
}

  
darkBtn.onclick = toggleDarkMode;