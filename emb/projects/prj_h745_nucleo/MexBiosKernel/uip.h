
#ifndef __UIP__
#define __UIP__

#define HTTP_ENABLE         1
#define DHCP_ENABLE         1

#if HTTP_ENABLE && DHCP_ENABLE
#define UIP_BUFSIZE         0x0300
#elif HTTP_ENABLE
#define UIP_BUFSIZE         0x0300
#elif DHCP_ENABLE
#define UIP_BUFSIZE         0x0260
#else
#define UIP_BUFSIZE         0x0130
#endif

#define UIP_STATUS_FAILED   0x1
#define UIP_STATUS_LINKUP   0x2
#define UIP_STATUS_SENDERR  0x4

typedef struct {
	char            SlaveID;
	unsigned short  DeviceNumber;
	unsigned short  VersionNumber;
	unsigned short  VersionDate;
	const char     *DeviceInfo;
	const char     *DeviceDescr;
} UIP_SLAVE_INFO;

typedef struct {
	char  state;
	char  rsvd;
	char  serverid[4];
	char  lease_time[4];
	char  ipaddr[4];
	char  netmask[4];
	char  dnsaddr[4];
	char  default_router[4];
	short timeout;
	short timer;
} DHCPS;

typedef short *(*TUipGetData)(unsigned short,unsigned short,unsigned short *);
typedef short *(*TUipGetRecord)(short, short, short, char *, char *);

typedef struct {
	char   macaddr[6];
	char   ipaddr[4];
	char   tcpSlave;
	short  tcpPort;
	char   dhcpEnable;
} UIP_PARAMS;

typedef struct {
	void  *data;
	short  len;
	short  mode;
} UIP_DATA_BUF;

typedef struct {
	short        clientPort;
	short        serverPort;
	char         macId;
	char         ipId;
	UIP_DATA_BUF rxBuf;
	UIP_DATA_BUF txBuf;
} UIP_UDP_CLIENT;

typedef struct {
	short        port;
	short        rxLen;
	UIP_DATA_BUF rxBuf;
	UIP_DATA_BUF txBuf;
} UIP_UDP_SERVER;

typedef struct {
	short  periodMs;
	char   status;
	char   wrFlag;
	char   current_bank;
	short  rxrdpt;
	short  info_hdr_len;
	short  info_data_len;
	char   http_seqnum;
	char   tcp_seqnum;
	short  ipid;
	short  tickPeriod;
	short  ackTimer;
	char   ackFlag;
	short  tcp_rx_bytes;
	short  tcp_tx_bytes;
	char   connected;
	short  connTimer;
	short  connTimeout;
	#if DHCP_ENABLE
	DHCPS  dhcp;
	#endif
	char   buf[UIP_BUFSIZE];
	UIP_PARAMS     *Params;
	UIP_SLAVE_INFO *SlaveInfo;
	char (*SendFunc)(char);
	void (*CsFunc)(char);
	TUipGetData     GetData;
	TUipGetRecord   GetRecord;
	UIP_UDP_CLIENT *UdpClient;
	UIP_UDP_SERVER *UdpServer;
} UIP_PORT;

void uip_init(UIP_PORT *);
void uip_process(UIP_PORT *);
void uip_periodic(UIP_PORT *);

#endif /* __UIP__ */


