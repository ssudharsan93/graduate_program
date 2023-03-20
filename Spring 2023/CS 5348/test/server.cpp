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

int main() {

    queue<int> *connection_queue = new queue<int>();
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( server_fd < 0 ){
        perror("Error socket: ");
    }

    int port = 8140;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    int bind_ret = bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if ( bind_ret < 0 ) {
        perror("Error bind: ");
    }

    listen(server_fd, 1);
    
    while ( true ) {
        cout << "Server is listening..." << endl;
        usleep(100000);
        int new_conn = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t*) &client_addrlen);
        char client_ip_address[INET_ADDRSTRLEN];
        const char *ip_address = inet_ntop(AF_INET, &client_addr.sin_addr, client_ip_address, INET_ADDRSTRLEN);
        //cout << "Connection Accepted from " << inet_ntoa(client_addr.sin_addr) << " Port: " << client_addr.sin_port << endl;
        cout << "Connection Accepted from " << ip_address << " Port: " << client_addr.sin_port << endl;

        if ( connection_queue->size() == 1 ) {
            cout << "Already have one connection in the queue." << endl;
            close(new_conn);
        } else {
            cout << "No connections in the queue." << endl;
            connection_queue->push(new_conn);
        }

        string my_msg = "Hello Client.\n";
        char server_msg[my_msg.size() + 1];
        strcpy(server_msg, my_msg.c_str());
        send(new_conn, server_msg, sizeof(server_msg), 0);

    }

    delete connection_queue;

}