#ifndef H_NW_SERVER
#define H_NW_SERVER

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

// #include "networking/socket_helper.h"

#define PORT_DSS 8080
#define PORT_VIDEO 2501

class dyver_server_t
{
public:
	explicit dyver_server_t() {}
	~dyver_server_t() {}

	void initialize() {}

private:
};

#endif