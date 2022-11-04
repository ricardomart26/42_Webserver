<?php

$servername = "localhost";
$dbUsername = "ricardo";
$dbPassword = "Foxinha12";
$dbName = "LoginSystem";

$conn = mysqli_connect($servername, $dbUsername, $dbPassword, $dbName);

if (!$conn) {
	die("Connection to db failed: " . mysqli_connect_error());

}
