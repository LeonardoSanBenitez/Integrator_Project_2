<?php
	$bdServidor = '127.0.0.1';
	$bdUsuario = 'root';
	$bdSenha = '';
	$bdBanco = 'benchmarking';
	
	$conexao = mysqli_connect($bdServidor, $bdUsuario, $bdSenha, $bdBanco);
	if (mysqli_connect_errno($conexao)) {
		echo "Problemas para conectar no banco. Verifique os dados!";
		die();
	}

	function acessar_historico($conexao){
		$sqlBusca = 'SELECT * FROM historico';
		$resultado = mysqli_query($conexao, $sqlBusca);
		$respostas = array();
		while ($resposta = mysqli_fetch_assoc($resultado)) {
			$respostas[] = $resposta;
		}
		return $respostas;
	}
	
	function gravar_resposta($conexao, $_resposta){
		$sqlGravar = "
			INSERT INTO historico
			(usuario, r1, r2, r3, r4, r5,r6, r7, r8)
			VALUES
			(
			'{$_resposta['usuario']}',
			'{$_resposta['r1']}',
			'{$_resposta['r2']}',
			'{$_resposta['r3']}',
			'{$_resposta['r4']}',
			'{$_resposta['r5']}',
			'{$_resposta['r6']}',
			'{$_resposta['r7']}',
			'{$_resposta['r8']}'
			)
		";
		mysqli_query($conexao, $sqlGravar);	
	}
?>