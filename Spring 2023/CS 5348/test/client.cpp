#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

using namespace std;

int main() {

    int client_fd;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( client_fd < 0 ){
        perror("Error socket: ");
    }

    int port = 8140;

    struct sockaddr_in server_addr;
    // struct sockaddr_in client_addr;
    // int client_addrlen = sizeof(client_addr);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    struct timeval timeout;
    timeout.tv_sec = 10; // set timeout to 5 seconds
    timeout.tv_usec = 0;


    int sock_opt_ret = setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    cout << "Sock Option Return Code: " << sock_opt_ret << endl;
    if(sock_opt_ret < 0) {
        perror("Error setting socket option");
        exit(EXIT_FAILURE);
    }


    int connect_ret = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if ( connect_ret < 0 ) {
        cout << "Error code: " << errno << endl;
        if (errno == ECONNREFUSED) {
            cout << "Connection refused by server\n" << endl;
        } else {
            perror("Error connecting to server");
        }
    }
    
    char buffer[1024];
    int recv_ret = recv(client_fd, buffer, sizeof(buffer), 0);

    cout << buffer << endl;

    cout << "Connection Return Code: " << connect_ret << endl;
    cout << "Recv Return Code: " << recv_ret << endl;
        
    // string my_msg = "You Up?\n";
    // char client_msg[my_msg.size() + 1];
    // strcpy(client_msg, my_msg.c_str());
    // send(client_fd, client_msg, sizeof(client_msg), 0);

    // if (connect_ret < 0) {
    //     cout << "Connection Refused: " << strerror(errno) << endl;
    //     perror("Connection Refused: ");
    // }

    while ( true ) {
        usleep(100);
    }

}