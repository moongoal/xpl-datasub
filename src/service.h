#ifndef SERVICE_H
#define SERVICE_H

// Maximum allowed connections
#define SERVICE_MAX_CONNS 16

struct DSServiceClient;
typedef struct DSServiceClient DSServiceClient;
typedef DSServiceClient *DSServiceClientHandle;

/**
 * Start the network service.
 */
void start_service();

/*
 * Stop the network service.
 */
void shutdown_service();

/**
 * Run one iteration of the service loop.
 */
void service_loop_once();

#endif // SERVICE_H
