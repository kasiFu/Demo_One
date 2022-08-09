
#include "stdlib.h"
#include "string.h"
#include "datalink_types.h"
#include "datalink_hdwr_tx.h"



#define MAX_TIME 10


t_msg_sts data_tx_V1( unsigned char *msg, unsigned char msg_len )
{
    int timeout_ctr=0;
    int i=0;

    if (!msg)
    {
        return(BAD_PTR);
    }

    if ((msg_len < MIN_MSG_LEN)  || (msg_len > MAX_MSG_LEN))
    {
        return(BAD_MSG);
    }

/*
#define HW_STS_REG  ((unsigned char *)0x8000000)
#define HW_DATA_REG ((unsigned char *)0x8000004)
*/

    while (i < msg_len)
    {
        *HW_STS_REG = L1_RTS;
        if (*HW_STS_REG & L1_CTS)
        {
            timeout_ctr = 0;
            HW_DATA_REG[i++] = *msg++;
        }
        else
        {
            if (++timeout_ctr > MAX_TIME)
            {
                reset_transmitter();
                log_msg(msg, msg_len);
                return(TX_BAD);
            }
        }
    }

    return(TX_GOOD);

}



t_msg_sts data_tx_V2( unsigned char *data_ptr, unsigned char data_len )
{
    int timeout_ctr=0;
    int i=0;

    if (!data_ptr)
    {
        return(BAD_PTR);
    }

    while (i < data_len)
    {
        hw_send_rts();
        if (hw_check_cts())
        {
            timeout_ctr = 0;
            hw_tx_byte(*data_ptr++);
            i++;
        }
        else
        {
            if (++timeout_ctr > MAX_TIME)
            {
                reset_transmitter();
                log_msg(data_ptr, data_len);
                return(TX_BAD);
            }
        }
    }

    return(TX_GOOD);

}

static int log_flag=1;
t_msg_sts pkt_transmit( unsigned char *msg, unsigned char msg_len, unsigned char msg_num )
{
    t_msg_packet pkt;
    int rc;
    char log_buf[200];


    if (!msg)
    {
        return(BAD_PTR);
    }

    if ((msg_len < MIN_MSG_LEN) || (msg_len > MAX_MSG_LEN))
    {
        return(BAD_MSG);
    }

    pkt.hdr.len = msg_len + sizeof(pkt.hdr);
    pkt.hdr.num = msg_num; 
    pkt.hdr.crc = calc_crc(msg, msg_len);

    memcpy(pkt.data, msg, msg_len);

    rc = data_tx_V2( (unsigned char *)&pkt, sizeof(t_msg_hdr) + msg_len );

    if (log_flag)
    {
        strncpy(log_buf, "Message Transmitted: ", sizeof(log_buf));
        strncat(log_buf, msg, sizeof(log_buf));
        log_msg( log_buf, sizeof(log_buf) );
    }


    return(rc);
}

