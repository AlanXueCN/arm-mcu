/* WizNet W5200 Register Definitions */

// $Id$

#include <stdint.h>

// Common Registers

#define	W5200_MR		0x0000
#define W5200_GAR		0x0001
#define W5200_SUBR		0x0005
#define W5200_SHAR		0x0009
#define W5200_SIPR		0x000F
#define W5200_IR		0x0015
#define W5200_IMR		0x0016
#define W5200_RTR		0x0017
#define W5200_RCR		0x0019
#define W5200_PATR		0x001C
#define W5200_PPPALGO		0x001E
#define W5200_PTIMER		0x0028
#define W5200_PMAGIC		0x0029
#define W5200_INTLEVEL		0x0030
#define W5200_IR2		0x0034
#define W5200_PSTATUS		0x0035
#define W5200_IMR2		0x0036

// Socket Registers

#define W5200_MAX_SOCKETS	8

#define W5200_SOCKET_REG(s)	(0x4000 + (s << 8))

#define W5200_Sn_MR(s)		(W5200_SOCKET_REG(s) + 0x00)
#define W5200_Sn_CR(s)		(W5200_SOCKET_REG(s) + 0x01)
#define W5200_Sn_IR(s)		(W5200_SOCKET_REG(s) + 0x02)
#define W5200_Sn_SR(s)		(W5200_SOCKET_REG(s) + 0x03)
#define W5200_Sn_PORT(s)	(W5200_SOCKET_REG(s) + 0x04)
#define W5200_Sn_DHAR(s)	(W5200_SOCKET_REG(s) + 0x06)
#define W5200_Sn_DIPR(s)	(W5200_SOCKET_REG(s) + 0x0C)
#define W5200_Sn_DPORT(s)	(W5200_SOCKET_REG(s) + 0x10
#define W5200_Sn_MSSR(s)	(W5200_SOCKET_REG(s) + 0x12)
#define W5200_Sn_PROTO(s)	(W5200_SOCKET_REG(s) + 0x14)
#define W5200_Sn_IP_TOS(s)	(W5200_SOCKET_REG(s) + 0x15)
#define W5200_Sn_IP_TTL(s)	(W5200_SOCKET_REG(s) + 0x16)
#define W5200_Sn_RXMEMSIZE(s)	(W5200_SOCKET_REG(s) + 0x1E)
#define W5200_Sn_TXMEM_SIZE(s)	(W5200_SOCKET_REG(s) + 0x1F)
#define W5200_Sn_TX_FSR(s)	(W5200_SOCKET_REG(s) + 0x20)
#define W5200_Sn_TX_RD(s)	(W5200_SOCKET_REG(s) + 0x22)
#define W5200_Sn_TX_WR(s)	(W5200_SOCKET_REG(s) + 0x24)
#define W5200_Sn_RX_RSR(s)	(W5200_SOCKET_REG(s) + 0x26)
#define W5200_Sn_RX_RD(s)	(W5200_SOCKET_REG(s) + 0x28)
#define W5200_Sn_RX_WR(s)	(W5200_SOCKET_REG(s) + 0x2A)
#define W5200_Sn_IMR(s)		(W5200_SOCKET_REG(s) + 0x2C)
#define W5200_Sn_FRAG(s)	(W5200_SOCKET_REG(s) + 0x2D)

// W5200 register bit masks

#define W5200_MR_RST		0x80
#define W5200_MR_PB		0x10
#define W5200_MR_PPPOE_ENABLE	0x08

#define W5200_IR_CONFLICT	0x80
#define W5200_IR_PPPOE_CLOSE	0x20

#define W5200_IMR_CONFLICT	0x80
#define W5200_IMR_PPPOE_CLOSE	0x20

#define W5200_PSTATUS_LINK	0x20
#define W5200_PSTATUS_POWERDOWN	0x08

#define W5200_Sn_MR_MULTI	0x80
#define W5200_Sn_MR_MF		0x40
#define W5200_Sn_MR_ND		0x20
#define W5200_Sn_MR_MC		0x20
#define W5200_Sn_MR_CLOSED	0x00
#define W5200_Sn_MR_TCP		0x01
#define W5200_Sn_MR_UDP		0x02
#define W5200_Sn_MR_IPRAW	0x03
#define W5200_Sn_MR_MACRAW	0x04

#define W5200_Sn_CR_OPEN	0x01
#define W5200_Sn_CR_LISTEN	0x02
#define W5200_Sn_CR_CONNECT	0x04
#define W5200_Sn_CR_DISCON	0x08
#define W5200_Sn_CR_CLOSE	0x10
#define W5200_Sn_CR_SEND	0x20
#define W5200_Sn_CR_SEND_MAC	0x21
#define W5200_Sn_CR_SEND_KEEP	0x22
#define W5200_Sn_CR_RECV	0x40

#define W5200_Sn_SR_SOCK_CLOSED		0x00
#define W5200_Sn_SR_SOCK_ARP		0x01
#define W5200_Sn_SR_SOCK_INIT		0x13
#define W5200_Sn_SR_SOCK_LISTEN		0x14
#define W5200_Sn_SR_SOCK_SYNSENT	0x15
#define W5200_Sn_SR_SOCK_SYNRECV	0x16
#define W5200_Sn_SR_SOCK_ESTABLISHED	0x17
#define W5200_Sn_SR_SOCK_FIN_WAIT	0x18
#define W5200_Sn_SR_SOCK_CLOSING	0x1A
#define W5200_Sn_SR_SOCK_TIME_WAIT	0x1B
#define W5200_Sn_SR_SOCK_CLOSE_WAIT	0x1C
#define W5200_Sn_SR_SOCK_LAST_ACK	0x1D
#define W5200_Sn_SR_SOCK_UDP		0x22
#define W5200_Sn_SR_SOCK_IPRAW		0x32
#define W5200_Sn_SR_SOCK_MACRAW		0x42
#define W5200_Sn_SR_SOCK_PPPOE		0x5F

// W5200 driver functions

int W5200_write_register(const uint16_t address, const uint8_t data);

int W5200_read_register(const uint16_t address, uint8_t *data);

int W5200_initialize(const uint32_t spiportnum);

int W5200_set_hardware_address(const macaddress_t address);

int W5200_get_hardware_address(macaddress_t address);

int W5200_configure_network(const ipv4address_t address,
                            const ipv4address_t subnet,
                            const ipv4address_t gateway);

int W5200_get_ipaddress(ipv4address_t address);

int W5200_get_linkstate(int *linkstate);

void W5200_tick(void);
