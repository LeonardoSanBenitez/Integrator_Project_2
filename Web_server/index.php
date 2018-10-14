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
				<header class="row"><h1>Projeto Integrador 2</h1></header>	
				
				<div id="myCarousel" class="carousel slide" data-ride="carousel">
				  <!-- Indicators -->
				  <ol class="carousel-indicators">
					<li data-target="#myCarousel" data-slide-to="0" class="active"></li>
					<li data-target="#myCarousel" data-slide-to="1"></li>
					<li data-target="#myCarousel" data-slide-to="2"></li>
				  </ol>

				  <!-- Wrapper for slides -->
				  <div class="carousel-inner">
					<div class="item active">
					  <img src="https://wallpapercave.com/wp/y7MHn2V.jpg" alt="Chania">
					  <div class="carousel-caption">
						<h3>Projeto Integrador 2</h3>
						<p>blablabla</p>
					  </div>
					</div>

					<div class="item">
					  <img src="https://wallpapercave.com/wp/aIaQVpx.jpg" alt="Chicago">
					  <div class="carousel-caption">
						<h3>LPAE</h3>
						<p>blablabla</p>
					  </div>
					</div>

					<div class="item">
					  <img src="https://wallpapercave.com/wp/y7MHn2V.jpg" alt="New York">
					  <div class="carousel-caption">
						<h3>DAELN</h3>
						<p>blablabla</p>
					  </div>
					</div>
				  </div>

				  <!-- Left and right controls -->
				  <a class="left carousel-control" href="#myCarousel" data-slide="prev">
					<span class="glyphicon glyphicon-chevron-left"></span>
					<span class="sr-only">Previous</span>
				  </a>
				  <a class="right carousel-control" href="#myCarousel" data-slide="next">
					<span class="glyphicon glyphicon-chevron-right"></span>
					<span class="sr-only">Next</span>
				  </a>
				</div>
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