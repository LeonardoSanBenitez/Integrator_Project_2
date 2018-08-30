<?php
	$historico = array();
	include "dataBase.php";

	if (isset($_GET['index'])) {	//tem um jeito melhor de verificar isso 
		$_resposta = array();
		//$_resposta['index'] = $_GET['index'];	//is auto increment
		$_resposta['team'] = $_GET['team'];
		$_resposta['local'] = $_GET['local'];
		$_resposta['volume'] = $_GET['volume'];
		$_resposta['color'] = $_GET['color'];
		//$_resposta['date'] = $_GET['date'];	//TODO: get date()

		//gravar_resposta($conexao, $_resposta);
		$historico = $_resposta;
	}
	
	
	//$historico = acessar_historico($conexao);
	var_dump($historico);
?>

<!DOCTYPE html>
<html>
<body>
	<br>
	<h1>Verificador de recebimento </h1>
	<table>
		<tr>
			<th>Team</th>
			<th>Local</th>
			<th>Volume</th>
			<th>Color</th>
			<th>Date</th>
		</tr>
		<tr>
			<td><?php echo $historico['team']; ?> </td>
			<td><?php echo $historico['local']; ?> </td>
			<td><?php echo $historico['volume']; ?> </td>
			<td><?php echo $historico['color']; ?> </td>
			<td><?php echo $historico['date']; ?> </td>
		</tr>
	</table>
</body>
</html>