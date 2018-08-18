(function($) {
	/*---------------------------------------------------------------------*/
	/*--                        Variaveis Globais                        --*/
	/*---------------------------------------------------------------------*/
	var usuario;
	var questionario = "corpo_docente";
	var pergunta = 1;

	/*---------------------------------------------------------------------*/
	/*--                       Funções Principais                        --*/
	/*---------------------------------------------------------------------*/
	proxima_pagina = function (r){
		if (pergunta == 8 && questionario == "corpo_docente"){
			pergunta = 000;		
			transicao ("#questionario", "#grafico")
		}
		else if (pergunta == 000 && questionario == "corpo_docente"){
			pergunta = 1;
			$("#grafico").fadeOut(250);
			carrega_pagina ();
		} 
		else{
			pergunta = pergunta + 1;
			carrega_pagina ();
		}
	}
	
	carrega_pagina = function (){
		transicao ("#questionario", "#questionario");
		
		setTimeout(function(){
			//$("#questionario_titulo")	.load("modelo/" + questionario + "/titulo.txt");
			// $("#id_titulo")				.text("CD " + pergunta);
			// $("#id_texto")				.load("modelo/" + questionario + "/cd_" + pergunta + "/id.txt",function(responseText, textStatus, XMLHttpRequest){ if (textStatus == "error") alert ("Desculpe o transtorno, mas esta pergunta não consta na nossa base de dados.");});
			// $("#r1_texto")				.load("modelo/" + questionario + "/cd_" + pergunta + "/r1.txt");
			// $("#r3_texto")				.load("modelo/" + questionario + "/cd_" + pergunta + "/r3.txt");
			// $("#r5_texto")				.load("modelo/" + questionario + "/cd_" + pergunta + "/r5.txt");
			// $("#ajuda_titulo")			.load("modelo/" + questionario + "/cd_" + pergunta + "/id.txt");
			// $("#ajuda_texto")			.load("modelo/" + questionario + "/cd_" + pergunta + "/descricao.txt");
		}, 250);
	}
	
	/*---------------------------------------------------------------------*/
	/*--                        Funções Auxiliares                       --*/
	/*---------------------------------------------------------------------*/
	transicao = function (atual, proxima){
		$(atual).fadeOut(250);
		setTimeout(function(){
			$(proxima).fadeIn(250);
		}, 300);		
	}

}(jQuery));
