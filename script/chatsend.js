/**************************************

	Envoi de message

***************************************/
(function(){

	$('#post').click(function(e){
		var m = document.getElementById('msg');
		
		e.preventDefault(); //

		var message = m.value; //message entre
		
		var error = 0;
		
			if(message == ""){ //message vide
				error = 1;
				alert("Erreur : message vide ou incorrect.");
			}
			else if(false){ //erreur nom d'utilisateur
				error = -1;
				alert("Erreur : nom d'utilisateur non valide, veuillez vous reconnecter.");
			}

		$.ajax({url : "./htbin/chatsend.py", type : "POST", data : "num="+error+"&msg="+message});
		m.value = "";
	});

}());