//Recuperation de la feuille de style
var stylesheet = window.document.getElementById("chosenStyle");

//Bouton du style normal
var button1 = window.document.getElementById("styleNormal");
//button1.addEventListener('click', stylesheet.href = "./stylesheet/stylesheet.css", false);
button1.onclick = styleDefault;

//Bouton du style de nuit
var button2 = window.document.getElementById("styleNuit");
button2.onclick = styleNuit;

//Bouton du style original
var button3 = window.document.getElementById("styleOrigin");
button3.onclick = styleOrigin;

//Bouton reset
var button4 = window.document.getElementById("styleReset");
button4.onclick = styleReset;

//Fonctions de changement de style
function styleNuit() {
	stylesheet.href = "./stylesheet/stylesheet_nuit.css";
};

function styleDefault(){
	stylesheet.href = "./stylesheet/stylesheet.css";
};

function styleOrigin() {
	stylesheet.href = "./stylesheet/stylesheet_frenchy.css";
};

function styleReset() {
	stylesheet.href = "./stylesheet/reset.css";
};