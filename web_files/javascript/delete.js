
function delete_request()
{
    xhttp = new XMLHttpRequest();

    xhttp.open("DELETE", "file_to_delete.txt", true);
    xhttp.send();
}
