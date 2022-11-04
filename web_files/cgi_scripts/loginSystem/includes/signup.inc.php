<?php

if (isset($_POST["submit"])) 
{
	$name = $_POST["name"];
	$email = $_POST["email"];
	$uid = $_POST["uid"];
	$pwd = $_POST["pwd"];
	$pwdRepeat = $_POST["pwd-repeat"];

	require_once 'dbh.inc.php';
	require_once 'utils.inc.php';

	if (emptyInputSignup($name, $email, $uid, $pwd, $pwdRepeat) !== false)
	{
		header("Location: ../signup.php?error=emptyinput");
		exit();
	}

	if (invalidUid($uid) !== false)
	{
		header("Location: ../signup.php?error=InvalidUid");
		exit();
	}

	if (invalidEmail($email) !== false)
	{
		header("Location: ../signup.php?error=InvalidEmail");
		exit();
	}

	if (pwdDontMatch($pwd, $pwdRepeat) !== false)
	{
		header("Location: ../signup.php?error=PasswordDontMach");
		exit();
	}

	if (uidOrEmailExists($conn, $uid, $email) !== false)
	{
		header("Location: ../signup.php?error=UsernameTaken");
		exit();
	}

	createUser($conn, $name, $email, $uid, $pwd);

} else {
	header("Location: ../signup.php");
	exit();
}
