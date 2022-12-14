### Configuration file :
```
--------------------------------
server {
  listen:       80
  server_name:  data.com
  
  location / {
    root          ./data/
    index         index.html
    allow_methods GET POST
  }
}

server {
  listen:       80
  server_name:  website.com
}

server {
  listen:       81
  server_name:  lofi.com
}
--------------------------------
```

### Some explaination 
Classe principale 
- Webserver

Webserver
- une classe ConfigInfo
- autant de classes Server que de sockets (std::map<int, Server>)
          
ConfigInfo 
- autant de classes Server que de sockets (std::map<int, Server>)
- fonction parse(filename)
  - une ligne "server {" veut dire : creation d'une instance ServerInfo
  - une ligne "listen" veut dire : recherche dans std::map<int, Server> s'il existe deja un Server pour le int port --> si non, creation d'une nouvelle instance Server; si oui, addNewInfo a l'instance Server qui ecoute deja le bon port
  - une ligne "location" veut dire : ajout d'une structure Location dans ServerInfo
  - remplir ServerInfo avec toutes les informations restantes
- int _size = map.size()

Avec ce fichier de configuration, il y aura donc 2 instances de la classe Server car deux sockets :
- une instance Server avec deux ServerInfo (un pour data.com, l'autre pour website.com) qui a un socket connecte au port 80
- une instance Server avec un ServerInfo (un pour lofi.com) qui a un socket connecte au port 81

Server 
- un pointeur vers l'instance ServerInfo a utilise par defaut
- fonction getSocket() qui renvoie le socket connecte a un port, pour que la classe principale puisse ajoute tous les sockets a la fonction select()
- fonction addNewInfo() qui prend en parametre une instance de la classe ServerInfo et l'ajoute au vecteur
