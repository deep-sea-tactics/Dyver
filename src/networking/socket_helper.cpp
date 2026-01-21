#include "socket_helper.h"

void rx_thread(listen_socket_t *p_self, std::int16_t fd)
{
	if (p_self == nullptr)
	{
		throw std::runtime_error("Unexpected null listen socket, thread terminated forcefully.");
	}

	if (p_self->is_dead() == true)
	{
		std::terminate();
	}

	p_self->rx(fd);
}