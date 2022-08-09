#include "stdio.h"

extern int send_can_msg(void *);
extern int send_enet_msg(void *);
extern int send_serial_msg(void *);

#define CANT_ROUTE_MSG -1

enum e_msg_type
{
    CAN_BUS,
    ENET,
    SERIAL,
    INVALID
};
typedef enum e_msg_type t_msg_type;


int route_msg(t_msg_type msg_type, void *msg)
{
    int rc;

    if (msg_type >= INVALID)
    {
        return(CANT_ROUTE_MSG);
    }

    switch (msg_type)
    {
    case CAN_BUS:
        rc = send_can_msg(msg);
        break;
    case ENET:
        rc = send_enet_msg(msg);
        break;
    case SERIAL:
        rc = send_serial_msg(msg);
        break;
    default:
        printf("\nBad Message Type");
        rc = CANT_ROUTE_MSG;
    }

    return(rc);

}

