<?php
	include "dataBase.php";
	date_default_timezone_set('America/Sao_Paulo');

	if (isset($_GET['index'])) {	//tem um jeito melhor de verificar isso 
		$_buffer = array();
		//$_buffer['index'] = $_GET['index'];	//is auto increment
		$_buffer['team'] = $_GET['team'];
		$_buffer['instaled'] = $_GET['instaled'];
		$_buffer['volume'] = $_GET['volume'];
		$_buffer['color'] = $_GET['color'];
		$_buffer['date'] = date("Y-m-d h:i:s");

		//var_dump($_buffer);
		
		echo insertData($connection, $_buffer);
	}
?>