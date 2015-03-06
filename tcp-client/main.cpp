#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define LINE_ARRAY_SIZE (MAX_LINE+1)

using namespace std;

int main()
{
  int socketDescriptor;
  unsigned short int serverPort;
  struct sockaddr_in serverAddress;
  struct hostent *hostInfo;
  char buf[LINE_ARRAY_SIZE], c;

  cout << "Enter server host name or IP address: ";
  cin.get(buf, MAX_LINE, '\n');

  // gethostbyname() elkapja a hostname-et vagy IP-t "számok és pontok"
  // formátumban, és a hostent struct-ra mutató pointert ad vissza,
  // ezt használjuk később.
  // It's not important for us what this structure is actually composed of.
  hostInfo = gethostbyname(buf);
  if (hostInfo == NULL) {
    cout << "problem interpreting host: " << buf << "\n";
    exit(1);
  }

  cout << "Enter server port number: ";
  cin >> serverPort;
  cin.get(c); // dispose of the newline

  // Csinál egy socket-et  "AF_INET" miatt IPv4 protocolt használ
  // "SOCK_STREAM" megbízható kapcsolatot azonosít (TCP; UDP-nél SOCK_DGRAM kell)
  // az utolsó paramétert megnézni!!!! (0)
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    cerr << "cannot create socket\n";
    exit(1);
  }

  // Kapcsolódik a szerverhez. Először beállítjuk a mezőket a serverAddress struc-ban
  // A rendszer az általunk megadott local portra állít, ha nincs használatban

  serverAddress.sin_family = hostInfo->h_addrtype;
  memcpy((char *) &serverAddress.sin_addr.s_addr,
         hostInfo->h_addr_list[0], hostInfo->h_length);
  serverAddress.sin_port = htons(serverPort);

  if (connect(socketDescriptor,
              (struct sockaddr *) &serverAddress,
              sizeof(serverAddress)) < 0) {
    cerr << "cannot connect\n";
    exit(1);
  }

  cout << "\nA beirt sorokat a szerver nagybetuskent visszairja\n";
  cout << "bevitel vége: csak pontot tartalmazó sor\n";
  cout << "Ha a bevitt karakterek száma több, mint " << MAX_LINE << "\n";
  cout << "akkor csak az első " << MAX_LINE << " karaktert dolgozza fel.\n\n";

  // kiírja a fenti szöveget, aztán input-ot olvas a MAX_LINE-ig
  // a többit, a sor végét ("\n") levágja

  cout << "Input: ";
  cin.get(buf, MAX_LINE, '\n');
  while (cin.get(c) && c != '\n')
    ;

  // Pontra megállítja az input olvasást
  while (strcmp(buf, ".")) {
    // Elküldi a szervernek
    if (send(socketDescriptor, buf, strlen(buf) + 1, 0) < 0) {
      cerr << "cannot send data ";
      close(socketDescriptor);
      exit(1);
    }

    // buffert nulláz.
    memset(buf, 0x0, LINE_ARRAY_SIZE);

    // visszaolvassa a szervertől a küldött sort
    if (recv(socketDescriptor, buf, MAX_LINE, 0) < 0) {
      cerr << "didn't get response from server?";
      close(socketDescriptor);
      exit(1);
    }

    cout << "Modified: " << buf << "\n";

    // Prompt-ot ad, input-ot olvas a MAX_LINE karakterig,
    // levágja a végét ("\n"-et is). Mint az előzőnél

    cout << "Input: ";
    cin.get(buf, MAX_LINE, '\n');
    while (cin.get(c) && c != '\n')
      ;
  }

  close(socketDescriptor);
  return 0;
}
