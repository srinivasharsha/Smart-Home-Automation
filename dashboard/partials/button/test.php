<?php
include ('../connectivity/conn.php');
$id=3;
$result = mysqli_query($con, "SELECT distinct devicecredentials.resource,devicecredentials.auth from devicecredentials WHERE devicecredentials.Dev_Id=$id" ) or die("Query fail :" .mysqli_error());
	$row = mysqli_fetch_array($result);
	echo $row['resource'];
	
?>
