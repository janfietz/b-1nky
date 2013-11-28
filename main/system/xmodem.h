#ifndef XMODEM_H
#define XMODEM_H

#define XMODEM_MAX_PROTO_ERRORS     20
#define XMODEM_PACKET_SIZE          128
#define XMODEM_PACKET_SIZE_1K       1024
#define XMODEM_PACKET_SIZE_MAX      XMODEM_PACKET_SIZE_1K
#define XMODEM_MAX_TRIES            1000
#define XMODEM_GETCHAR_TIMEOUT      1      // MAX_TRIES * GETCHAR_TIMEOUT = Packet receive timeout


#define XMODEM_CHARAVAIL(x)         UART5_CharAvail(x)
#define XMODEM_GETCHAR(x)           UART5_GetChar(x)
#define XMODEM_PUTCHAR(x)           UART5_PutChar(x)

typedef enum
{
    XMODEM_ASC_TMO = 0x00,          //Timeout special
    XMODEM_ASC_SOH = 0x01,          //Ctrl-A    Start Of Heading    marks 128Bytes block
    XMODEM_ASC_STX = 0x02,          //Ctrl-B    Start Of Text       marks 1kBytes block
    XMODEM_ASC_EOT = 0x04,          //Ctrl-D    End Of Transmission
    XMODEM_ASC_ACK = 0x06,          //Ctrl-F    Acknowledge
    XMODEM_ASC_NAK = 0x15,          //Ctrl-U    Not Acknowledge
    XMODEM_ASC_CAN = 0x18,          //Ctrl-X    Cancel
    XMODEM_ASC_DBL = 0xFE,          //Error special Duplicate Received
    XMODEM_ASC_ERR = 0xFF,          //Error special
} XMODEM_ASC_E;

#define TIMEOUT 32000

XMODEM_ASC_E xmodem_packet_receive(uint8_t iPacket, uint8_t *pData, uint16_t *uLen);
bool xmodem_send_waitforstart(void);
int32_t xmodem_send(uint8_t *pData, uint16_t uLen);
bool xmodem_send_data(uint8_t *pData, uint32_t uLen);

#endif
