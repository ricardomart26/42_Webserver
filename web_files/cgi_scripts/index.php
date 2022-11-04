<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h1>Hello</h1>

    <?php
        echo 'Firstname: ' .$_POST['fname']."\n";
        echo 'Lastname: ' .$_POST['lname']."\n";
    ?>
    <form action="" method="POST">
        <label for="fname">First name:</label><br>
        <input type="text" id="fname" name="fname" value="John"><br>
        <label for="lname">Last name:</label><br>
        <input type="text" id="lname" name="lname" value="Doe"><br><br>
        <label for="question">If you are gay, click this box: </label>
        <input type="checkbox" id="question" name="question">
        <input type="submit" value="Submit">
    </form>
</body>
</html>
