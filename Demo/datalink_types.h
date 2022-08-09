#ifndef DATALINK_TYPES_H
#define DATALINK_TYPES_H

#ifdef VCAST_MICROSOFT_LONG_LONG
#define inline __inline  // MS Studio uses different syntax for inline
#endif


extern int log_msg(void *msg, int msg_len);
extern int calc_crc(void *msg, int msg_len);
extern void reset_transmitter(void);


enum e_msg_sts
{
  BAD_PTR = -1,
  BAD_MSG = -2,
  TX_GOOD = 0,
  TX_BAD,
  RX_GOOD,
  RX_BAD,
};
typedef enum e_msg_sts t_msg_sts;

#define HW_STS_REG  ((unsigned char *)0x8000000)
#define HW_DATA_REG ((unsigned char *)0x8000004)

#define L1_RTS 1
#define L1_CTS 1
#define L1_TX_COMPLETE 2
#define L1_RX_DATA_RDY 2
#define L1_LOOPBACK_MODE 4

#define MIN_MSG_LEN  1
#define MAX_MSG_LEN  100


struct s_msg_hdr
{
    unsigned char  len;
    unsigned char  num;
    unsigned char  crc;
};
typedef struct s_msg_hdr t_msg_hdr;

struct s_msg_packet
{
    t_msg_hdr       hdr;
    unsigned char   data[MAX_MSG_LEN];
};
typedef struct s_msg_packet t_msg_packet;

#endif
