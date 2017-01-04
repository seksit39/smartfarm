<?php
//connecting to the database
define('DB_HOST', 'localhost');
define('DB_NAME', 'robot');
define('DB_USER','root');
define('DB_PASSWORD','');

$con=mysql_connect(DB_HOST,DB_USER,DB_PASSWORD) or die("Failed to connect to MySQL: " . mysql_error());
$db=mysql_select_db(DB_NAME,$con) or die("Failed to connect to MySQL: " . mysql_error());

 $sql = "INSERT INTO connected_car_1.sensor (value) VALUES ('".$_GET["value"]."')";    

   // Execute SQL statement

  mysql_query($sql,$con);
mysql_close($con);
?>