
#include "stdlib.h"
#include "memory.h"
#include "datalink_types.h"
#include "datalink_hdwr_rx.h"


t_msg_sts data_rx( unsigned char *data_ptr, unsigned char max_data_len)
{
    int timeout_ctr=0;
    int i=0;
    unsigned char data_len;

    if (!data_ptr)
    {
        return(BAD_PTR);
    }

    if (hw_data_avail())
    {
        *data_ptr = hw_rx_byte();  // 1st byte is the length

        data_len = *data_ptr;

        while ((i < data_len) & (i < max_data_len))
        {
            *++data_ptr = hw_rx_byte();
            i++;
        }

        hw_rx_complete();
    }

    return(RX_GOOD);

}



t_msg_sts pkt_receive( unsigned char *msg, unsigned char *msg_len )
{
    t_msg_packet pkt;
    int rc;

    if (!msg)
    {
        return(BAD_PTR);
    }

    rc = data_rx( (unsigned char *)&pkt, sizeof(pkt) );
        
    if ((pkt.hdr.len < MIN_MSG_LEN) || (pkt.hdr.len > MAX_MSG_LEN))
    {
        return(BAD_MSG);
    }

    memcpy(msg, pkt.data, pkt.hdr.len );

    *msg_len = pkt.hdr.len;

    return(rc);
}
