<section>
	<h2> Log in </h2>
	<form action="includes/login.inc.php" method="post">
		<input type="text" name="uid" placeholder="Username/Email...">
		<input type="password" name="pwd" placeholder="Password...">
		<button type="submit" name="submit">Log in</button>
	</form>
</section>

<?php
	if (isset($_GET["error"]))
	{
		if ($_GET["error"] == "emptyInput")
			echo "<p>Input field is empty</p>";
		else if ($_GET["error"] == "WrongLogin")
			echo "<p>Wrong username or email</p>";
		else if ($_GET["error"] == "WrongPassword")
			echo "<p>Wrong Password</p>";
		else if ($_GET["error"] == "StatementFailed")
			echo "<p>Statement has failed, try again!</p>";
		else if ($_GET["error"] == "none")
			echo "<p>Log in Successfull</p>"; 
	}
?>
