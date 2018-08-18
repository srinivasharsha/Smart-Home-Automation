<?php
$con = mysqli_connect("IP","USER,"PASSWORD","DB");
if(! $con)
{
    die('Connection Failed'.mysqli_error());
}
?>
