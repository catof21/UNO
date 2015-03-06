#include <arpa/inet.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_MSG 100
#define LINE_ARRAY_SIZE (MAX_MSG+1)

using namespace std;

int main()
{
  int listenSocket, connectSocket, i,j;
  unsigned short int listenPort;
  socklen_t clientAddressLength;
  struct sockaddr_in clientAddress, serverAddress;
  char line[LINE_ARRAY_SIZE];

  cout << "Enter port number to listen on (between 1500 and 65000): ";
  cin >> listenPort;

  // Listening Socket-et hoz létre a kliens(ek) kéréseihez
  listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocket < 0) {
    cerr << "cannot create listen socket";
    exit(1);
  }

  // Listen socket és listen port összekötése. Csinál egy
  // serverAddress struct-ot, aztán bind().
  // a htonl() és a htons() konvertálja a long integers-t és a short integers-t
  // a host byte order-ről
  //(on x86 this is Least Significant Byte first) to network byte order (Most Significant Byte first).
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(listenPort);

  if (bind(listenSocket,
           (struct sockaddr *) &serverAddress,
           sizeof(serverAddress)) < 0) {
    cerr << "cannot bind socket";
    exit(1);
  }

  // Vár a kliens kapcsolódásra
  // nem blokkoló hívás, regisztrálja a hívást a rendszer
  // ezen a socket-en, és aztán ezen a thread-en fut tovább

  listen(listenSocket, 5);

  while (1) {
    cout << "Waiting for TCP connection on port " << listenPort << " ...\n";

    // Elfogadja a kapcsolatot a kérő klienssel
    // accept() call is a blocking call; i.e., this thread of
    // execution stops until a connection comes in.
    // connectSocket is a new socket that the system provides,
    // separate from listenSocket.
    // ide kell, hogy multikapcsolat is lehessen!
    // a connectSocket bezárása előtt nem tud más csatlakozni
    clientAddressLength = sizeof(clientAddress);
    connectSocket = accept(listenSocket,
                           (struct sockaddr *) &clientAddress,
                           &clientAddressLength);
    if (connectSocket < 0) {
      cerr << "cannot accept connection ";
      exit(1);
    }

    // Kliens IP-jét megmutatja
    // inet_ntoa() konvertálja az IP-t binary-ból olvashatóvá
    cout << "  connected to " << inet_ntoa(clientAddress.sin_addr);

    // Kliens Port-ját mutatja
    // ntohs() konvertálja a Port-ot a short int-et network byte-tá,
    cout << ":" << ntohs(clientAddress.sin_port) << "\n";

    // Socket-ről olvas a recv(), eltárolja a line tömbben
    // Ha nincs pillanatnyilag üzenet, a recv() vár/blokkol amíg
    // nem jön valami.
    // Nullázza a line-t először, így tudjuk a string végét
    // j csak sorszám
    j=1;
    memset(line, 0x0, LINE_ARRAY_SIZE);
    while (recv(connectSocket, line, MAX_MSG, 0) > 0) {
      cout << j++ << "--  " << line << "\n";

      // nagybetűssé alakítja
      for (i = 0; line[i] != '\0'; i++)
        line[i] = toupper(line[i]);
      // visszaküldi a kliensnek

      if (send(connectSocket, line, strlen(line) + 1, 0) < 0)
        cerr << "Error: cannot send modified data";

      memset(line, 0x0, LINE_ARRAY_SIZE);  // set line to all zeroes
    }
  }
}
