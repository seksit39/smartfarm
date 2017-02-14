<?php

	function Connection(){
		$server="localhost";
		$user="root";
		$pass="12345678";
		$db="smart farm";
	   	
		//$connection = mysqli_connect($server, $user, $pass);

		$connection = mysqli_connect($_SERVER['RDS_HOSTNAME'], $_SERVER['RDS_USERNAME'], $_SERVER['RDS_PASSWORD'], $_SERVER['RDS_DB_NAME'], $_SERVER['RDS_PORT']);

	if (mysqli_connect_errno())
	{
		echo "Database Connect Failed : " . mysqli_connect_error();
		exit();
	}

		return $connection;
	}

?>
