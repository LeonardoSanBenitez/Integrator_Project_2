<?php 
include "dataBase.php";

/*
//date_default_timezone_set ("America/Brasilia");
//date.timezone = America/Brasilia;
$date = date("Y-m-d h:i:s");
//$date = "YYYY-MM-DD HH:MI:SS";
$json = '[
{"team": "Benitez", "local":"LPAE", "volume":"900ml", "color":"1", "date":"'.$date.'"},
{"team": "Elvis", "local":"LPT", "volume":"850ml", "color":"2", "date":"'.$date.'"},
{"team": "Benitez", "local":"LPAE", "volume":"875ml", "color":"1", "date":"'.$date.'"},
{"team": "Benitez", "local":"LPAE", "volume":"870ml", "color":"1", "date":"'.$date.'"},
{"team": "Ednei", "local":"LD1", "volume":"300ml", "color":"2", "date":"'.$date.'"},
{"team": "Ednei", "local":"LD1", "volume":"550ml", "color":"3", "date":"'.$date.'"}
]';
echo $json; 
*/

$connection = connectDB();
print json_encode(searchData($connection, 5));
closeDB($connection);
		
?>