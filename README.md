# webserv
You must write a HTTP server in C++ 98.

# Web Server / HTTP / Web Client

A web server is an computer software that accepts requests through the World Wide web, usually following the HTTP protocol. It interprets the request message, verifies its syntax, identifies HTTP headers and sends back a response, satisfying the request if possible.

HTTP (or hypertext Transfer Protocol) is a protocol for client/server communication, meaning that each exchange between a client and a web server follows a set of rules.

A web browser is a software that consults and displays websites, through the request of files to a web server. It is a HTTP client. The most used web browser is Google Chrome.

# Communication between client and server

After clicking on the link of a website, the web browser will request the files to display said website. For example, http://www.example.com will produce this request :

```
GET / HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-GB,en;q=0.5
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
```

- a request line : the method (GET), the URL requested (/) and the protocol version (HTTP/1.1)
- a required header (Host: ) : the domain name of the server (www.example.com)
- [various optional headers](https://en.wikipedia.org/wiki/List_of_HTTP_header_fields#Request_fields)


After receiving the request, the server sends back a message with a status code, and if possible, the requested file.

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

HTTP defines methods to indicate the requested action to be performed. The subject requires at least three :

- GET : method to request a representation of the resource's state. It should only retrieve data (ex: receiving some html code)
- POST : method to request the process of the representation sent in the request (ex: posting a message online in a forum)
- DELETE : method to request the deletion of the resource's state

# HTTP Status and Errors

1xx informational response – the request was received, continuing process

2xx successful – the request was successfully received, understood, and accepted

3xx redirection – further action needs to be taken in order to complete the request

4xx client error – the request contains bad syntax or cannot be fulfilled

5xx server error – the server failed to fulfil an apparently valid request

# Config File

The configuration file takes inspiration from the "server" part of an NGINX configuration file. A simple example is :


```
server {

	listen			0.0.0.0:80
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
	error_page 404			./data/my_website/error_files/404.html
}
```


### listen
Sets the address of the host (here: 0.0.0.0) and port (here: 80) on which the server will receive requests

### server_name
Sets names of the virtual server (here: my_website and my_website.com)

### location
Sets the correct routes within the file system (here: ex: my_website.com/home.html redirects to ./data/my_website/home.html)

### root
Sets the path the URI will be added to (here: ex: ./data/my_website)

### index
The default file to load if the request ends with '/' (here: ./data/my_website/index.html)

### autoindex
If "on" and no index file are set, requests ending with '/' produces a list of files and folders within the requested directory

### client_body_buffer_size
Sets the buffer size to read from a client request body, meaning any POST actions. If the request body is larger, part or the whole body is written in a temporary file

### allow_methods
Sets the methods that the server accepts requests of

### Example
The server receives a request one a port they listen to (here: 80) or by server name (here: my_website.com)

The request is : http://my_website.com/hello/home.html:80

The URI is : hello/home.html

The location block that best matches the URI is : /

Therefore the root is : ./data/my_website

The server will send back : ./data/my_website/hello/home.html

If the server does not find the requested file, it will send a response with the appropriate error (in this case : error 404).


# Setting up errors in the config file

When a request results in a error, the server sends back the right code and a error file, for example :

```
<html>
	<head>
		<title>404 Not Found</title>
	</head>
	<body>
		<center>
			<h1>404 Not Found</h1>
		</center>
		<hr><center>nginx/1.22.1</center>
	</body>
</html>
```

In the configuration file, this redirection is setup with the directive "error_page", followed by the error code (here: 404) and the file to send back (here: ./data/my_website/error_files/404.html)


# Poll(), Select(), Kqueue() and Epoll()


# CGI

The CGI (Common Gateway Interface) is a interface which allows a web server send or receive datas of an application as a data base. A CGI script send a web server request to an application. The script receive the application data and transfer to a web client (browser).

![](https://www.ionos.fr/digitalguide/fileadmin/_processed_/0/c/csm_une-interface-common-gateway_92a25b62a1.png)

> Example with a form : in an online form, candidacy or registration, the input datas are process by a CGI before send to a server

## Useful variables

| CONTENT_LENGTH 	| Size in octets of the content                                 	|
| CONTENT_TYPE   	| Type of the content                                           	|
| QUERY_STRING   	| String as URL                                                 	|
| REQUEST_METHOD 	| Contains the use methods (GET, POST, HEAD, PUT, DELETE, LINK) 	|

# Contributors

[agatocherry](https://github.com/agatocherry)

[kejebane](https://github.com/britney94)

[shdorlin](https://github.com/shell02)

# Resources

[Helpful documentation by 42 students](https://webserv42.notion.site/Webserv-cbb6ab4136ba4b4c8cb4f98109d5fc1f)

[Tutorial by 42 cclaude student](https://github.com/cclaude42/webserv)

## HTTP

[Wikipedia](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol)

[Request methods](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods)

[BD for understanding what HTTPS is](https://howhttps.works/fr/)

[Errors code (but with cat meme)](https://http.cat/)

[RCF 9110](https://datatracker.ietf.org/doc/html/rfc9110)

## NGINX

[Beginners's guide](http://nginx.org/en/docs/beginners_guide.html#conf_structure)

[Some useful definitions](http://nginx.org/en/docs/http/ngx_http_core_module.html)

## CGI

[What is it (fr)](https://www.ionos.fr/digitalguide/sites-internet/developpement-web/quest-ce-que-la-cgi/)
