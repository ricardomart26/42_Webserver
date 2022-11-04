

<section class="signup-form">
	<h2> SIGN UP </h2>
	<form action="includes/signup.inc.php" method="post">
		<input type="text" name="name" placeholder="Full name...">
		<input type="text" name="email" placeholder="Email...">
		<input type="text" name="uid" placeholder="Username...">
		<input type="password" name="pwd" placeholder="Password...">
		<input type="password" name="pwd-repeat" placeholder="Repeat password...">
		<button type="submit" name="submit">Sign up</button>
	</form>
</section>

<?php

	if (isset($_GET["error"]))
	{
		if (empty($_GET["error"]))
		{
		}
		else if ($_GET["error"] == "emptyinput")
			echo "<p>Fill in all the fields</p>"; 
		else if ($_GET["error"] == "InvalidUid")
			echo "<p>Invalid Username, must be letters or numbers </p>"; 
		else if ($_GET["error"] == "InvalidEmail")
			echo "<p>Email is invalid</p>"; 
		else if ($_GET["error"] == "PasswordDontMach")
			echo "<p>Password Doesnt match</p>"; 
		else if ($_GET["error"] == "UsernameTaken")
			echo "<p>Username already chosen, try another</p>"; 
		else if ($_GET["error"] == "StatementFailed")
			echo "<p>Something failed in database statement</p>"; 
		else if ($_GET["error"] == "none")
			echo "<p>Sign up successfully</p>"; 
	}

?>
