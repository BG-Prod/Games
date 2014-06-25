var connect = document.getElementById("envoyer");
connect.addEventListener("click", function() {
	verifCo();
});

function verifCo()
{
	var formulaire = document.getElementById("login");
	
	var username = document.getElementById("userName");
	var passwd = document.getElementById("userPwd");
	
	var welcome = document.createElement('section');

		var nom = document.createElement('p');
			nom.appendChild(document.createTextNode("Bienvenue " + username.value));

		var lienChat = document.createElement('a');
			lienChat.setAttribute('href', './chat.html');
			lienChat.innerHTML = 'Lien vers le chat';

	welcome.appendChild(nom);
	welcome.appendChild(lienChat);
	
	formulaire.onsubmit = function()
	{
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
				//var text = document.createElement(xhr.responseText);

				//formulaire.replaceChild(text,document.getElementById("login").firstChild);
				formulaire.appendChild(welcome);
				document.getElementsByTagName("form")[0].setAttribute("style", "display : none;");
			}
			else
			{
				document.ajax.dyn="Error code " + xhr.status;
			}
		   }
		}; 
	 
	   xhr.open( "POST", "../htbin/login.py",  true);
	   
	   xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	   
	   xhr.send("username="+username.innerText + "&" + "userpwd=" + passwd.innerText);
	   
	   return false;
	};
}