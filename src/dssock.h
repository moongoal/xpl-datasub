#ifndef DSSOCK_H
#define DSSOCK_H

#define DSSOCK_BACKLOG 16

struct DSSocket;
typedef struct DSSocket DSSocket;

DSSocket *new_socket();
void free_socket(DSSocket * const s);
void open_server_socket(DSSocket * const s, const char * const ip_addr, unsigned short int port);
void close_socket(DSSocket * const s);
void set_socket_non_blocking(DSSocket * const s);
int get_next_socket_connection(DSSocket * const s, DSSocket * const c);
int recv_from_socket(DSSocket * const s, char *const buf, size_t const buf_sz);

#endif // DSSOCK_H
