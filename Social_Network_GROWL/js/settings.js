let openProfile = document.querySelectorAll("#profile");
let profileMenu = document.querySelectorAll(".profile-disclosed");
let profileArrow = document.querySelectorAll("#menu-arrow-profile");

let openTheme = document.querySelectorAll("#theme");
let themeMenu = document.querySelectorAll(".theme-disclosed");
let themeArrow = document.querySelectorAll("#menu-arrow-theme");

let openPrivacy = document.querySelectorAll("#privacy");
let privacyMenu = document.querySelectorAll(".privacy-disclosed");
let privacyArrow = document.querySelectorAll("#menu-arrow-privacy");

let openDelete = document.querySelectorAll("#delete");
let deleteMenu = document.querySelectorAll(".delete-disclosed");
let deleteArrow = document.querySelectorAll("#menu-arrow-delete");

let openPassword = document.querySelectorAll("#passwordChange");
let passwordMenu = document.querySelectorAll(".password-disclosed");
let passwordArrow = document.querySelectorAll("#menu-arrow-password");

/*
    Menu opening functions
*/

function openSettings(input, menu, arrow){
    if(input.getAttribute("name") === "Closed"){
        menu.style.display = "block";
        arrow.style.rotate = "90deg";
        input.setAttribute("name", "Open");
    }
    else if(input.getAttribute("name") === "Open"){
        menu.style.display = "none";
        arrow.style.rotate = "0deg";
        input.setAttribute("name", "Closed");
    }
}

/*
    Event listeners
*/

openTheme[0].addEventListener('click', function(){openSettings(openTheme[0], themeMenu[0], themeArrow[0])});
openProfile[0].addEventListener('click', function(){openSettings(openProfile[0], profileMenu[0], profileArrow[0])});
openPrivacy[0].addEventListener('click', function(){openSettings(openPrivacy[0], privacyMenu[0], privacyArrow[0])});
openDelete[0].addEventListener('click', function(){openSettings(openDelete[0], deleteMenu[0], deleteArrow[0])});
openPassword[0].addEventListener('click', function(){openSettings(openPassword[0], passwordMenu[0], passwordArrow[0])});

/*
    Confirm function
*/
function delete_account(){
    swal({
        title: "Are you sure?",
        text: "Once deleted, you will not be able to recover your account!",
        icon: "warning",
        buttons: {
            cancel: true,
            confirm: "Delete",
        },
        dangerMode: true,
    })
    .then((willDelete) => {
        if (willDelete) {
            swal({
                title: "Your account was succesfully deleted!",
                text: "You will be redirected to the login page...",
                icon: "success",
            });
            document.getElementById("form-delete-account").submit();
        } else {
            swal("Your account was not deleted!", {
                icon: "error",
            });
        }
    });
}

function delete_friend(friend_no){
    swal({
        title: "Are you sure?",
        text: "Once deleted, your friend will have to add you again!",
        icon: "warning",
        buttons: {
            cancel: true,
            confirm: "Delete",
        },
        dangerMode: true,
    })
    .then((willDelete) => {
        if (willDelete) {
            swal("Your friend was succesfully removed!", {
                icon: "success",
            });
            document.getElementById("form-delete-friend" + friend_no).submit();
        } else {
            swal("Your friend was not removed!", {
                icon: "error",
            });
        }
    });
}

function previewPicture(e){
        
    var divImages = document.getElementById("profilePicture");
        element = Array.from(e.files)[0]

        if (element) {
            const input = document.getElementById("hiddenfile");
            const file = input.files[0];
            const maxSize = 500000;

            if(file.size > maxSize){
                swal('File too large. max size : 500ko');
                input.value = '';
            }
            
            else{
                var oImg = document.createElement("img");
                oImg.setAttribute('src', URL.createObjectURL(element));
                fetch(oImg.src) .then((res) => res.blob()) .then((blob) => {
                    // Read the Blob as DataURL using the FileReader API
                    const reader = new FileReader();
                    reader.onloadend = () => {
                        divImages.src = reader.result;
                        document.getElementById("srcPP_base64").setAttribute('value', (reader.result).split("base64,")[1]);
                        document.getElementById("srcPP_type").setAttribute('value', (reader.result).split(";")[0].split("data:")[1]);
                    };
                    reader.readAsDataURL(blob);
                });
            }
            
            divImages.appendChild(oImg);
        }
        
}

function getfile(){
    document.getElementById('hiddenfile').click();
}