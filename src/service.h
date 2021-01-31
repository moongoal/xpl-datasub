#ifndef SERVICE_H
#define SERVICE_H

// Maximum allowed connections
#define SERVICE_MAX_CONNS 16

void start_service();
void shutdown_service();
void service_loop_once();

#endif // SERVICE_H
