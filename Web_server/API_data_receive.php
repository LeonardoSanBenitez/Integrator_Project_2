<?php
	include "dataBase.php";
	date_default_timezone_set('America/Sao_Paulo');

	if (isset($_GET['team'])) {	//TODO: tem um jeito melhor de verificar isso?
		$_buffer = array();
		//$_buffer['index'] = $_GET['index'];	//is auto increment
		$_buffer['team'] = $_GET['team'];
		$_buffer['instaled'] = $_GET['instaled'];
		$_buffer['volume'] = $_GET['volume'];
		$_buffer['color'] = $_GET['color'];
		$_buffer['date'] = date("Y-m-d h:i:s");

		//test URL: API_data_receive.php?team=elvis&instaled=LTAP&volume=230ml&color=1
		var_dump($_buffer);//debug
		//echo ("TEAM: {$_buffer['team']}");
		//echo ("INSTALED: {$_buffer['instaled']}");
		
		$connection = connectDB();
		echo insertData($connection, $_buffer);
		closeDB($connection);
	}
?>