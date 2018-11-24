<?php
include "dataBase.php";


//date_default_timezone_set ("America/Brasilia");
//date.timezone = America/Brasilia;
$date = date("Y-m-d h:i:s");
//$date = "YYYY-MM-DD HH:MI:SS";
$json = '[
{"team": "Benitez", "instaled":"LPAE", "volume":"900ml", "red": 200, "green": 50, "blue": 50, "received":"'.$date.'"},
{"team": "Benitez", "instaled":"LPAE", "volume":"900ml", "red": 50, "green": 50, "blue": 200, "received":"'.$date.'"},
{"team": "Benitez", "instaled":"LPAE", "volume":"900ml", "red": 200, "green": 50, "blue": 50, "received":"'.$date.'"}
]';
echo $json;

/*
$connection = connectDB();
print json_encode(searchData($connection, 5));
closeDB($connection);*/

?>
