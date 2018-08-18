<?php
	$historico = array();
	//session_start();
	//unset($_SESSION['historico']);
	include "banco.php";
	
	if (isset($_GET['usuario'])) {
		$_resposta = array();
		$_resposta['usuario'] = $_GET['usuario'];
		$_resposta['r1'] = $_GET['r1'];
		$_resposta['r2'] = $_GET['r2'];
		$_resposta['r3'] = $_GET['r3'];
		$_resposta['r4'] = $_GET['r4'];
		$_resposta['r5'] = $_GET['r5'];
		$_resposta['r6'] = $_GET['r6'];
		$_resposta['r7'] = $_GET['r7'];
		$_resposta['r8'] = $_GET['r8'];
		gravar_resposta($conexao, $_resposta);
	}
	
	$historico = acessar_historico($conexao);
	//var_dump($historico);
?>

<!DOCTYPE html>
<html>
<body>
	<br>
	<h1>Histórico de respostas</h1>
	<table>
		<tr>
			<th>Usuário</th>
			<th>R1</th>
			<th>R2</th>
			<th>R3</th>
			<th>R4</th>
			<th>R5</th>
			<th>R6</th>
			<th>R7</th>
			<th>R8</th>
		</tr>
		
		<?php foreach ($historico as $resposta) : ?>
			<tr>
				<td><?php echo $resposta['usuario']; ?> </td>
				<td><?php echo $resposta['r1']; ?> </td>
				<td><?php echo $resposta['r2']; ?> </td>
				<td><?php echo $resposta['r3']; ?> </td>
				<td><?php echo $resposta['r4']; ?> </td>
				<td><?php echo $resposta['r5']; ?> </td>
				<td><?php echo $resposta['r6']; ?> </td>
				<td><?php echo $resposta['r7']; ?> </td>
				<td><?php echo $resposta['r8']; ?> </td>
			</tr>
		<?php endforeach; ?>
	</table>
</body>
</html>