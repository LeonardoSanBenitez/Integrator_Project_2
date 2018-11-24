<?php
	include "dataBase.php";
	date_default_timezone_set('America/Sao_Paulo');

	if (isset($_GET['team'])) {	//TODO: tem um jeito melhor de verificar isso?
		$_buffer = array();
		$_buffer['team'] = $_GET['team'];
		$_buffer['instaled'] = $_GET['instaled'];
		$_h = $_GET['altura'];	//recebe o valor em milímetros
		$_buffer['color_red'] = $_GET['red'];
		$_buffer['color_green'] = $_GET['green'];
		$_buffer['color_blue'] = $_GET['blue'];
		$_buffer['date'] = date("Y-m-d h:i:s");

		//test URL: API_data_receive.php?team=elvis&instaled=LTAP&altura=100&red=255&green=0&blue=0
		$_Rh = (53.6*$_h - 43.05*$_h + 43.05*53.6)/53.6;
		$_buffer['volume'] = number_format(0.000000333333*3.141592*$_h*($_Rh*$_Rh + $_Rh*43.05 + 43.05*43.05), 3).'L';
		
		//var_dump($_buffer);
		
		$connection = connectDB();
		echo insertData($connection, $_buffer);
		closeDB($connection);
	}
?>