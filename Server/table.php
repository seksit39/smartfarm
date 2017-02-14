<?php

	include("connectAdd.php"); 	
	
	$link=Connection();

	$result=mysqli_query($link,"SELECT * FROM `seksu` ORDER BY `time` DESC");
?>

<html>
   <head>
      <title>Smart Farm</title>
   </head>
<body>
   <h1>Smart Farm Project</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Times&nbsp;</td>
			<td>&nbsp;AirHumi&nbsp;</td>
			<td>&nbsp;AirTemp&nbsp;</td>
			<td>&nbsp;GroundHumi&nbsp;</td>
			<td>&nbsp;GroundTemp&nbsp;</td>
			<td>&nbsp;Light&nbsp;</td>
			<td>&nbsp;Rain&nbsp;</td>
		</tr>

      <?php 
		  if($result!==FALSE){
		     while($row = mysqli_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s </td>
		        	<td> &nbsp;%s&nbsp; </td>
		        	<td> &nbsp;%s&nbsp; </td>
		        	<td> &nbsp;%s&nbsp; </td>
		        	<td> &nbsp;%s&nbsp; </td>
		        	<td> &nbsp;%s&nbsp; </td>
		        	<td> &nbsp;%s&nbsp; </td></tr>", 
		           $row["time"], $row["airHumi"], $row["airTemp"], $row["groundHumi"], $row["groundTemp"], $row["light"], $row["rain"]);
		     }
		     //mysql_free_result($result);
		     //mysql_close();
		  }
      ?>

   </table>
</body>
</html>
