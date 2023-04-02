#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {

    int client_fd;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( client_fd < 0 ){
        perror("Error socket: ");
    }

    int port = 8140;

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    int connection_accepted_code;

    int connect_ret = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    int recv_ret = recv(client_fd, &connection_accepted_code, sizeof(connection_accepted_code), 0);

    if ( connect_ret < 0 ) {
        cout << "Error code: " << errno << endl;
        if (errno == ECONNREFUSED) {
            cout << "Connection refused by server\n" << endl;
        } else {
            perror("Error connecting to server");
        }
    }

    if ( connection_accepted_code == 1 ) {
        cout << "Connection to server accepted. Server is ready to accept messages." << endl;

    }

    int index = 0;
    int num_of_prints = 10;

    if ( argc < 2 || ( string(argv[1]).length() == 0 ) ) {
        cout << "No Computer ID or irregular Computer ID provided" << endl;
        exit(1);
    }

    string Computer_ID = string(argv[1]);

    cout << "User provided CID = " <<  Computer_ID << endl;

    char buffer[1024];

    string CID = to_string(index + 1);

    string msg1 = "SPL," + Computer_ID + ".1,###";
    string msg3 = "END," + Computer_ID + ".1,###";
    string msg4 = "TRM," + Computer_ID + ".1,###";

    strcpy(buffer, msg1.c_str());
    recv_ret = send(client_fd, buffer, sizeof(buffer), 0);

    for ( int i = 0; i < num_of_prints; i++ ) {
        usleep( ( 1.5 ) * 1000000);
        
        string msg2 = "PRT," + Computer_ID + ".1,AC:" + to_string(5 * i);

        strcpy(buffer, msg2.c_str());
        recv_ret = send(client_fd, buffer, sizeof(buffer), 0);
    }

    usleep( ( index + 1 ) * 1000000);
    strcpy(buffer, msg3.c_str());
    recv_ret = send(client_fd, buffer, sizeof(buffer), 0);

    usleep( ( index + 1 ) * 10000000);
    strcpy(buffer, msg4.c_str());
    recv_ret = send(client_fd, buffer, sizeof(buffer), 0);

    usleep( ( index + 1 ) * 10000000);

}