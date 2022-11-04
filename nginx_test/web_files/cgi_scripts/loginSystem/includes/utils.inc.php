<?php

function emptyInputSignup($name, $email, $uid, $pwd, $pwdRepeat)
{
	if (empty($name) || empty($email) ||empty($uid) ||empty($pwd) || empty($pwdRepeat))
		return (true);
	return (false);
}

function invalidUid($uid)
{
	if (!preg_match("/^[a-zA-Z0-9]*$/", $uid))
		return (true);
	return (false);
}

function invalidEmail($email)
{
	if (!filter_var($email, FILTER_VALIDATE_EMAIL))
		return (true);
	return (false);
}

function pwdDontMatch($pwd, $pwdRepeat)
{
	if ($pwd !== $pwdRepeat)
		return (true);
	return (false);
}


function uidOrEmailExists($conn, $uid, $email)
{
	$sql = "SELECT * FROM users WHERE usersUid = ? OR usersEmail = ?;";
	$statement = mysqli_stmt_init($conn);
	if (!mysqli_stmt_prepare($statement, $sql))
	{
		header("location: ../signup.php?error=StatementFailed");
		exit();
	}
	mysqli_stmt_bind_param($statement, "ss", $uid, $email);
	mysqli_stmt_execute($statement);

	$resultData = mysqli_stmt_get_result();

	if ($row = mysqli_fetch_assoc($resultData)) 
		return ($row);
	else 
		return (false);
	
	mysqli_stmt_close($statement);
}

function createUser($conn, $name, $email, $username, $pwd)
{
	$sql = "INSERT INTO users (usersName, usersEmail, usersUid, usersPwd) VALUES (?, ?, ?, ?);";
	$statement = mysqli_stmt_init($conn);
	if (!mysqli_stmt_prepare($statement, $sql))
	{
		header("location: ../signup.php?error=StatementFailed");
		exit();
	}

	$hashedPwd = password_hash($pwd, PASSWORD_DEFAULT);

	mysqli_stmt_bind_param($statement, "ssss", $uid, $email, $username, $hashedPwd);
	mysqli_stmt_execute($statement);
	mysqli_stmt_close($statement);
	
	header("location: ../signup.php?error=none");
	exit();
}
