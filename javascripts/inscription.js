// Recuperation des elements
var lastname = document.getElementById("lastname");
var firstname = document.getElementById("firstname");
var birthdate = document.getElementById("birthdate");
var useremail = document.getElementById("useremail");
var username = document.getElementById("username");
var userpwd = document.getElementById("userpwd");
var userpwdconf = document.getElementById("userpwdconf");

// Boutons du formulaire
var bEffacer = document.getElementById("effacer");
bEffacer.addEventListener("click", function() {
	for(var i = 0; i<document.getElementsByClassName("formulaire").length; i++) {
		document.getElementsByClassName("formulaire")[i].setAttribute("src","");
	}
});

var bEnvoyer = document.getElementById("envoyerIns");
bEnvoyer.addEventListener("click", function() {
	if(verifBirthDate() && verifEmail() && verifFirstName() && verifLastName() && verifPseudo() && verifPwd() && verifPwdConf()) {
		alert("Inscription réussie !");
	}
	else {
		alert("Des champs sont encore faux !");
	}
});

// Utilisation des fonctions
lastname.onblur = verifLastName;
firstname.onblur = verifFirstName;
birthdate.onblur = verifBirthDate;
useremail.onblur = verifEmail;
username.onblur = verifPseudo;
userpwd.onblur = verifPwd;
userpwdconf.onblur = verifPwds;

// Implementation des fonctions
function verifLastName(){
	var name = /^[A-Z]{1}[a-zçîïéèàù]*([\s-][A-Z]{1}[a-zçîïéèàù]*)*$/
	if(name.test(lastname.value))
	{
		document.getElementsByClassName("formulaire")[0].setAttribute("src", "./ressources/ok.png");
		return true;
	}
	else
	{
		document.getElementsByClassName("formulaire")[0].setAttribute("src", "./ressources/false.png");
		return false;
	}
}

function verifFirstName(){
	var name = /^[A-Z]{1}[a-zçîïéèàù]*([\s-][A-Z]{1}[a-zçîïéèàù]*)*$/
	if(name.test(firstname.value))
	{
		document.getElementsByClassName("formulaire")[1].setAttribute("src", "./ressources/ok.png");
		return true;
	}
	else
	{
		document.getElementsByClassName("formulaire")[1].setAttribute("src", "./ressources/false.png");
		return false;
	}
}

function verifBirthDate(){
	var date = /^(\d{1,2}\/){2}\d{4}$/;
	
    if(!date.test(birthdate.value)){
		document.getElementsByClassName("formulaire")[2].setAttribute("src", "./ressources/false.png");
		return false;
	}
    else{
        var tmp = birthdate.value.split('/');
        tmp[1] -=1;
        var correct = new Date();
        correct.setFullYear(tmp[2]);
        correct.setMonth(tmp[1]);
        correct.setDate(tmp[0]);
        if(correct.getFullYear()==tmp[2] && correct.getMonth()==tmp[1] && correct.getDate()==tmp[0]){
            document.getElementsByClassName("formulaire")[2].setAttribute("src", "./ressources/ok.png");
			return true;
        }
        else{
            document.getElementsByClassName("formulaire")[2].setAttribute("src", "./ressources/false.png");
			return false;
        }
    }
}

function verifEmail(){
	var mail = /^[0-9a-zA-Z.\-_]+@[0-9a-z.\-_]+\.[a-z]{2,}$/;
	if(mail.test(useremail.value))
	{
		document.getElementsByClassName("formulaire")[3].setAttribute("src", "./ressources/ok.png");
		return true;
	}
	else
	{
		document.getElementsByClassName("formulaire")[3].setAttribute("src", "./ressources/false.png");
		return false;
	}
}

function verifPseudo(){
	var psd = /^[\w]{6,}$/;
	if(psd.test(username.value))
	{
		document.getElementsByClassName("formulaire")[4].setAttribute("src", "./ressources/ok.png");
		return true;
	}
	else
	{
		document.getElementsByClassName("formulaire")[4].setAttribute("src", "./ressources/false.png");
		return false;
	}
}

function verifPwds(){
	verifPwd();
	verifPwdConf();
}

function verifPwd(){
	var pwd = /([a-zA-Z0-9]){8,}/;
	var pwd2 = /.*[A-Z]{1,}.*/;
	var pwd3 = /.*[a-z]{1,}.*/;
	var pwd4 = /.*\d{1,}.*/;
	if(pwd.test(userpwd.value) && pwd2.test(userpwd.value) && pwd3.test(userpwd.value) && pwd4.test(userpwd.value))
	{
		document.getElementsByClassName("formulaire")[5].setAttribute("src", "./ressources/ok.png");
		return true;
	}
	else
	{
		document.getElementsByClassName("formulaire")[5].setAttribute("src", "./ressources/false.png");
		return false;
	}
}

function verifPwdConf(){
	if(userpwd.value===userpwdconf.value)
	{
		document.getElementsByClassName("formulaire")[6].setAttribute("src", "./ressources/ok.png");
		return true;
	}
	else
	{
		document.getElementsByClassName("formulaire")[6].setAttribute("src", "./ressources/false.png");
		return false;
	}
}

