<!DOCTYPE html>
<html lang="pt-br">
	<head>
		<!-- Definições Iniciais -->
		<title>PI-2 hub</title>
		<meta charset="utf-8" />
		<meta name="description"			content="Plataforma online do Projeto Integrador 2 da Engenharia Eletrônica do Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina." />
		<meta name="keywords"				content="PI2, Projeto, Integrador, DAELN, IFSC" />
		<meta name="author"					content="Leonardo Benitez" />
		<meta name="viewport"				content="width=device-width, initial-scale=1" />
		<meta name="robots" 				content="index,follow" />
		<meta http-equiv="content-language"	content="pt-br" />
		<link rel="icon"					href="view/imagens/favicon.ico"  type="shortcut icon" />

		<!-- CSS -->
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" />
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css" />
		<link rel="stylesheet" href="view/css/template.css" />
	</head>
	
	<body>
		<div class="geral" id="app">
			<!-- Navbar -->
			<nav class="navbar navbar-default"><?php include "view/html/navbar.html"; ?></nav>
			
			<!-- Main Content -->
			<div class="container-fluid wrap">
				<!-- Título -->
				<header class="row"><h1>Galeria</h1></header>
					
				<br>	
				<iframe width="560" height="315" src="https://www.youtube.com/embed/I3pGfxb3tKc" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>
				<br>
				<iframe width="560" height="315" src="https://www.youtube.com/embed/bZsXNGX_RGI" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>
			</div>
				
			<!-- footer -->
			<footer class="container-fluid rodape"> <?php include "view/html/rodape.html"; ?> </footer>
		</div>
		
		<!-- Java Script -->
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
 		<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
		<script src="https://cdn.jsdelivr.net/npm/vue"></script>		
 		<script src="controller/vue_controller.js"></script>		
	</body>
</html>