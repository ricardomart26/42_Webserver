<?php

if (isset($_POST["submit"]))
{
	$uid = $_POST["uid"];
	$pwd = $_POST["pwd"];

	require_once 'dbh.inc.php';
	require_once 'utils.inc.php';

	if (emptyInputLogin($uid, $pwd) !== false)
	{
		header("Location : ../login.php?error=emptyInput");
		exit();
	}

	loginUser($conn, $uid, $pwd);
}
else
{
	header("Location: ../login.php");
	exit();
}
