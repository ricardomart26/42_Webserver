# CONFIGURATION FILE

https://docs.nginx.com/nginx/admin-guide/basic-functionality/managing-configuration-files/
https://www.javatpoint.com/nginx-directive-and-context


- DIRECTIVES (conf options)
- FEATURE-SPECIFIC CONFIGURATION FILES (includes)
- CONTEXTS (servers)
	- Events
	- HTTP
		- Locations
	- Mail
	- Stream


*Start with the name of option
*Continue with parameters
*End the options with semicolon (;)
Example : " gzip on; "

*Between curly brackets ( {} ) we have contexts. 
*Start with name of context
*Then curly brackets
*Then parameters
Example:
		worker_processes 2;     # directive in the global context  
		http {                  # http context  
			gzip on;            # directive in http context  
		
		server {            # server context  
			listen 80;      # directive in server context  
		}  

* Comment = '#' and should be ignored.

ATTENTION: Directives may be different depending on the context.
	THERE ARE 3 TYPES OF DIRECTIVES:
		- Normal (example: gzip)
			--> Only 1 directive by context. 
			--> children directive overwrite parent context
		- Array (example: error_log)
			--> If same directive it will add instead of overwrite
			--> children directive overwrite parent context
		- Action Directive (example rewrite and return)
			--> Used to change things.
			--> It will make the action in that moment, going from up to down and updating.
		
	THERE ARE 10 TYPES OF CONTEXT:
		- Main / Global (example: user and group)
			--> Not contained in {}
			--> In the beggining of the file
			--> Directives in this context cannot be overwitten because this context cannot be inherited
		- Events
			--> Sets global options for connection processing
		- HTTP:
			- Server Context
				--> Inside HTTP context
				--> Define virtual host settings
				--> There can be more than one Server inside HTTP
				--> Define settings for different IP addresses or ports
				- Location Context 
					--> Inside Server context
					--> Handle Request of the Client
					--> Location can also be inside Location...
			- Upstream Context


=========================================================================================================================
=========================================================================================================================

error page: https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page

Syntax: 	error_page code ... [=[response]] uri;
Default: 	—
Context: 	http, server, location, if in location

Defines the URI that will be shown for the specified errors. A uri value can contain variables.

Example:

	error_page 404             /404.html;
	error_page 500 502 503 504 /50x.html;

This causes an internal redirect to the specified uri with the client request method changed to “GET” (for all methods other than “GET” and “HEAD”).

It is also possible to use URL redirects for error processing:

	error_page 403      http://example.com/forbidden.html;
	error_page 404 =301 http://example.com/notfound.html;

=========================================================================================================================
=========================================================================================================================

limit_except: https://nginx.org/en/docs/http/ngx_http_core_module.html#limit_except

Syntax: 	limit_except method ... { ... }
Default: 	—
Context: 	location

Limits allowed HTTP methods inside a location. The method parameter can be one of the following: GET, POST, DELETE. Allowing the GET method makes the HEAD method also allowed.

	limit_except GET {
		allow 192.168.1.0/32;
		deny  all;
	}

Please note that this will limit access to all methods except GET.

=========================================================================================================================
=========================================================================================================================

client_max_body_size: https://nginx.org/en/docs/http/ngx_http_core_module.html#client_max_body_size

Syntax: 	client_max_body_size size;
Default: 	client_max_body_size 1m;
Context: 	http, server, location

Sets the maximum allowed size of the client request body. If the size in a request exceeds the configured value, the 413 (Request Entity Too Large) error is returned to the client. Please be aware that browsers cannot correctly display this error. Setting size to 0 disables checking of client request body size. 

=========================================================================================================================
=========================================================================================================================

listen: https://nginx.org/en/docs/http/ngx_http_core_module.html#listen

Syntax: 

listen address[:port] [default_server] [proxy_protocol] [backlog=number] [rcvbuf=size] [sndbuf=size] [bind];

Default:	listen *:80 | *:8000;
Context:	server

Sets the address and port for IP on which the server will accept requests. Both address and port, or only address or only port can be specified. An address may also be a hostname, for example:

	listen 127.0.0.1:8000;
	listen 127.0.0.1;
	listen 8000;
	listen *:8000;
	listen localhost:8000;

If only address is given, the port 80 is used.

If the directive is not present then either *:80 is used if nginx runs with the superuser privileges, or *:8000 otherwise.

The default_server parameter, if present, will cause the server to become the default server for the specified address:port pair. If none of the directives have the default_server parameter then the first server with the address:port pair will be the default server for this pair.

The proxy_protocol parameter (1.5.12) allows specifying that all connections accepted on this port should use the PROXY protocol.

	The PROXY protocol version 2 is supported since version 1.13.11. 

The listen directive can have several additional parameters specific to socket-related system calls. These parameters can be specified in any listen directive, but only once for a given address:port pair.

backlog=number
	sets the backlog parameter in the listen() call that limits the maximum length for the queue of pending connections. By default, backlog is set to -1 on FreeBSD, DragonFly BSD, and macOS, and to 511 on other platforms. 

rcvbuf=size
	sets the receive buffer size (the SO_RCVBUF option) for the listening socket. 

sndbuf=size
	sets the send buffer size (the SO_SNDBUF option) for the listening socket. 

bind

	instructs to make a separate bind() call for a given address:port pair. This is useful because if there are several listen directives with the same port but different addresses, and one of the listen directives listens on all addresses for the given port (*:port), nginx will bind() only to *:port. It should be noted that the getsockname() system call will be made in this case to determine the address that accepted the connection. If the setfib, fastopen, backlog, rcvbuf, sndbuf, accept_filter, deferred, ipv6only, reuseport, or so_keepalive parameters are used then for a given address:port pair a separate bind() call will always be made. 

reuseport

	instructs to create an individual listening socket for each worker process (using the SO_REUSEPORT socket option on Linux 3.9+), allowing a kernel to distribute incoming connections between worker processes.

		Inappropriate use of this option may have its security implications. 

Example:

	listen 127.0.0.1 default_server accept_filter=dataready backlog=1024;

=========================================================================================================================
=========================================================================================================================

root: https://nginx.org/en/docs/http/ngx_http_core_module.html#root

Syntax: 	root path;
Default: 	root html;
Context: 	http, server, location, if in location

Sets the root directory for requests. For example, with the following configuration

	location /i/ {
		root /data/w3;
	}

The /data/w3/i/top.gif file will be sent in response to the “/i/top.gif” request.

The path value can contain variables, except $document_root and $realpath_root.

A path to the file is constructed by merely adding a URI to the value of the root directive. If a URI has to be modified, the alias directive should be used. 

=========================================================================================================================
=========================================================================================================================

Syntax: 	server_name name ...;
Default: 	server_name "";
Context: 	server

Sets names of a virtual server, for example:

	server {
		server_name example.com www.example.com;
	}

The first name becomes the primary server name.

Server names can include an asterisk (“*”) replacing the first or last part of a name:

	server {
		server_name example.com *.example.com www.example.*;
	}

Such names are called wildcard names.

The first two of the names mentioned above can be combined in one:

	server {
		server_name .example.com;
	}

It is also possible to use regular expressions in server names, preceding the name with a tilde (“~”):

	server {
		server_name www.example.com ~^www\d+\.example\.com$;
	}

Regular expressions can contain captures (0.7.40) that can later be used in other directives:

	server {
		server_name ~^(www\.)?(.+)$;

		location / {
			root /sites/$2;
		}
	}

	server {
		server_name _;

		location / {
			root /sites/default;
		}
	}

Named captures in regular expressions create variables (0.8.25) that can later be used in other directives:

	server {
		server_name ~^(www\.)?(?<domain>.+)$;

		location / {
			root /sites/$domain;
		}
	}

	server {
		server_name _;

		location / {
			root /sites/default;
		}
	}

If the directive’s parameter is set to “$hostname” (0.9.4), the machine’s hostname is inserted.

It is also possible to specify an empty server name (0.7.11):

	server {
		server_name www.example.com "";
	}

It allows this server to process requests without the “Host” header field — instead of the default server — for the given address:port pair. This is the default setting.

	Before 0.8.48, the machine’s hostname was used by default. 

During searching for a virtual server by name, if the name matches more than one of the specified variants, (e.g. both a wildcard name and regular expression match), the first matching variant will be chosen, in the following order of priority:

	the exact name
	the longest wildcard name starting with an asterisk, e.g. “*.example.com”
	the longest wildcard name ending with an asterisk, e.g. “mail.*”
	the first matching regular expression (in order of appearance in the configuration file)

Detailed description of server names is provided in a separate Server names document. 

=========================================================================================================================
=========================================================================================================================


location / {
	root /data/www;
}

This location block specifies the “/” prefix compared with the URI from the request. 
For matching requests, the URI will be added to the path specified in the root directive, that is, to /data/www, so if tje URL is localhost:80/index.html, the path is /data/www/index.html. 

If there are several matching location blocks nginx selects the one with the longest prefix. The location block above provides the shortest prefix, of length one, and so only if all other location blocks fail to provide a match, this block will be used. 
