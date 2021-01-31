#ifndef DSSOCK_H
#define DSSOCK_H

#define DSSOCK_BACKLOG 16

struct DSSocket;
typedef struct DSSocket DSSocket;

/**
 * Allocate a new socket object.
 *
 * @note Objects allocated by this function must be freed by calling `free_socket()`.
 */
DSSocket *new_socket();

/**
 * Free an object allocated by `new_socket()`.
 *
 * @param s Pointer to the socket to deallocate.
 */
void free_socket(DSSocket * const s);

/**
 * Open a server socket.
 *
 * @param s Pointer to the server socket memory.
 * @param ip_addr String representation of the IP address.
 * @param port The port where the server will listen to new connections.
 */
void open_server_socket(DSSocket * const s, const char * const ip_addr, unsigned short int port);

/**
 * Close an open socket.
 *
 * @param s Pointer to the socket to close.
 */
void close_socket(DSSocket * const s);

/*
 * Set the socket as non-blocking.
 *
 * @param s The socket.
 */
void set_socket_non_blocking(DSSocket * const s);

/**
 * If any new connection is incoming, accept the connection and
 * allocate its socket in `c`.
 *
 * @param s The server socket.
 * @param c Pointer to the memory that will be populated with the new socket.
 *
 * @return 1 if a new connection has been established; `c` will contain the
 *  socket for the new connection. 0 if no connection is waiting.
 *
 * @note `c` may be modified by this function even if no connection is accepted.
 */
int get_next_socket_connection(DSSocket * const s, DSSocket * const c);

/**
 * Receive data from a socket.
 *
 * @param s The socket to receive data from.
 * @param buf The output buffer where the received data will be stored.
 * @param buf_sz The size of `buf` in bytes.
 *
 * @return 0 if no data is available, -1 if the socket must be closed, the size
 *  of the received data otherwise.
 */
int recv_from_socket(DSSocket * const s, char *const buf, size_t const buf_sz);

#endif // DSSOCK_H
