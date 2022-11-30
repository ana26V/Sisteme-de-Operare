# Sisteme-de-Operare


Acesta este un program C care primește 2 argumente din linia de comandă: un director sursă și un director destinație.

Se parcurge recursiv structura de directoare din directorul sursă. Pentru fiecare intrare din directorul sursă, se executa următoarele operații, în funcție de tipul intrării:

Pentru directoare, se creaza un director echivalent în directorul destinație, cu aceleași drepturi ca directorul original. Astfel, structura de directoare din directorul destinație va fi asemănătoare cu cea din sursă.
Pentru fișierele obișnuite, în funcție de dimensiunea fișierului se creaza o copie sau un link:
Pentru fișierele mai mari de 500 octeți, se va crea o copie a fișierului în directorul destinație (și, după caz, în subfolderul echivalent). Aceste fișiere copie vor avea aceleași drepturi de read ca și fișierele originale, si vor primi drepturi de write pentru toata lumea (Ex: dacă fișierul original are –rwx-x-wx, fisierul nou va avea –rw-w--w--).
Pentru fisierele mai mari de 300 octeti, dar mai mici de 500 octeti, se va crea o legatura de tip hardlink catre fisierul original. Aceste linkuri vor avea aceleași drepturi de acces ca și fișierele originale.
Pentru celelalte fișiere, se vor crea legături simbolice către fișierul original. Aceste linkuri vor avea aceleași drepturi de acces ca și fișierele originale.
Pentru (soft) linkuri, nu se va executa nici o operație.
