#!/bin/bash

# export GATEWAY_INTERFACE="CGI/1.1"
# export SERVER_PROTOCOL="HTTP/1.1"
# export SCRIPT_FILENAME="index.php"
# # export SCRIPT_NAME="index.php"
# export REDIRECT_STATUS="200"
# export CONTENT_LENGTH="32"
# export REQUEST_METHOD="POST"
# export QUERY_STRING="Random"
# # export PATH_INFO="/home/ricardo/Desktop/42/42_projects/42_WebServ/web_files/index.php"


# echo "fname=John&lname=Doe&question=on" | /usr/bin/php-cgi

# REDIRECT_STATUS=true
# SCRIPT_FILENAME=/home/ricardo/Desktop/42/42_projects/42_WebServ/web_files/index.php
# REQUEST_METHOD=POST
# GATEWAY_INTERFACE=CGI/1.1
# CONTENT_LENGTH=6

# export REDIRECT_STATUS
# export SCRIPT_FILENAME
# export REQUEST_METHOD
# export GATEWAY_INTERFACE
# export CONTENT_LENGTH

# echo "test=1" | php-cgi

#!/bin/sh
REQUEST_DATA="first_name=val_1&last_name=val_2&gender=male"
export GATEWAY_INTERFACE="CGI/1.1"
export SERVER_PROTOCOL="HTTP/1.1"
# export QUERY_STRING="test=querystring"
export REDIRECT_STATUS="200"
export SCRIPT_FILENAME="test.php"
export REQUEST_METHOD="POST"
export CONTENT_LENGTH=${#REQUEST_DATA}
export CONTENT_TYPE="application/x-www-form-urlencoded;charset=utf-8"

echo $REQUEST_DATA | /usr/bin/php-cgi
