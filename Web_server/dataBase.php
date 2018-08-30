<?php
	///Database variables
	$bdServer = '127.0.0.1';
	$bdUser = 'root';
	$bdPassword = '';
	$bdName = 'receiveddata';
	
	///Connection
	$connection = mysqli_connect($bdServer, $bdUser, $bdPassword, $bdName);
	if (mysqli_connect_errno($connection)) {
		echo "Problemas para conectar no banco. Verifique os dados!";
		die();
	}
	
	/// Main function
	function searchData($_connection) {
		$sqlSelect = 'SELECT * FROM raw_data';
		$result = mysqli_query($_connection, $sqlSelect);
		$data = array();
		while ($line = mysqli_fetch_assoc($result)) {
			$data[] = $line;
		}
		return $data;
	}
	
	function insertData($_connection, $_data){
		$sqlInsert = "
			INSERT INTO tarefas
			(team, instaled, volume, color, date)
			VALUES
			(
				'{$_data['team']}',
				'{$_data['instaled']}',
				'{$_data['volume']}',
				'{$_data['color']}',
				'{$_data['date']}'
			)
		";
	
		if (mysqli_query($_connection, $sqlInsert)) return "sucess";
		
		else return "fail";
	}
?>