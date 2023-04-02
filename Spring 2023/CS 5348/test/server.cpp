#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <string>
#include <queue>

using namespace std;

int set_up_printer_socket() {
    
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( server_fd < 0 ){
        perror("Error socket: ");
    }

    int port = 8140;

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    int bind_ret = bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if ( bind_ret < 0 ) {
        perror("Error bind: ");
    }

    return server_fd;

}

int main() {

    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);

    int server_fd = set_up_printer_socket();

    listen(server_fd, 1);

    cout << "Server is listening..." << endl;
    int new_conn = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t*) &client_addrlen);
    char client_ip_address[INET_ADDRSTRLEN];
    const char *ip_address = inet_ntop(AF_INET, &client_addr.sin_addr, client_ip_address, INET_ADDRSTRLEN);
    //cout << "Connection Accepted from " << inet_ntoa(client_addr.sin_addr) << " Port: " << client_addr.sin_port << endl;
    cout << "Connection Accepted from " << ip_address << " Port: " << client_addr.sin_port << endl;

    int conn_accept_code = 1;
    send(new_conn, &conn_accept_code, sizeof(conn_accept_code), 0);

    string msg;
    int recv_ret;
    
    while ( true ) {
        char buffer[1024];
        recv_ret = recv(new_conn, buffer, sizeof(buffer), 0);
        msg = string(buffer);

        if ( recv_ret > 0 ) { 
            cout << "Received message from " << ip_address << " Port: " << client_addr.sin_port << endl;
            cout << "Message: " << msg << " Message Size: "<< msg.length() << endl;
            cout << "Recv return code: " << to_string(recv_ret) << endl;
        }
    }

}