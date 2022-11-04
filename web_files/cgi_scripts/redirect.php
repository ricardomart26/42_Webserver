<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Document</title>
</head>
<body>
	<form method="post">
		Go to index.html behind: 
		<input type="submit" value="Go" name="Submit1">
	</form>
	
	<form method="post">
		Go to index.php in current folder:  
		<input type="submit" value="Go" name="Submit2">
	</form>
	
	<form method="post">
		Absolute path in Location:  
		<input type="submit" value="Go" name="Submit3">
	</form>
	
	<?php
		if (isset($_POST["Submit1"]))
			header("Location: ../index.html");
		if (isset($_POST["Submit2"]))
			header("Location: index.php");
		if (isset($_POST["Submit3"]))
			header("Location: web_files/cgi_scripts/index.php");
	?>

</body>
</html>
