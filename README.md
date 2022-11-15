## webserv
You must write a HTTP server in C++ 98.

# HTTP/Web server

What is a web server ? What is a HTTP Server ?

# Web browser/HTTP Client

What is a web browser (focus on the http client part) ? What kind of information does a web browser sends to the HTTP server ? (->client requests and server responses)

*Client request*
```
GET / HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-GB,en;q=0.5
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
```


*Server response*
```
HTTP/1.1 200 OK
Date: Mon, 23 May 2005 22:38:34 GMT
Content-Type: text/html; charset=UTF-8
Content-Length: 155
Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT
Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)
ETag: "3f80f-1b6-3e1cb03b"
Accept-Ranges: bytes
Connection: close

<html>
  <head>
    <title>An Example Page</title>
  </head>
  <body>
    <p>Hello World, this is a very simple HTML document.</p>
  </body>
</html>
```


# HTTP Methods


# HTTP Status and Errors


# Config File

The configuration file takes inspiration from the "server" part of an NGINX configuration file. A simple example is :


```
server {

	listen			0.0.0.0:81
	server_name		my_website my_website.com

	location		/ {
		root			./data/my_website
		index			index.html
	}

	location		/test {
		root					./data/my_website/test
	}
	
	autoindex				off
	client_body_buffer_size	1000
	allow_methods			GET POST DELETE
}
```


*listen

	Sets the address of the host (here: 0.0.0.0) and port (here: 80) on which the server will receive requests

*server_name

	Sets names of the virtual server (here: my_website and my_website.com)

*location

	Sets the correct routes within the file system (here: ex: my_website.com/home.html redirects to ./data/my_website/home.html)

*root

	Sets the path the URI will be added to (here: ex: ./data/my_website)

*index

	The default file to load if the request ends with '/' (here: ./data/my_website/index.html)

*autoindex

	If "on" and no index file are set, requests ending with '/' produces a list of files and folders within the requested directory

*client_body_buffer_size

	Sets the buffer size to read from a client request body, meaning any POST actions. If the request body is larger, part or the whole body is written in a temporary file

*allow_methods

	Sets the methods that the server accepts requests of

The server receives a request one a port they listen to (here: 80) or by server name (here: my_website.com)
The request is : http://my_website.com/hello/home.html:80
The URI is : hello/home.html
The location block that best matches the URI is : /
Therefore the root is : ./data/my_website
The server will send back : ./data/my_website/hello/home.html

If the server does not find the requested file, it will send a response with the appropriate error (in this case : error 404).

# Setting up errors in the config file

Example : error_page 404 srcs/config/files/default_error_pages/404.html

# Poll(), Select(), Kqueue() and Epoll()


# CGI


# Ressources

[Wikipedia - HTTP](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol)
[Beginners's guide to NGINX](http://nginx.org/en/docs/beginners_guide.html#conf_structure)
[Some useful definitions](http://nginx.org/en/docs/http/ngx_http_core_module.html)
[HTTP request methods](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods)
[Helpful documentation by 42 students](https://webserv42.notion.site/Webserv-cbb6ab4136ba4b4c8cb4f98109d5fc1f)
