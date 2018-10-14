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
				
				<!-- Questionário -->
				<section id="data-hub" class="row table-responsive">
					<table class="table table-hover">
					  <thead class="thead-light" >
						<tr>
						  <th scope="col">Equipe</th>
						  <th scope="col">Local</th>
						  <th scope="col">Volume</th>
						  <th scope="col">Cor</th>
						  <th scope="col">Data</th>
						</tr>
					  </thead>
					  <tbody>
						<tr v-for="data in json">
						  <td>{{data.team}}</td>
						  <td>{{data.instaled}}</td>
						  <td>{{data.volume}}</td>
						  <td>{{translateColor(data.color)}}</td>
						  <td>{{data.received}}</td>
						</tr>
					  </tbody>
					</table>
					<!-- TODO: botão não está responsivo -->
					<button title="Ajuda" type="button" class="btn btn-primary" data-toggle="modal" data-target="#ajuda"><i class='fa fa-question fa-2x'></i></button>
				</section>
				
				
				<!-- Modal Ajuda -->
				<section id="ajuda" class="modal fade" role="dialog">
				  <div class="modal-dialog">
					<!-- Modal content-->
					<div class="modal-content">
						<header class="modal-header">
							<button type="button" class="close" data-dismiss="modal">&times;</button>
							<h4 class="modal-title">Ajuda</h4>
						</header>
						<article class="modal-body">
							<p>Equipe: quem enviou os dados.</p>
							<p>Local: de onde vem os dados (LPAE, LPT, etc)</p>
							<p>Volume: quanto líquido há dentro do pote.</p></p>
							<p>Cor: o líquido pode ser vermelho, azul ou verde.</p>
							<p>Data: quando o dado chegou no nosso servidor.</p>
						</article>
						<footer class="modal-footer">
							<button type="button" class="btn btn-default" data-dismiss="modal">Fechar</button>
						</footer>
					</div>
				  </div>
				</section>		
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