#include <stdlib.h>
#include <string.h>
#include "dssock.h"
#include "service.h"

struct DSServiceClient {
    DSSocket *socket;
};

static DSSocket *server_socket = NULL;
static DSServiceClient clients[SERVICE_MAX_CONNS];

void start_service() {
    if(server_socket) {
        return;
    }

    for(size_t i = 0; i < SERVICE_MAX_CONNS; ++i) {
        memset(&clients[i], 0, sizeof(DSServiceClient));
    }

    server_socket = new_socket();
    open_server_socket(server_socket, "127.0.0.1", 4047);
}

static void close_client_connection(DSServiceClient * const client) {
    close_socket(client->socket);
    free_socket(client->socket);

    client->socket = NULL;
}

inline static int is_client_connected(DSServiceClient * const client) {
    return client->socket != NULL;
}

inline static DSServiceClient *get_free_client() {
    for(size_t i = 0; i < SERVICE_MAX_CONNS; ++i) {
        if(!is_client_connected(&clients[i])) {
            return &clients[i];
        }
    }

    return NULL;
}

void shutdown_service() {
    for(size_t i = 0; i < SERVICE_MAX_CONNS; ++i) {
        if(is_client_connected(&clients[i])) {
            close_client_connection(&clients[i]);
        }
    }

    close_socket(server_socket);
    free_socket(server_socket);

    server_socket = NULL;
}

static void service_loop_accept() {
    static DSSocket *next_socket = NULL;

    if(!next_socket) {
        next_socket = new_socket();
    }

    if(get_next_socket_connection(server_socket, next_socket)) {
        DSServiceClient *next_client = get_free_client();

        if(!next_client) {
            // Max connected clients reached
            close_socket(next_socket);
        }

        next_client->socket = next_socket;
        next_socket = NULL; // Will be allocated at next loop
    }
}

static void service_loop_register() {
    for(size_t i = 0; i < SERVICE_MAX_CONNS; ++i) {
        DSServiceClient * const client = &clients[i];
    }
}

void service_loop_once() {
    service_loop_accept();
    service_loop_register();
}
