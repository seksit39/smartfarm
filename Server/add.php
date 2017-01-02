<?php
   	include("connect.php");
   	
   	$link=Connection();

   $airHumi = $_POST["airHumi"];
   $airTemp = $_POST["airTemp"];
   $groundHumi = $_POST["groundHumi"];
   $groundTemp = $_POST["groundTemp"];
   $light = $_POST["light"];
   $rain = $_POST["rain"];


	$query = "INSERT INTO `seksu` (`airHumi`,`airTemp`,`groundHumi`,`groundTemp`,`light`,`rain`) 
		VALUES ('".$airHumi."','".$airTemp."','".$groundHumi."','".$groundTemp."','".$light."','".$rain."')"; 
   	
   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>
