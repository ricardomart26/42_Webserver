#!/usr/bin/php
<?php
echo "<!DOCTYPE html>";
echo "<html>";
echo "<head>";
echo "<meta charset=\"UTF-8\">";
echo "</head>";
echo "<body>";
$method = trim($_SERVER['REQUEST_METHOD']);
if ($_SERVER['REQUEST_METHOD'] === 'POST')
{
   // if (upload_file() == false)
   // {
   //    http_response_code(400);
   //    return ;
   // }
   thank_user();
}
else if ($_SERVER['REQUEST_METHOD'] === 'GET'){
   echo "<h1>STILL IMPLEMENTING GET</h1>";
}

echo "<h1>You have been successful in the ".$method." request</h2>";
echo "</body>";
echo "</html>";

function upload_file()
{
   $upload_dir = "post/uploads/";
   echo $_FILES["cute_picture"]["name"];
   $file_to_upload = $basename($_FILES["cute_picture"]["name"]);
   // $extension = pathinfo($file_to_upload, PATHINFO_EXTENSION);
   // $file_to_upload = pathinfo($file_to_upload, PATHINFO_FILENAME);
   // $file_to_upload = $upload_dir . $file_to_upload . date('m-d-Y_hia') . $extension;
   // if (file_exists($file_to_upload))
   // {
   //    echo "<h1>Duplicated File was created at the exact same time</h1>";
   //    return (false);
   // }
   // if (move_uploaded_file($_FILES["cute_picture"]["tmp_name"], $file_to_upload)) {
   //    echo "<p>The file ". htmlspecialchars( basename( $_FILES["cute_picture"]["name"])). " has been uploaded.</p>";
   // } else {
   //    echo "Sorry, there was an error uploading your file.";
   // }
   return (true);

}

function thank_user()
{
   $gender = set_name_separator($_POST['gender'], "");
   $intro = appropriate_intro($gender);
   $fn = set_name_separator($_POST['first_name'], " ");
   $ln = set_name_separator($_POST['last_name'], " ");
   $name = $fn.$ln;
   if (empty($fn) && empty($ln)) {
      $name = "whoever you are";
   }
   echo "<p>Thank you for using our CGI, ".$intro.$name."!!!!!! </p>";
}

function set_name_separator( $name , $separator)
{
   if (isset($name) && !empty($name)) {
      $name = $separator.trim($name);
   } else {
      $name="";
   }
   return $name;
}

function appropriate_intro( $gender )
{
   if ($gender == "male") {
      $intro = "Mr.";
   } else if ($gender == "female") {
      $intro = "Mrs.";
   } else {
      $intro = "";
   }
   return $intro;
}

?>
