/*****************************

	Lecture des messages

******************************/

var updateChat = setInterval( function(){maj();}, 2000); //on regarde toutes les 2s si un nouveau message
var affichage = document.getElementById("viewmessage"); //la div specialement faite pour
var cpt = 0;


var maj = function(){
	var xhr;
	
	try {  xhr = new ActiveXObject('Msxml2.XMLHTTP');   }
	catch (e) 
	{
		try {   xhr = new ActiveXObject('Microsoft.XMLHTTP'); }
		catch (e2) 
		{
		    try {  xhr = new XMLHttpRequest();  }
		    catch (e3) {  xhr = false;   }
		}
	}
	
	xhr.onreadystatechange  = function() 
	{ 
	    if(xhr.readyState  == 4)
	    {
			if(xhr.status  == 200)
			{	
				var data = JSON.parse(xhr.responseText);
				
				//alert(data.length);
				
				if(cpt != data.length){
					for(var i = cpt; i<data.length; i++) {
						var text = "";
						text = text + data[i].user + " : " + data[i].msg;
						
						affichage.appendChild(document.createElement('p').appendChild(document.createTextNode(text)));
						affichage.appendChild(document.createElement('br'));
					}
					cpt = data.length;
				}
			}
		}
	}

	xhr.open("GET", "../htbin/chatget.py",  true);
	xhr.send(null);
};	

function mettreEnForme(json){
	var element = document.createElement("p");
	
	var chaine = "";
	chaine += json["user"] + "(" + json["time"] + ") : " + json["msg"];
	
	element.appendChild(document.createTextNode(chaine)); //username + ( + heure + ) + : + message
	
	return element;
}