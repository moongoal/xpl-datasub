#define DSSOCK_IMPL
#include <memory.h>
#include <string.h>
#include <Windows.h>
#include "dssock.h"

typedef struct DSSocket {
    SOCKET socket;
} DSSocket;

void open_server_socket(DSSocket * const s,const char * const ip_addr, unsigned short int port) {
    memset(s, 0, sizeof(DSSocket));

    s.socket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP
    );

    if(s.socket == INVALID_SOCKET) {
        // Error
        abort();
    }

    // Set socket options
    const BOOL reuse_addr = TRUE;

    setsockopt(
        s.socket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &reuse_addr,
        sizeof(reuse_addr)
    );

    // Set non-blocking mode
    set_socket_non_blocking(s);

    // Bind & listen
    sockaddr_in service;

    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(ip_addr);
    service.sin_port = htons((u_short)port);

    if(bind(s.socket, (SOCKADDR *) &service, sizeof(sockaddr_in))) {
        // Error
        abort();
    }

    if(listen(s.socket, DSSOCK_BACKLOG)) {
        // Error
        abort();
    }
}

void close_socket(DSSocket * const s) {
    shutdown(
        s.socket,
        SD_BOTH
    );

    memset(s, 0, sizeof(DSSocket));
}

void set_socket_non_blocking(DSSocket * const s) {
    unsigned long blocking = 0;

    ioctlsocket(
        s.socket,
        FIONBIO,
        &blocking
    );
}

int get_next_socket_connection(DSSocket * const s, DSSocket * const c) {
    sockaddr addr;
    int addr_len;

    c.socket = accept(
        s.socket,
        &addr,
        &addr_len
    );

    if(c.socket == INVALID_SOCKET) {
        int last_error = WSAGetLastError();

        if(last_error == WSAEWOULDBLOCK) {
            return 0; // No connection available
        } else {
            // Error
            abort();
        }
    } else {
        // Connected!
        set_socket_non_blocking(c);

        return 1;
    }
}

DSSocket *new_socket() {
    return malloc(sizeof(DSSocket));
}

void free_socket(DSSocket * const s) {
    free(s);
}

int recv_from_socket(DSSocket * const s, char *const buf, size_t const buf_sz) {
    int read_bytes = recv(
        s.socket,
        buf,
        buf_sz,
        0
    );

    if(read_bytes == SOCKET_ERROR) {
        int error = WSAGetLastError();

        switch(error) {
            case WSAEWOULDBLOCK:
                return 0; // No data available

            default:
                return -1; // Error, close the connection
        }
    } else if (read_bytes == 0) {
        // Connection gracefully closed
        return -1; // Close the socket
    }

    return read_bytes; // Data succesfully read
}
