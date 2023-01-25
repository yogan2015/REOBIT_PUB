// ����:
// �������: W:\ProjectsGit\motorcontroldemo_035\cood.xml
// ������������: ������� �������
// ���� ��������: 25.12.2020 9:40:25
// ������������: default
// COODEdit Basic v.7.3.8
#include "DSP.h"
#include "main.h"
#include "cood1.h"
#include "co_ODvars.h"

// ����� 122 �������� � �������
// ����� 760 ��������� � �������
Uint16 const co1_numOfInd = 122;
// ����� ������������ ��� �����
Uint16 const co1_groupEnum = 15;
// ���-�����:
Uint32 const co1_odHash[4] = {0x5997F190, 0x22AC056B, 0xB47A12F6, 0xCDE7A7F7};
// ������� � �������� ����������
long const CO1_OD_TBL3[] = {
(long)(&co1_vars.co_deviceType),	//[1000h.00h], ��������: ��� ����������, �������: Device Type, ������: CAN
(long)(&co1_vars.co_errorRegister),	//[1001h.00h], ��������: ������� ������, �������: ErrReg, ������: CAN
(long)(&co1_vars.co_deviceState),	//[1002h.00h], ��������: Manufacturer Status Register, �������: DevSta, ������: CAN
(long)(&co1_vars.co_emcyCOBID),	//[1014h.00h], ��������: COB-ID Emergency Object, �������: eCOBID, ������: CAN
(long)(&co1_vars.co_CHBT),	//[1016h.01h], ��������: ����� �������� ��������� Heartbeat, �������: CHBT, ������: CAN
(long)(&co1_vars.co_PHBT),	//[1017h.00h], ��������: ������ ��������� ��������� Heartbeat, �������: PHBT, ������: CAN
(long)(&co1_vars.co_vendorID),	//[1018h.01h], ��������: ��� �������������, �������: VendID, ������: CAN
(long)(&co1_vars.co_productCode),	//[1018h.02h], ��������: ��� ��������, �������: PrCode, ������: CAN
(long)(&co1_vars.co_revisionNumber),	//[1018h.03h], ��������: ����� �������, �������: RevNum, ������: CAN
(long)(&co1_vars.co_serialNumber),	//[1018h.04h], ��������: �������� �����, �������: SerNum, ������: CAN
(long)(&co1_vars.co_csrxCOBID),	//[1200h.01h], ��������: COB-ID Client->Server(rx), �������: CSRXID, ������: CAN
(long)(&co1_vars.co_sctxCOBID),	//[1200h.02h], ��������: COB-ID Server->Client(tx), �������: SCTXID, ������: CAN
(long)(&co1_vars.co_cstxCOBID),	//[1280h.01h], ��������: COB-ID Client->Server(tx), �������: CSTXID, ������: CAN
(long)(&co1_vars.co_scrxCOBID),	//[1280h.02h], ��������: COB-ID Server->Client(rx), �������: SCRXID, ������: CAN
(long)(&co1_vars.co_ssNODEID),	//[1280h.03h], ��������: NODE-ID on SDO server, �������: SDOSID, ������: CAN
(long)(&co1_vars.co_RPDO1COBID),	//[1400h.01h], ��������: COB-ID for RPDO1, �������: IRPDO1, ������: CAN
(long)(&co1_vars.co_transType),	//[1400h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO2COBID),	//[1401h.01h], ��������: COB-ID for RPDO2, �������: IRPDO2, ������: CAN
(long)(&co1_vars.co_transType),	//[1401h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO3COBID),	//[1402h.01h], ��������: COB-ID for RPDO3, �������: IRPDO3, ������: CAN
(long)(&co1_vars.co_transType),	//[1402h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO4COBID),	//[1403h.01h], ��������: COB-ID for RPDO4, �������: IRPDO4, ������: CAN
(long)(&co1_vars.co_transType),	//[1403h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO5COBID),	//[1404h.01h], ��������: COB-ID for RPDO5, �������: IRPDO5, ������: CAN
(long)(&co1_vars.co_transType),	//[1404h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO6COBID),	//[1405h.01h], ��������: COB-ID for RPDO6, �������: IRPDO6, ������: CAN
(long)(&co1_vars.co_transType),	//[1405h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO7COBID),	//[1406h.01h], ��������: COB-ID for RPDO7, �������: IRPDO7, ������: CAN
(long)(&co1_vars.co_transType),	//[1406h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO8COBID),	//[1407h.01h], ��������: COB-ID for RPDO8, �������: IRPDO8, ������: CAN
(long)(&co1_vars.co_transType),	//[1407h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO1_1Mapping),	//[1600h.01h], ��������: RPDO1-1 Mapping, �������: RPM11, ������: CAN
(long)(&co1_vars.co_RPDO1_2Mapping),	//[1600h.02h], ��������: RPDO1-2 Mapping, �������: RPM12, ������: CAN
(long)(&co1_vars.co_RPDO1_3Mapping),	//[1600h.03h], ��������: RPDO1-3 Mapping, �������: RPM13, ������: CAN
(long)(&co1_vars.co_RPDO1_4Mapping),	//[1600h.04h], ��������: RPDO1-4 Mapping, �������: RPM14, ������: CAN
(long)(&co1_vars.co_RPDO2_1Mapping),	//[1601h.01h], ��������: RPDO2-1 Mapping, �������: RPM21, ������: CAN
(long)(&co1_vars.co_RPDO2_2Mapping),	//[1601h.02h], ��������: RPDO2-2 Mapping, �������: RPM22, ������: CAN
(long)(&co1_vars.co_RPDO2_3Mapping),	//[1601h.03h], ��������: RPDO2-3 Mapping, �������: RPM23, ������: CAN
(long)(&co1_vars.co_RPDO2_4Mapping),	//[1601h.04h], ��������: RPDO2-4 Mapping, �������: RPM24, ������: CAN
(long)(&co1_vars.co_RPDO3_1Mapping),	//[1602h.01h], ��������: RPDO3-1 Mapping, �������: RPM31, ������: CAN
(long)(&co1_vars.co_RPDO3_2Mapping),	//[1602h.02h], ��������: RPDO3-2 Mapping, �������: RPM32, ������: CAN
(long)(&co1_vars.co_RPDO3_3Mapping),	//[1602h.03h], ��������: RPDO3-3 Mapping, �������: RPM33, ������: CAN
(long)(&co1_vars.co_RPDO3_4Mapping),	//[1602h.04h], ��������: RPDO3-4 Mapping, �������: RPM34, ������: CAN
(long)(&co1_vars.co_RPDO4_1Mapping),	//[1603h.01h], ��������: RPDO4-1 Mapping, �������: RPM41, ������: CAN
(long)(&co1_vars.co_RPDO4_2Mapping),	//[1603h.02h], ��������: RPDO4-2 Mapping, �������: RPM42, ������: CAN
(long)(&co1_vars.co_RPDO4_3Mapping),	//[1603h.03h], ��������: RPDO4-3 Mapping, �������: RPM43, ������: CAN
(long)(&co1_vars.co_RPDO4_4Mapping),	//[1603h.04h], ��������: RPDO4-4 Mapping, �������: RPM44, ������: CAN
(long)(&co1_vars.co_RPDO5_1Mapping),	//[1604h.01h], ��������: RPDO5-1 Mapping, �������: RPM51, ������: CAN
(long)(&co1_vars.co_RPDO5_2Mapping),	//[1604h.02h], ��������: RPDO5-2 Mapping, �������: RPM52, ������: CAN
(long)(&co1_vars.co_RPDO5_3Mapping),	//[1604h.03h], ��������: RPDO5-3 Mapping, �������: RPM53, ������: CAN
(long)(&co1_vars.co_RPDO5_4Mapping),	//[1604h.04h], ��������: RPDO5-4 Mapping, �������: RPM54, ������: CAN
(long)(&co1_vars.co_RPDO6_1Mapping),	//[1605h.01h], ��������: RPDO6-1 Mapping, �������: RPM61, ������: CAN
(long)(&co1_vars.co_RPDO6_2Mapping),	//[1605h.02h], ��������: RPDO6-2 Mapping, �������: RPM62, ������: CAN
(long)(&co1_vars.co_RPDO6_3Mapping),	//[1605h.03h], ��������: RPDO6-3 Mapping, �������: RPM63, ������: CAN
(long)(&co1_vars.co_RPDO6_4Mapping),	//[1605h.04h], ��������: RPDO6-4 Mapping, �������: RPM64, ������: CAN
(long)(&co1_vars.co_RPDO7_1Mapping),	//[1606h.01h], ��������: RPDO7-1 Mapping, �������: RPM71, ������: CAN
(long)(&co1_vars.co_RPDO7_2Mapping),	//[1606h.02h], ��������: RPDO7-2 Mapping, �������: RPM72, ������: CAN
(long)(&co1_vars.co_RPDO7_3Mapping),	//[1606h.03h], ��������: RPDO7-3 Mapping, �������: RPM73, ������: CAN
(long)(&co1_vars.co_RPDO7_4Mapping),	//[1606h.04h], ��������: RPDO7-4 Mapping, �������: RPM74, ������: CAN
(long)(&co1_vars.co_RPDO8_1Mapping),	//[1607h.01h], ��������: RPDO8-1 Mapping, �������: RPM81, ������: CAN
(long)(&co1_vars.co_RPDO8_2Mapping),	//[1607h.02h], ��������: RPDO8-2 Mapping, �������: RPM82, ������: CAN
(long)(&co1_vars.co_RPDO8_3Mapping),	//[1607h.03h], ��������: RPDO8-3 Mapping, �������: RPM83, ������: CAN
(long)(&co1_vars.co_RPDO8_4Mapping),	//[1607h.04h], ��������: RPDO8-4 Mapping, �������: RPM84, ������: CAN
(long)(&co1_vars.co_TPDO1COBID),	//[1800h.01h], ��������: COB-ID for TPDO1, �������: ITPDO1, ������: CAN
(long)(&co1_vars.co_transType),	//[1800h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO1ITime),	//[1800h.03h], ��������: Inhibit Time 1, �������: ITime1, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1800h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO1EventTimer),	//[1800h.05h], ��������: Event Timer 1, �������: EvTmr1, ������: CAN
(long)(&co1_vars.co_TPDO2COBID),	//[1801h.01h], ��������: COB-ID for TPDO2, �������: ITPDO2, ������: CAN
(long)(&co1_vars.co_transType),	//[1801h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO2ITime),	//[1801h.03h], ��������: Inhibit Time 2, �������: ITime2, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1801h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO2EventTimer),	//[1801h.05h], ��������: Event Timer 2, �������: EvTmr2, ������: CAN
(long)(&co1_vars.co_TPDO3COBID),	//[1802h.01h], ��������: COB-ID for TPDO3, �������: ITPDO3, ������: CAN
(long)(&co1_vars.co_transType),	//[1802h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO3ITime),	//[1802h.03h], ��������: Inhibit Time 3, �������: ITime3, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1802h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO3EventTimer),	//[1802h.05h], ��������: Event Timer 3, �������: EvTmr3, ������: CAN
(long)(&co1_vars.co_TPDO4COBID),	//[1803h.01h], ��������: COB-ID for TPDO4, �������: ITPDO4, ������: CAN
(long)(&co1_vars.co_transType),	//[1803h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO4ITime),	//[1803h.03h], ��������: Inhibit Time 4, �������: ITime4, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1803h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO4EventTimer),	//[1803h.05h], ��������: Event Timer 4, �������: EvTmr4, ������: CAN
(long)(&co1_vars.co_TPDO5COBID),	//[1804h.01h], ��������: COB-ID for TPDO5, �������: ITPDO5, ������: CAN
(long)(&co1_vars.co_transType),	//[1804h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO5ITime),	//[1804h.03h], ��������: Inhibit Time 5, �������: ITime5, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1804h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO5EventTimer),	//[1804h.05h], ��������: Event Timer 5, �������: EvTmr5, ������: CAN
(long)(&co1_vars.co_TPDO6COBID),	//[1805h.01h], ��������: COB-ID for TPDO6, �������: ITPDO6, ������: CAN
(long)(&co1_vars.co_transType),	//[1805h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO6ITime),	//[1805h.03h], ��������: Inhibit Time 6, �������: ITime6, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1805h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO6EventTimer),	//[1805h.05h], ��������: Event Timer 6, �������: EvTmr6, ������: CAN
(long)(&co1_vars.co_TPDO7COBID),	//[1806h.01h], ��������: COB-ID for TPDO7, �������: ITPDO7, ������: CAN
(long)(&co1_vars.co_transType),	//[1806h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO7ITime),	//[1806h.03h], ��������: Inhibit Time 7, �������: ITime7, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1806h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO7EventTimer),	//[1806h.05h], ��������: Event Timer 7, �������: EvTmr7, ������: CAN
(long)(&co1_vars.co_TPDO8COBID),	//[1807h.01h], ��������: COB-ID for TPDO8, �������: ITPDO8, ������: CAN
(long)(&co1_vars.co_transType),	//[1807h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO8ITime),	//[1807h.03h], ��������: Inhibit Time 8, �������: ITime8, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1807h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO8EventTimer),	//[1807h.05h], ��������: Event Timer 8, �������: EvTmr8, ������: CAN
(long)(&co1_vars.co_TPDO1_1Mapping),	//[1A00h.01h], ��������: TPDO1-1 Mapping, �������: TPM11, ������: CAN
(long)(&co1_vars.co_TPDO1_2Mapping),	//[1A00h.02h], ��������: TPDO1-2 Mapping, �������: TPM12, ������: CAN
(long)(&co1_vars.co_TPDO1_3Mapping),	//[1A00h.03h], ��������: TPDO1-3 Mapping, �������: TPM13, ������: CAN
(long)(&co1_vars.co_TPDO1_4Mapping),	//[1A00h.04h], ��������: TPDO1-4 Mapping, �������: TPM14, ������: CAN
(long)(&co1_vars.co_TPDO2_1Mapping),	//[1A01h.01h], ��������: TPDO2-1 Mapping, �������: TPM21, ������: CAN
(long)(&co1_vars.co_TPDO2_2Mapping),	//[1A01h.02h], ��������: TPDO2-2 Mapping, �������: TPM22, ������: CAN
(long)(&co1_vars.co_TPDO2_3Mapping),	//[1A01h.03h], ��������: TPDO2-3 Mapping, �������: TPM23, ������: CAN
(long)(&co1_vars.co_TPDO2_4Mapping),	//[1A01h.04h], ��������: TPDO2-4 Mapping, �������: TPM24, ������: CAN
(long)(&co1_vars.co_TPDO3_1Mapping),	//[1A02h.01h], ��������: TPDO3-1 Mapping, �������: TPM31, ������: CAN
(long)(&co1_vars.co_TPDO3_2Mapping),	//[1A02h.02h], ��������: TPDO3-2 Mapping, �������: TPM32, ������: CAN
(long)(&co1_vars.co_TPDO3_3Mapping),	//[1A02h.03h], ��������: TPDO3-3 Mapping, �������: TPM33, ������: CAN
(long)(&co1_vars.co_TPDO3_4Mapping),	//[1A02h.04h], ��������: TPDO3-4 Mapping, �������: TPM34, ������: CAN
(long)(&co1_vars.co_TPDO4_1Mapping),	//[1A03h.01h], ��������: TPDO4-1 Mapping, �������: TPM41, ������: CAN
(long)(&co1_vars.co_TPDO4_2Mapping),	//[1A03h.02h], ��������: TPDO4-2 Mapping, �������: TPM42, ������: CAN
(long)(&co1_vars.co_TPDO4_3Mapping),	//[1A03h.03h], ��������: TPDO4-3 Mapping, �������: TPM43, ������: CAN
(long)(&co1_vars.co_TPDO4_4Mapping),	//[1A03h.04h], ��������: TPDO4-4 Mapping, �������: TPM44, ������: CAN
(long)(&co1_vars.co_TPDO5_1Mapping),	//[1A04h.01h], ��������: TPDO5-1 Mapping, �������: TPM51, ������: CAN
(long)(&co1_vars.co_TPDO5_2Mapping),	//[1A04h.02h], ��������: TPDO5-2 Mapping, �������: TPM52, ������: CAN
(long)(&co1_vars.co_TPDO5_3Mapping),	//[1A04h.03h], ��������: TPDO5-3 Mapping, �������: TPM53, ������: CAN
(long)(&co1_vars.co_TPDO5_4Mapping),	//[1A04h.04h], ��������: TPDO5-4 Mapping, �������: TPM54, ������: CAN
(long)(&co1_vars.co_TPDO6_1Mapping),	//[1A05h.01h], ��������: TPDO6-1 Mapping, �������: TPM61, ������: CAN
(long)(&co1_vars.co_TPDO6_2Mapping),	//[1A05h.02h], ��������: TPDO6-2 Mapping, �������: TPM62, ������: CAN
(long)(&co1_vars.co_TPDO6_3Mapping),	//[1A05h.03h], ��������: TPDO6-3 Mapping, �������: TPM63, ������: CAN
(long)(&co1_vars.co_TPDO6_4Mapping),	//[1A05h.04h], ��������: TPDO6-4 Mapping, �������: TPM64, ������: CAN
(long)(&co1_vars.co_TPDO7_1Mapping),	//[1A06h.01h], ��������: TPDO7-1 Mapping, �������: TPM71, ������: CAN
(long)(&co1_vars.co_TPDO7_2Mapping),	//[1A06h.02h], ��������: TPDO7-2 Mapping, �������: TPM72, ������: CAN
(long)(&co1_vars.co_TPDO7_3Mapping),	//[1A06h.03h], ��������: TPDO7-3 Mapping, �������: TPM73, ������: CAN
(long)(&co1_vars.co_TPDO7_4Mapping),	//[1A06h.04h], ��������: TPDO7-4 Mapping, �������: TPM74, ������: CAN
(long)(&co1_vars.co_TPDO8_1Mapping),	//[1A07h.01h], ��������: TPDO8-1 Mapping, �������: TPM81, ������: CAN
(long)(&co1_vars.co_TPDO8_2Mapping),	//[1A07h.02h], ��������: TPDO8-2 Mapping, �������: TPM82, ������: CAN
(long)(&co1_vars.co_TPDO8_3Mapping),	//[1A07h.03h], ��������: TPDO8-3 Mapping, �������: TPM83, ������: CAN
(long)(&co1_vars.co_TPDO8_4Mapping),	//[1A07h.04h], ��������: TPDO8-4 Mapping, �������: TPM84, ������: CAN
(long)(&co1_vars.co_nodeID),	//[2000h.00h], ��������: CAN NODE-ID, �������: NodeID, ������: CAN
(long)(&co1_vars.co_bitRate),	//[2001h.00h], ��������: CAN Bit Rate, �������: CANBR, ������: CAN, ���� � 0 �� 2: 0000000000000111b
(long)(&co1_vars.co_vendorID),	//[2002h.01h], ��������: ��� �������������, �������: VendID, ������: CAN
(long)(&co1_vars.co_productCode),	//[2002h.02h], ��������: ��� ��������, �������: PrCode, ������: CAN
(long)(&co1_vars.co_revisionNumber),	//[2002h.03h], ��������: ����� �������, �������: RevNum, ������: CAN
(long)(&co1_vars.co_serialNumber),	//[2002h.04h], ��������: �������� �����, �������: SerNum, ������: CAN
(long)(&co1_vars.co_specialData1),	//[2003h.01h], ��������: Special Data 1, �������: SpDat1, ������: CAN
(long)(&co1_vars.co_specialData2),	//[2003h.02h], ��������: Special Data 2, �������: SpDat2, ������: CAN
(long)(&co1_vars.co_specialData3),	//[2003h.03h], ��������: Special Data 3, �������: SpDat3, ������: CAN
(long)(&co1_vars.co_specialData4),	//[2003h.04h], ��������: Special Data 4, �������: SpDat4, ������: CAN
(long)(&co1_vars.co_secretCode),	//[2004h.00h], ��������: Secret Code, �������: Secret, ������: CAN
(long)(&co1_vars.co_protectBit),	//[2005h.00h], ��������: Protect Bit, �������: ProtBt, ������: CAN, ���� � 0 �� 0: 0000000000000001b
(long)(&co1_odHash[0]),	//[2007h.01h], ��������: md5_hash_0, �������: md5_hash_0, ������: CAN
(long)(&co1_odHash[1]),	//[2007h.02h], ��������: md5_hash_1, �������: md5_hash_1, ������: CAN
(long)(&co1_odHash[2]),	//[2007h.03h], ��������: md5_hash_2, �������: md5_hash_2, ������: CAN
(long)(&co1_odHash[3]),	//[2007h.04h], ��������: md5_hash_3, �������: md5_hash_3, ������: CAN
(long)(&co1_vars.co_heartbeatFlag0),	//[2010h.01h], ��������: Heartbeat Flag 0-31, �������: HFlag0, ������: CAN
(long)(&co1_vars.co_heartbeatFlag1),	//[2010h.02h], ��������: Heartbeat Flag 32-63, �������: HFlag1, ������: CAN
(long)(&co1_vars.co_heartbeatFlag2),	//[2010h.03h], ��������: Heartbeat Flag 64-95, �������: HFlag2, ������: CAN
(long)(&co1_vars.co_heartbeatFlag3),	//[2010h.04h], ��������: Heartbeat Flag 96-127, �������: HFlag3, ������: CAN
(long)(&co1_vars.co_heartbeatMask0),	//[2011h.01h], ��������: Heartbeat Mask 0-31, �������: HMask0, ������: CAN
(long)(&co1_vars.co_heartbeatMask1),	//[2011h.02h], ��������: Heartbeat Mask 32-63, �������: HMask1, ������: CAN
(long)(&co1_vars.co_heartbeatMask2),	//[2011h.03h], ��������: Heartbeat Mask 64-95, �������: HMask2, ������: CAN
(long)(&co1_vars.co_heartbeatMask3),	//[2011h.04h], ��������: Heartbeat Mask 96-127, �������: HMask3, ������: CAN
(long)(&co1_vars.co_heartbeatAutoStart),	//[2012h.00h], ��������: Heartbeat Autostart, �������: HBASta, ������: CAN, ���� � 0 �� 0: 0000000000000001b
(long)(&co1_vars.co_heartbeatAutoRecovery),	//[2014h.00h], ��������: Heartbeat Autorecovery, �������: HBARec, ������: CAN, ���� � 0 �� 0: 0000000000000001b
(long)(&co1_vars.co_nodeState),	//[2015h.00h], ��������: ��������� �������� CAN-Open, �������: State, ������: CAN
(long)(&co1_vars.co_emergencyErrorCode),	//[2016h.00h], ��������: Emergency Error Code, �������: EmErCo, ������: CAN
(long)(&co1_vars.co_deviceErrorState),	//[2017h.00h], ��������: Device Error State, �������: DeErSt, ������: CAN
(long)(&co1_vars.co_ODCommand),	//[2080h.01h], ��������: Object Dictionary Command, �������: ODComm, ������: CAN
(long)(&co1_vars.co_currentODIndex),	//[2080h.02h], ��������: Current OD Index, �������: ODCInd, ������: CAN
(long)(&co1_vars.co_currentODSubIndex),	//[2080h.03h], ��������: Current OD Sub-Index, �������: ODCSub, ������: CAN
(long)(&co1_vars.co_currentODEText),	//[2080h.04h], ��������: Current OD Element Text, �������: ODCTxt, ������: CAN
(long)(&co1_vars.co_currentODEFormat),	//[2080h.05h], ��������: Current OD Element Format, �������: ODCFrm, ������: CAN
(long)(&co1_vars.co_currentODEMin),	//[2080h.06h], ��������: Current OD Element Min, �������: ODCMin, ������: CAN
(long)(&co1_vars.co_currentODEMax),	//[2080h.07h], ��������: Current OD Element Max, �������: ODCMax, ������: CAN
(long)(&co1_vars.co_currentODEDefault),	//[2080h.08h], ��������: Current OD Element Default, �������: ODCDef, ������: CAN
(long)(&co1_vars.co_currentODEMinLow),	//[2080h.09h], ��������: Current OD Element MinLow, �������: ODCMiL, ������: CAN
(long)(&co1_vars.co_currentODEMaxLow),	//[2080h.0Ah], ��������: Current OD Element MaxLow, �������: ODCMaL, ������: CAN
(long)(&co1_vars.co_currentODEDefaultLow),	//[2080h.0Bh], ��������: Current OD Element Default Low, �������: ODCDeL, ������: CAN
(long)(&co1_vars.co_currentODEAddrLow),	//[2080h.0Ch], ��������: Current OD Element Address, �������: ODCAdr, ������: CAN
(long)(&co1_vars.co_currentODEAddrLow),	//[2080h.0Dh], ��������: Current OD Element Address, �������: ODCAdr, ������: CAN
(long)(&co1_vars.co_currentODEType),	//[2080h.0Eh], ��������: ������ ����������, �������: ������, ������: CAN
(long)(&co1_vars.co_odIndexSize),	//[2081h.00h], ��������: ���������� ��������, �������: ������, ������: CAN
(long)(&co1_vars.co_defaultIndex1),	//[2082h.01h], ��������: Default Index 1, �������: DfInd1, ������: CAN
(long)(&co1_vars.co_defaultIndex2),	//[2082h.02h], ��������: Default Index 2, �������: DfInd2, ������: CAN
(long)(&co1_vars.co_maskElement01),	//[2083h.01h], ��������: Mask Element, �������: MskEl0, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement01),	//[2083h.02h], ��������: Mask Element, �������: MskEl1, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElement23),	//[2083h.03h], ��������: Mask Element, �������: MskEl2, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement23),	//[2083h.04h], ��������: Mask Element, �������: MskEl3, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElement45),	//[2083h.05h], ��������: Mask Element, �������: MskEl4, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement45),	//[2083h.06h], ��������: Mask Element, �������: MskEl5, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElement67),	//[2083h.07h], ��������: Mask Element, �������: MskEl6, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement67),	//[2083h.08h], ��������: Mask Element, �������: MskEl7, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElement89),	//[2083h.09h], ��������: Mask Element, �������: MskEl8, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement89),	//[2083h.0Ah], ��������: Mask Element, �������: MskEl9, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElementAB),	//[2083h.0Bh], ��������: Mask Element, �������: MskElA, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElementAB),	//[2083h.0Ch], ��������: Mask Element, �������: MskElB, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElementCD),	//[2083h.0Dh], ��������: Mask Element, �������: MskElC, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElementCD),	//[2083h.0Eh], ��������: Mask Element, �������: MskElD, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElementEF),	//[2083h.0Fh], ��������: Mask Element, �������: MskElE, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElementEF),	//[2083h.10h], ��������: Mask Element, �������: MskElF, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_scaleNum0),	//[2100h.01h], ��������: Scale Number 0, �������: SN0, ������: CAN
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.02h], ��������: Scale Number 0 Format, �������: S0Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1),	//[2101h.01h], ��������: Scale Number 1, �������: SN1, ������: CAN
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.02h], ��������: Scale Number 1 Format, �������: S1Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum2),	//[2102h.01h], ��������: Scale Number 2, �������: SN2, ������: CAN
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.02h], ��������: Scale Number 2 Format, �������: S2Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum3),	//[2103h.01h], ��������: Scale Number 3, �������: SN3, ������: CAN
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.02h], ��������: Scale Number 3 Format, �������: S3Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum4),	//[2104h.01h], ��������: Scale Number 4, �������: SN4, ������: CAN
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.02h], ��������: Scale Number 4 Format, �������: S4Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum5),	//[2105h.01h], ��������: Scale Number 5, �������: SN5, ������: CAN
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.02h], ��������: Scale Number 5 Format, �������: S5Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum6),	//[2106h.01h], ��������: Scale Number 6, �������: SN6, ������: CAN
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.02h], ��������: Scale Number 6 Format, �������: S6Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum7),	//[2107h.01h], ��������: Scale Number 7, �������: SN7, ������: CAN
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.02h], ��������: Scale Number 7 Format, �������: S7Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum8),	//[2108h.01h], ��������: Scale Number 8, �������: SN8, ������: CAN
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.02h], ��������: Scale Number 8 Format, �������: S8Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum9),	//[2109h.01h], ��������: Scale Number 9, �������: SN9, ������: CAN
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.02h], ��������: Scale Number 9 Format, �������: S9Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumA),	//[210Ah.01h], ��������: Scale Number A, �������: SNA, ������: CAN
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.02h], ��������: Scale Number A Format, �������: SAFmt, ������: CAN
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumB),	//[210Bh.01h], ��������: Scale Number B, �������: SNB, ������: CAN
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.02h], ��������: Scale Number B Format, �������: SBFmt, ������: CAN
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumC),	//[210Ch.01h], ��������: Scale Number C, �������: SNC, ������: CAN
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.02h], ��������: Scale Number C Format, �������: SCFmt, ������: CAN
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumD),	//[210Dh.01h], ��������: Scale Number D, �������: SND, ������: CAN
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.02h], ��������: Scale Number D Format, �������: SDFmt, ������: CAN
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumE),	//[210Eh.01h], ��������: Scale Number E, �������: SNE, ������: CAN
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.02h], ��������: Scale Number E Format, �������: SEFmt, ������: CAN
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumF),	//[210Fh.01h], ��������: Scale Number F, �������: SNF, ������: CAN
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.02h], ��������: Scale Number F Format, �������: SFFmt, ������: CAN
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum10),	//[2110h.01h], ��������: Scale Number 10, �������: SN10, ������: CAN
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.02h], ��������: Scale Number 10 Format, �������: S10Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum11),	//[2111h.01h], ��������: Scale Number 11, �������: SN11, ������: CAN
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.02h], ��������: Scale Number 11 Format, �������: S11Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum12),	//[2112h.01h], ��������: Scale Number 12, �������: SN12, ������: CAN
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.02h], ��������: Scale Number 12 Format, �������: S12Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum13),	//[2113h.01h], ��������: Scale Number 13, �������: SN13, ������: CAN
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.02h], ��������: Scale Number 13 Format, �������: S13Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum14),	//[2114h.01h], ��������: Scale Number 14, �������: SN14, ������: CAN
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.02h], ��������: Scale Number 14 Format, �������: S14Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum15),	//[2115h.01h], ��������: Scale Number 15, �������: SN15, ������: CAN
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.02h], ��������: Scale Number 15Format, �������: S15Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum16),	//[2116h.01h], ��������: Scale Number 16, �������: SN16, ������: CAN
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.02h], ��������: Scale Number 16Format, �������: S16Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum17),	//[2117h.01h], ��������: Scale Number 17, �������: SN17, ������: CAN
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.02h], ��������: Scale Number 17Format, �������: S17Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum18),	//[2118h.01h], ��������: Scale Number 18, �������: SN18, ������: CAN
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.02h], ��������: Scale Number 18Format, �������: S18Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum19),	//[2119h.01h], ��������: Scale Number 19, �������: SN19, ������: CAN
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.02h], ��������: Scale Number 19Format, �������: S19Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1A),	//[211Ah.01h], ��������: Scale Number 1A, �������: SN1A, ������: CAN
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.02h], ��������: Scale Number 1AFormat, �������: S1AFmt, ������: CAN
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1B),	//[211Bh.01h], ��������: Scale Number 1B, �������: SN1B, ������: CAN
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.02h], ��������: Scale Number 1BFormat, �������: S1BFmt, ������: CAN
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1C),	//[211Ch.01h], ��������: Scale Number 1C, �������: SN1C, ������: CAN
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.02h], ��������: Scale Number 1C Format, �������: S1CFmt, ������: CAN
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1D),	//[211Dh.01h], ��������: Scale Number 1D, �������: SN1D, ������: CAN
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.02h], ��������: Scale Number 1D Format, �������: S1DFmt, ������: CAN
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&cmd.all),	//[2502h.01h], ��������: ����, �������: ����, ������: ����� ����������, ���� � 0 �� 0: 0000000000000001b
(long)(&cmd.all),	//[2502h.02h], ��������: ����, �������: ����, ������: ����� ����������, ���� � 1 �� 1: 0000000000000010b
(long)(&cmd.all),	//[2502h.03h], ��������: �������� ��������� ������, �������: ������, ������: ����� ����������, ���� � 2 �� 2: 0000000000000100b
(long)(&cmd.all),	//[2502h.04h], ��������: ����� ���������� CAN, �������: ���CAN, ������: ����� ����������
(long)(&drv_interface.req_data),	//[2506h.01h], ��������: ������� ������ �����, �������: OfflineCounterMax, ������: ��� �����
(long)(&drv_interface.ans_data),	//[2506h.02h], ��������: ������� ������ �����, �������: OfflineCounter, ������: ��� �����
(long)(&drv_interface.data_Low),	//[2506h.03h], ��������: data_Low, �������: data_L, ������: ��� �����
(long)(&drv_interface.data_High),	//[2506h.04h], ��������: data_High, �������: data_H, ������: ��� �����
(long)(&sm_prot.Main_ErrorCode),	//[2532h.01h], ��������: ��� ������ ARM, �������: ��� ������ ARM, ������: ���. ���� �����, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_prot.Main_ErrorCode),	//[2532h.02h], ��������: ���������� ���� ������, �������: ���+, ������: ���. ���� �����, ���� � 8 �� 15: 1111111100000000b
(long)(&sm_prot.Main_Flags),	//[2532h.03h], ��������: ��������� ������, �������: System, ������: ���. ���� �����, ���� � 0 �� 0: 0000000000000001b
(long)(&disp_group_number),	//[2534h.01h], ��������: ����� ���� ��� ������ ����������, �������: � �� ��, ������: CAN
(long)(&VendorToken),	//[2600h.01h], ��������: VendorToken, �������: VendorToken, ������: ��� �����
(long)(&drv_status.all),	//[3000h.00h], ��������: ������ ���������������, �������: ������, ������: ��� �����, ���� � 0 �� 5: 0000000000111111b
(long)(&msCounter),	//[3100h.01h], ��������: ������� ���������� 1 ���, �������: ��.������.1 ���, ������: ��������
(long)(&FastCounter),	//[3100h.02h], ��������: ������� ���������� 10 ���, �������: ��.������.10 ���, ������: ��������
(long)(&LoopCounter),	//[3100h.03h], ��������: BackgroundCounter, �������: BackgroundCounter, ������: ��������
(long)(&TIsr10),	//[3100h.04h], ��������: T_10���, �������: T_10���, ������: ��������
(long)(&TIsr1),	//[3100h.05h], ��������: T_1���, �������: T_1���, ������: ��������
(long)(&rmp.T),	//[5000h.01h], ��������: T ������� �� ��������, �������: rmpT, ������: ��
(long)(&rmp.input),	//[5000h.02h], ��������: ���� ��, �������: ������, ������: ��
(long)(&rmp.output),	//[5000h.03h], ��������: ����� ��, �������: �������, ������: ��
(long)(&pid_id.pid_ref_reg3),	//[5100h.01h], ��������: �������, �������: ���-�, ������: ���. ���� Id
(long)(&pid_id.pid_fdb_reg3),	//[5100h.02h], ��������: �������� �����, �������: ���.��, ������: ���. ���� Id
(long)(&pid_id.Kp_reg3),	//[5100h.03h], ��������: �������. �����. Kp, �������: Kp, ������: ���. ���� Id
(long)(&pid_id.pid_out_max),	//[5100h.04h], ��������: �������� ������, �������: Max, ������: ���. ���� Id
(long)(&pid_id.pid_out_min),	//[5100h.05h], ��������: ������� ������, �������: Min, ������: ���. ���� Id
(long)(&pid_id.Ki_reg3),	//[5100h.06h], ��������: ������������ �����. Ki, �������: Ki, ������: ���. ���� Id
(long)(&pid_id.Kd_reg3),	//[5100h.07h], ��������: ����. �����. Kd, �������: Kd, ������: ���. ���� Id
(long)(&pid_id.Kc_reg3),	//[5100h.08h], ��������: ������.���������.�����������, �������: Kc, ������: ���. ���� Id
(long)(&pid_id.e_reg3),	//[5100h.09h], ��������: ������ ��������������� ��������, �������: ������, ������: ���. ���� Id
(long)(&pid_id.pid_out_reg3),	//[5100h.0Ah], ��������: ����� ����������, �������: �����, ������: ���. ���� Id
(long)(&pid_id.up_reg3),	//[5100h.0Bh], ��������: ���.�������., �������: ���.�������., ������: ���. ���� Id
(long)(&pid_id.ui_reg3),	//[5100h.0Ch], ��������: ���.������., �������: ���.������., ������: ���. ���� Id
(long)(&pid_id.ud_reg3),	//[5100h.0Dh], ��������: ���.������., �������: ���.������., ������: ���. ���� Id
(long)(&pid_spd.pid_ref_reg3),	//[5101h.01h], ��������: �������, �������: pisref, ������: ���. ��������
(long)(&pid_spd.pid_fdb_reg3),	//[5101h.02h], ��������: �������� �����, �������: pisfbd, ������: ���. ��������
(long)(&pid_spd.Kp_reg3),	//[5101h.03h], ��������: �������. �����. Kp, �������: Kp, ������: ���. ��������
(long)(&pid_spd.pid_out_max),	//[5101h.04h], ��������: �������� ������, �������: Max, ������: ���. ��������
(long)(&pid_spd.pid_out_min),	//[5101h.05h], ��������: ������� ������, �������: Min, ������: ���. ��������
(long)(&pid_spd.Ki_reg3),	//[5101h.06h], ��������: ������������ �����. Ki, �������: Ki, ������: ���. ��������
(long)(&pid_spd.Kd_reg3),	//[5101h.07h], ��������: ����. �����. Kd, �������: pisKd, ������: ���. ��������
(long)(&pid_spd.Kc_reg3),	//[5101h.08h], ��������: ������.���������.�����������, �������: Kc, ������: ���. ��������
(long)(&pid_spd.e_reg3),	//[5101h.09h], ��������: ������ ��������������� ��������, �������: ������, ������: ���. ��������
(long)(&pid_spd.pid_out_reg3),	//[5101h.0Ah], ��������: ����� ����������, �������: pisout, ������: ���. ��������
(long)(&pid_spd.up_reg3),	//[5101h.0Bh], ��������: ���.�������., �������: ���.�������., ������: ���. ��������
(long)(&pid_spd.ui_reg3),	//[5101h.0Ch], ��������: ���.������., �������: ���.������., ������: ���. ��������
(long)(&pid_spd.ud_reg3),	//[5101h.0Dh], ��������: ���.������., �������: ���.������., ������: ���. ��������
(long)(&pid_spd.saterr_reg3),	//[5101h.0Eh], ��������: ���������� ���������, �������: ����. �����, ������: ���. ��������
(long)(&pid_iq.pid_ref_reg3),	//[5102h.01h], ��������: �������, �������: ���-��, ������: ���. ���� Iq
(long)(&pid_iq.pid_fdb_reg3),	//[5102h.02h], ��������: �������� �����, �������: ���.��, ������: ���. ���� Iq
(long)(&pid_iq.Kp_reg3),	//[5102h.03h], ��������: �������. �����. Kp, �������: Kp, ������: ���. ���� Iq
(long)(&pid_iq.pid_out_max),	//[5102h.04h], ��������: �������� ������, �������: Max, ������: ���. ���� Iq
(long)(&pid_iq.pid_out_min),	//[5102h.05h], ��������: ������� ������, �������: Min, ������: ���. ���� Iq
(long)(&pid_iq.Ki_reg3),	//[5102h.06h], ��������: ������������ �����. Ki, �������: Ki, ������: ���. ���� Iq
(long)(&pid_iq.Kd_reg3),	//[5102h.07h], ��������: ����. �����. Kd, �������: Kd, ������: ���. ���� Iq
(long)(&pid_iq.Kc_reg3),	//[5102h.08h], ��������: ������.���������.�����������, �������: Kc, ������: ���. ���� Iq
(long)(&pid_iq.e_reg3),	//[5102h.09h], ��������: ������ ��������������� ��������, �������: ������, ������: ���. ���� Iq
(long)(&pid_iq.pid_out_reg3),	//[5102h.0Ah], ��������: ����� ����������, �������: �����, ������: ���. ���� Iq
(long)(&pid_iq.up_reg3),	//[5102h.0Bh], ��������: ���.�������., �������: ���.�������., ������: ���. ���� Iq
(long)(&pid_iq.ui_reg3),	//[5102h.0Ch], ��������: ���.������., �������: ���.������., ������: ���. ���� Iq
(long)(&pid_iq.ud_reg3),	//[5102h.0Dh], ��������: ���.������., �������: ���.������., ������: ���. ���� Iq
(long)(&pid_pos.pid_ref_reg3),	//[5103h.01h], ��������: �������, �������: pisref, ������: ���. ���������
(long)(&pid_pos.pid_ref_reg3),	//[5103h.02h], ��������: �������, �������: pisref, ������: ���. ���������
(long)(&pid_pos.pid_fdb_reg3),	//[5103h.03h], ��������: �������� �����, �������: pisfbd, ������: ���. ���������
(long)(&pid_pos.pid_fdb_reg3),	//[5103h.04h], ��������: �������� �����, �������: pisfbd, ������: ���. ���������
(long)(&pid_pos.Kp_reg3),	//[5103h.05h], ��������: �������. �����. Kp, �������: Kp, ������: ���. ���������
(long)(&pid_pos.pid_out_max),	//[5103h.06h], ��������: �������� ������, �������: Max, ������: ���. ���������
(long)(&pid_pos.pid_out_min),	//[5103h.07h], ��������: ������� ������, �������: Min, ������: ���. ���������
(long)(&pid_pos.Ki_reg3),	//[5103h.08h], ��������: ������������ �����. Ki, �������: Ki, ������: ���. ���������
(long)(&pid_pos.Kd_reg3),	//[5103h.09h], ��������: ����. �����. Kd, �������: pisKd, ������: ���. ���������
(long)(&pid_pos.DiffDelim),	//[5103h.0Ah], ��������: �����. ����. �����, �������: �����. ����. �����, ������: ���. ���������
(long)(&pid_pos.Kf_d),	//[5103h.0Bh], ��������: ����. �������, �������: ����. �������, ������: ���. ���������
(long)(&pid_pos.Kc_reg3),	//[5103h.0Ch], ��������: ������.���������.�����������, �������: Kc, ������: ���. ���������
(long)(&pid_pos.DeadZone),	//[5103h.0Dh], ��������: ������� ����, �������: ������� ����, ������: ���. ���������
(long)(&pid_pos.e_reg3),	//[5103h.0Eh], ��������: ������ ��������������� ��������, �������: ������, ������: ���. ���������
(long)(&pid_spd.saterr_reg3),	//[5103h.0Fh], ��������: ���������� ���������, �������: ����. �����, ������: ���. ���������
(long)(&pid_pos.pid_out_reg3),	//[5103h.10h], ��������: ����� ����������, �������: pisout, ������: ���. ���������
(long)(&pid_pos.up_reg3),	//[5103h.11h], ��������: ���.�������., �������: ���.�������., ������: ���. ���������
(long)(&pid_pos.ui_reg3),	//[5103h.12h], ��������: ���.������., �������: ���.������., ������: ���. ���������
(long)(&pid_pos.ud_reg3),	//[5103h.13h], ��������: ���.������., �������: ���.������., ������: ���. ���������
(long)(&pid_pos.e_reg3_filterOut),	//[5103h.14h], ��������: ������ ������, �������: ������ ������, ������: ���. ���������
(long)(&pwm.UalphaRef),	//[5105h.01h], ��������: Ua���, �������: Ua���, ������: ���
(long)(&pwm.UbetaRef),	//[5105h.02h], ��������: Ub���, �������: Ub���, ������: ���
(long)(&pwm.U_lim),	//[5105h.03h], ��������: U_���, �������: U_���, ������: ���
(long)(&pwm.GammaA),	//[5105h.04h], ��������: GammaA, �������: GmA, ������: ���
(long)(&pwm.GammaB),	//[5105h.05h], ��������: GammaB, �������: GmB, ������: ���
(long)(&pwm.GammaC),	//[5105h.06h], ��������: GammaC, �������: GmC, ������: ���
(long)(&pwm.k_pwm),	//[5105h.07h], ��������: TPWM, �������: TPWM, ������: ���
(long)(&pwm.DeadBand),	//[5105h.08h], ��������: ������� ����� (���), �������: ����. �����, ������: ���
(long)(&pwm.MinGammaLimit),	//[5105h.09h], ��������: ����������� ���. ������., �������: GamLim, ������: ���
(long)(&pwm.UdCompK),	//[5105h.0Ah], ��������: ����. ����������� Ud, �������: Ud����K, ������: ���
(long)(&pwm.UdCompEnable),	//[5105h.0Bh], ��������: ����������� Ud, �������: Ud����, ������: ���, ���� � 0 �� 0: 0000000000000001b
(long)(&pwm.PWM_type),	//[5105h.0Ch], ��������: ��� ���, �������: ������, ������: ���
(long)(&pwm.ULimitation),	//[5105h.0Dh], ��������: ULimitation, �������: ULimitation, ������: ���
(long)(&pwm.Frequency),	//[5105h.0Eh], ��������: ������� ���, �������: F���, ������: ���
(long)(&pwm.sector),	//[5105h.0Fh], ��������: ������, �������: ������, ������: ���
(long)(&pwm.U_mag),	//[5105h.10h], ��������: U_����, �������: U_����, ������: ���
(long)(&pwm.PDP_Fault),	//[5105h.11h], ��������: ����� ������, �������: F_bits, ������: ���
(long)(&sm_ctrl.state),	//[510Bh.01h], ��������: sm_state, �������: smstat, ������: �� sm_ctrl
(long)(&drv_status_code),	//[510Bh.02h], ��������: drv_status_code, �������: stcode, ������: �� sm_ctrl, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_prot.bit_fault1),	//[510Eh.01h], ��������: ����� ������ 1, �������: bitF_1, ������: ������
(long)(&sm_prot.bit_fault2),	//[510Eh.02h], ��������: ����� ������ 2, �������: bitF_2, ������: ������
(long)(&sm_prot.mask_fault1),	//[510Eh.03h], ��������: ����� ������ 1L, �������: mask1L, ������: ������, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_prot.mask_fault1),	//[510Eh.04h], ��������: ����� ������ 1H, �������: mask1H, ������: ������, ���� � 8 �� 15: 1111111100000000b
(long)(&sm_prot.mask_fault2),	//[510Eh.05h], ��������: ����� ������ 2L, �������: mask2L, ������: ������, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_prot.mask_fault2),	//[510Eh.06h], ��������: ����� ������  2H, �������: mask2H, ������: ������, ���� � 8 �� 15: 1111111100000000b
(long)(&sm_prot.Imax_protect),	//[510Eh.07h], ��������: ������������ ���, �������: ����.���, ������: ������
(long)(&sm_prot.Umax_protect),	//[510Eh.08h], ��������: ������������ ����������, �������: Ud_max, ������: ������
(long)(&sm_prot.Umin_protect),	//[510Eh.09h], ��������: ����������� ����������, �������: Ud_min, ������: ������
(long)(&sm_prot.speed_max),	//[510Eh.0Ah], ��������: ������������ ��������, �������: speed_max, ������: ������
(long)(&sm_prot.T_max),	//[510Eh.0Bh], ��������: ������������ �����������, �������: t_max, ������: ������
(long)(&refs.speed_ref),	//[5112h.01h], ��������: ��������, �������: ����_�, ������: �������
(long)(&refs.Iq_ref),	//[5112h.02h], ��������: ����. ��� ��, �������: ������, ������: �������
(long)(&refs.i_flux_ref),	//[5112h.03h], ��������: ��� ���������, �������: ������, ������: �������
(long)(&refs.theta_elec),	//[5112h.04h], ��������: theta_elec, �������: ������, ������: �������
(long)(&refs.uf_ref),	//[5112h.05h], ��������: �������� ���������� ��, �������: Uf_ref, ������: �������
(long)(&drv_params.p),	//[5113h.01h], ��������: ����� ��� �������, �������: ������, ������: �����. �����
(long)(&drv_params.I_nom),	//[5113h.02h], ��������: ����������� ���, �������: I�����, ������: �����. �����
(long)(&drv_params.U_nom),	//[5113h.03h], ��������: ����������� ���������� ����., �������: U�_���, ������: �����. �����
(long)(&drv_params.speed_nom),	//[5113h.04h], ��������: ����������� ��������, �������: �����������, ������: �����. �����
(long)(&drv_params.Udc_nom),	//[5113h.05h], ��������: ����������� ���������� ���, �������: Udc���, ������: �����. �����
(long)(&drv_params.Rs),	//[5113h.06h], ��������: Rs, �������: Rs, ������: �����. �����
(long)(&drv_params.Ls),	//[5113h.07h], ��������: Ls, �������: Ls, ������: �����. �����
(long)(&drv_params.freq_nom),	//[5113h.08h], ��������: ����������� �������, �������: ���.����., ������: �����. �����
(long)(&drv_params.sens_type),	//[5113h.09h], ��������: ��� ������� ���������, �������: Sens_type, ������: �����. �����, ���� � 0 �� 2: 0000000000000111b
(long)(&sm_ctrl.run_mode),	//[5114h.01h], ��������: ����� ������, �������: ������, ������: ��������� ��
(long)(&sw.all),	//[5114h.02h], ��������: �����������, �������: ������, ������: ��������� ��, ���� � 0 �� 0: 0000000000000001b
(long)(&sw.all),	//[5114h.03h], ��������: ��� ���� ����., �������: �������, ������: ��������� ��, ���� � 2 �� 2: 0000000000000100b
(long)(&sw.all),	//[5114h.04h], ��������: ������������, �������: ������������, ������: ��������� ��, ���� � 1 �� 1: 0000000000000010b
(long)(&sw.all),	//[5114h.05h], ��������: ��������� ��������� ������ JTAG, �������: (null), ������: ��������� ��, ���� � 3 �� 3: 0000000000001000b
(long)(&adc.Imeas_a_gain),	//[5116h.01h], ��������: ����������� ���� ���� �, �������: Ia����, ������: ���
(long)(&adc.Imeas_a_offset),	//[5116h.02h], ��������: �������� ���� ���� �, �������: Ia����, ������: ���
(long)(&adc.Imeas_a),	//[5116h.03h], ��������: ��� ���� �, �������: Ia_���, ������: ���
(long)(&adc.Imeas_b_gain),	//[5116h.04h], ��������: ����������� ���� ���� �, �������: Ib����, ������: ���
(long)(&adc.Imeas_b_offset),	//[5116h.05h], ��������: �������� ���� ���� �, �������: Ib����, ������: ���
(long)(&adc.Imeas_b),	//[5116h.06h], ��������: ��� ���� �, �������: Ib_���, ������: ���
(long)(&adc.Imeas_c),	//[5116h.07h], ��������: ��� ���� �, �������: Ic_���, ������: ���
(long)(&adc.Udc_meas_gain),	//[5116h.08h], ��������: ����������� ���������� ���, �������: Ud����, ������: ���
(long)(&adc.Udc_meas_offset),	//[5116h.09h], ��������: �������� ������. ���, �������: Ud����, ������: ���
(long)(&adc.Udc_meas),	//[5116h.0Ah], ��������: ���������� ���, �������: Ud, ������: ���
(long)(&adc.AI_meas_gain),	//[5116h.0Bh], ��������: �������� ����������� �����, �������: (null), ������: ���
(long)(&adc.AI_meas),	//[5116h.0Ch], ��������: ������� ���������� ���� 1, �������: ADC_ext1, ������: ���
(long)(&vhz.freq),	//[511Ah.01h], ��������: �������� �������, �������: F_���, ������: ������ U-f
(long)(&vhz.vout),	//[511Ah.02h], ��������: �������� ����������, �������: U_���, ������: ������ U-f
(long)(&vhz.FL),	//[511Ah.03h], ��������: ������� ������� �������, �������: f [0], ������: ������ U-f
(long)(&vhz.Vmin),	//[511Ah.04h], ��������: ������� ������� ����������, �������: U [0], ������: ������ U-f
(long)(&vhz.FH),	//[511Ah.05h], ��������: ������ ������� �������, �������: f [1], ������: ������ U-f
(long)(&vhz.Vmax),	//[511Ah.06h], ��������: ������ ������� ����������, �������: U [1], ������: ������ U-f
(long)(&vhz.Fmax),	//[511Ah.07h], ��������: ������������ �������, �������: f max, ������: ������ U-f
(long)(&cur_par.speed),	//[5138h.01h], ��������: ��������, �������: ����, ������: �����������
(long)(&cur_par.power),	//[5138h.02h], ��������: ���. ��������, �������: ������, ������: �����������
(long)(&cur_par.Is),	//[5138h.03h], ��������: ��� �������, �������: �����, ������: �����������
(long)(&cur_par.ThetaRefCurr),	//[5138h.04h], ��������: ���������, �������: ���������, ������: �����������
(long)(&cur_par.ThetaCurr),	//[5138h.05h], ��������: ������, �������: ������, ������: �����������
(long)(&cur_par.IsRef),	//[5138h.06h], ��������: ��� ������� ���, �������: ��������, ������: �����������
(long)(&global_time.PowerOn_time_min),	//[5138h.07h], ��������: ����� ����������� ���������, ���, �������: Power On Time, ������: �����������
(long)(&global_time.operational_time_min),	//[5138h.08h], ��������: ����� ������ �������, ���, �������: Work Time, ������: �����������
(long)(&dlog.mode_reset),	//[5150h.01h], ��������: dlog.mode_reset, �������: mode, ������: dlog
(long)(&dlog.control),	//[5150h.02h], ��������: dlog.control, �������: dlcont, ������: dlog
(long)(&dlog.ind_subind1),	//[5150h.03h], ��������: dlog.ind_subind1, �������: dlisi1, ������: dlog
(long)(&dlog.ind_subind2),	//[5150h.04h], ��������: dlog.ind_subind2, �������: dlisi2, ������: dlog
(long)(&dlog.ind_subind3),	//[5150h.05h], ��������: dlog.ind_subind3, �������: dlisi3, ������: dlog
(long)(&dlog.ind_subind4),	//[5150h.06h], ��������: dlog.ind_subind4, �������: dlisi4, ������: dlog
(long)(&dlog.StartBits),	//[5150h.07h], ��������: StartBitL, �������: StrtBL, ������: dlog, ���� � 0 �� 7: 0000000011111111b
(long)(&dlog.StartBits),	//[5150h.08h], ��������: StartBitH, �������: StrtBH, ������: dlog, ���� � 8 �� 15: 1111111100000000b
(long)(&dlog.OneShotOperation),	//[5150h.09h], ��������: OneShotOperation, �������: OneShotOp, ������: dlog, ���� � 0 �� 0: 0000000000000001b
(long)(&dlog.trig_shift),	//[5150h.0Ah], ��������: ���������� ����� �����������, �������: N �������., ������: dlog
(long)(&dlog.next_value_var),	//[5151h.00h], ��������: dlog.next_value_var, �������: dlnval, ������: ��� �����
(long)(&posspeedEqep.resol),	//[5152h.01h], ��������: ���-�� ��������, �������: ���-�� ��������, ������: ���-�������
(long)(&posspeedEqep.Posspeed_CTL.all),	//[5152h.02h], ��������: ������� ������, �������: ������� ������, ������: ���-�������, ���� � 2 �� 2: 0000000000000100b
(long)(&posspeedEqep.SpeedCalcType),	//[5152h.03h], ��������: ������������ �������� ����������, �������: SpeedCalcType, ������: ���-�������
(long)(&posspeedEqep.AngleOffset),	//[5152h.04h], ��������: ��������, �������: ������, ������: ���-�������
(long)(&posspeedEqep.Poscnt_res),	//[5152h.05h], ��������: ����������.���� � ������, �������: ����������.���� � ��, ������: ���-�������
(long)(&posspeedEqep.Poscnt_res16),	//[5152h.06h], ��������: ����������.���� � ������, �������: ����������.���� � ��, ������: ���-�������
(long)(&posspeedEqep.speed_elec),	//[5152h.07h], ��������: �������� , �������: ��������, ������: ���-�������
(long)(&posspeedEqep.theta_elec),	//[5152h.08h], ��������: ����. ������., �������: ����. ������., ������: ���-�������
(long)(&posspeedEqep.theta_mech),	//[5152h.09h], ��������: ���� ���., �������: ���� ���., ������: ���-�������
(long)(&posspeedEqep.Posspeed_CTL.all),	//[5152h.0Ah], ��������: ������� ����., �������: ������� ����., ������: ���-�������, ���� � 4 �� 4: 0000000000010000b
(long)(&posspeedEqep.speed_filter.T),	//[5152h.0Bh], ��������: � �������������� ������� ��������, �������: ��. ��������, ������: ���-�������
(long)(&posspeedEqep.Posspeed_FLG1.all),	//[5152h.0Ch], ��������: Posspeed_FLG1, �������: Posspeed_FLG1, ������: ���-�������
(long)(&posspeedEqep.GPIOsValue),	//[5152h.0Dh], ��������: GPIOsValue, �������: GPIOsValue, ������: ���-�������
(long)(&posspeedEqep.UPPS_forWatch),	//[5152h.0Eh], ��������: UPPS, �������: UPPS, ������: ���-�������
(long)(&posspeedEqep.Qcprdlat_tmp),	//[5152h.0Fh], ��������: QCPRD, �������: QCPRD, ������: ���-�������
(long)(&posspeedEqep.Qcprdlat16_tmp),	//[5152h.10h], ��������: QCPRD, �������: QCPRD, ������: ���-�������
(long)(&posspeedEqep.QEPSTS),	//[5152h.11h], ��������: QEPSTS, �������: QEPSTS, ������: ���-�������
(long)(&posspeedEqep.RevolutionCounter),	//[5152h.12h], ��������: ����� ��������, �������: revolCounter, ������: ���-�������
(long)(&posspeedEqep.Poscnt_resContinouosInt8),	//[5152h.13h], ��������: ���. ��������� � ������, �������: qcAbsPos, ������: ���-�������
(long)(&posspeedEqep.Poscnt_resContinouosInt),	//[5152h.14h], ��������: ���. ��������� � ������, �������: qcAbsPos, ������: ���-�������
(long)(&posspeedEqep.Poscnt_resContinouosLong),	//[5152h.15h], ��������: ���. ��������� � ������, �������: qcAbsPos, ������: ���-�������
(long)(&posspeedEqep.theta_mechContinouos),	//[5152h.16h], ��������: ���� ������������ �� �������., �������: ��.���.��_���, ������: ���-�������
(long)(&posspeedEqep.theta_elecContinouos),	//[5152h.17h], ��������: ���� ������������� �� �������., �������: ��.��.��_���, ������: ���-�������
(long)(&posspeedEqep.Index_eventCounter),	//[5152h.18h], ��������: ������� ������� ��������� �����, �������: (null), ������: ���-�������
(long)(&DPReCAP.enabled),	//[5155h.01h], ��������: �������, �������: ���, ������: ���-����
(long)(&DPReCAP.Angle),	//[5155h.02h], ��������: ������, �������: ������, ������: ���-����
(long)(&DPReCAP.speed),	//[5155h.03h], ��������: �������� , �������: ��������, ������: ���-����
(long)(&DPReCAP.speedMIN),	//[5155h.04h], ��������: ������� ��������, �������: ������� ��������, ������: ���-����
(long)(&DPReCAP.Angle6),	//[5155h.05h], ��������: ������6, �������: ������6, ������: ���-����
(long)(&DPReCAP.DPReCAP_FLG1.all),	//[5155h.06h], ��������: ���-������� ���, �������: ���-������� ���, ������: ���-����, ���� � 0 �� 0: 0000000000000001b
(long)(&DPReCAP.milsecREF),	//[5155h.07h], ��������: ������� ��������� ��������, �������: ������� ��������� ��, ������: ���-����
(long)(&DPReCAP.speedMinREF),	//[5155h.08h], ��������: �������� ���., �������: �������� ���., ������: ���-����
(long)(&DPReCAP.CAP_WrongEdgeCnt),	//[5155h.09h], ��������: ������ ������, �������: ������ ������, ������: ���-����
(long)(&DPReCAP.HallCode),	//[5155h.0Ah], ��������: ���������� �����, �������: �����, ������: ���-����, ���� � 0 �� 2: 0000000000000111b
(long)(&DPReCAP.AngleOffset),	//[5155h.0Bh], ��������: ��������, �������: ������, ������: ���-����
(long)(&DPReCAP.ErrorLevel),	//[5155h.0Ch], ��������: ������� �����, �������: ������� �����, ������: ���-����
(long)(&DPReCAP.CAP_WrongEdgeCnt1),	//[5155h.0Dh], ��������: ������ 1 ������, �������: ����_1_�., ������: ���-����
(long)(&DPReCAP.CAP_WrongEdgeCnt2),	//[5155h.0Eh], ��������: ������ 2 ������, �������: ����_2_�., ������: ���-����
(long)(&DPReCAP.CAP_WrongEdgeCnt3),	//[5155h.0Fh], ��������: ������ 3 ������, �������: ����_3_�., ������: ���-����
(long)(&DPReCAP.UserDirection),	//[5155h.10h], ��������: ����������� ��������, �������: ������, ������: ���-����, ���� � 2 �� 2: 0000000000000100b
(long)(&DPReCAP.WrongCodeCounterLimitPerSec),	//[5155h.11h], ��������: ����.����� ������ ���, �������: ����.��.���, ������: ���-����
(long)(&DPReCAP.WrongCodeCounter),	//[5155h.12h], ��������: ���-�� ������ �������� ������������������ , �������: ������ ����������., ������: ���-����
(long)(&CounterCAP_isr),	//[5155h.13h], ��������: ������� ���������� �� ������, �������: ����.Rx.Int., ������: ���-����
(long)(&cap0_counter),	//[5155h.14h], ��������: ������� ���������� CAP1, �������: ��.������.CAP1, ������: ���-����
(long)(&cap1_counter),	//[5155h.15h], ��������: ������� ���������� CAP2, �������: ��.������.CAP2, ������: ���-����
(long)(&cap2_counter),	//[5155h.16h], ��������: ������� ���������� CAP3, �������: ��.������.CAP3, ������: ���-����
(long)(&SSI_Encoder.resol),	//[5157h.01h], ��������: ���������� ��������� �� ������, �������: qepTik, ������: ���-SSI �������
(long)(&SSI_Encoder.AngleOffset),	//[5157h.02h], ��������: ��������, �������: ������, ������: ���-SSI �������
(long)(&SSI_Encoder.Poscnt_res),	//[5157h.03h], ��������: ����������.���� � ������, �������: ����������.���� � ��, ������: ���-SSI �������
(long)(&SSI_Encoder.speed_elec),	//[5157h.04h], ��������: �������� , �������: ��������, ������: ���-SSI �������
(long)(&SSI_Encoder.theta_elec),	//[5157h.05h], ��������: ����. ������., �������: ����. ������., ������: ���-SSI �������
(long)(&SSI_Encoder.theta_mech),	//[5157h.06h], ��������: ���� ���., �������: ���� ���., ������: ���-SSI �������
(long)(&SSI_Encoder.theta_mech_filtered),	//[5157h.07h], ��������: ���� ���. �������������, �������: theta_mech_filtered, ������: ���-SSI �������
(long)(&SSI_Encoder.theta_mech_filterK),	//[5157h.08h], ��������: � �������������� ������� ����, �������: ��. ����, ������: ���-SSI �������
(long)(&SSI_Encoder.RevolutionCounter),	//[5157h.09h], ��������: ����� ��������, �������: revolCounter, ������: ���-SSI �������
(long)(&SSI_Encoder.Poscnt_resContinouosLong),	//[5157h.0Ah], ��������: ���. ��������� � ������, �������: qcAbsPos, ������: ���-SSI �������
(long)(&SSI_Encoder.Poscnt_resContinouosInt8),	//[5157h.0Bh], ��������: ���. ��������� � ������, �������: qcAbsPos, ������: ���-SSI �������
(long)(&SSI_Encoder.Poscnt_resContinouosInt),	//[5157h.0Ch], ��������: ���. ��������� � ������, �������: qcAbsPos, ������: ���-SSI �������
(long)(&SSI_Encoder.theta_mechContinouos),	//[5157h.0Dh], ��������: ���� ������������ �� �������., �������: ��.���.��_���, ������: ���-SSI �������
(long)(&SSI_Encoder.theta_elecContinouos),	//[5157h.0Eh], ��������: ���� ������������� �� �������., �������: ��.��.��_���, ������: ���-SSI �������
(long)(&Debug1),	//[5174h.01h], ��������: DebugL1, �������: DebugL1, ������: ��� �������
(long)(&Debug1),	//[5174h.02h], ��������: DebugL1, �������: DebugL1, ������: ��� �������
(long)(&Debug2),	//[5174h.03h], ��������: DebugL2, �������: DebugL2, ������: ��� �������
(long)(&Debug2),	//[5174h.04h], ��������: DebugL2, �������: DebugL2, ������: ��� �������
(long)(&Debug3),	//[5174h.05h], ��������: DebugI3, �������: DebugI3, ������: ��� �������
(long)(&Debug3),	//[5174h.06h], ��������: DebugI3, �������: DebugI3, ������: ��� �������
(long)(&Debug4),	//[5174h.07h], ��������: DebugI4, �������: DebugI4, ������: ��� �������
(long)(&Debug4),	//[5174h.08h], ��������: DebugI4, �������: DebugI4, ������: ��� �������
(long)(&DebugW1),	//[5174h.09h], ��������: DebugW1, �������: DebugW1, ������: ��� �������
(long)(&DebugW1),	//[5174h.0Ah], ��������: DebugW1, �������: DebugW1, ������: ��� �������
(long)(&DebugW2),	//[5174h.0Bh], ��������: DebugW2, �������: DebugW2, ������: ��� �������
(long)(&DebugW2),	//[5174h.0Ch], ��������: DebugW2, �������: DebugW2, ������: ��� �������
(long)(&DebugW3),	//[5174h.0Dh], ��������: DebugW3, �������: DebugW3, ������: ��� �������
(long)(&DebugW3),	//[5174h.0Eh], ��������: DebugW3, �������: DebugW3, ������: ��� �������
(long)(&DebugW4),	//[5174h.0Fh], ��������: DebugW4, �������: DebugW4, ������: ��� �������
(long)(&DebugW4),	//[5174h.10h], ��������: DebugW4, �������: DebugW4, ������: ��� �������
(long)(&DebugF1),	//[5174h.11h], ��������: DebugF1, �������: DebugF1, ������: ��� �������
(long)(&DebugF2),	//[5174h.12h], ��������: DebugF2, �������: DebugF2, ������: ��� �������
(long)(&DebugF3),	//[5174h.13h], ��������: DebugF3, �������: DebugF3, ������: ��� �������
(long)(&DebugF4),	//[5174h.14h], ��������: DebugF4, �������: DebugF4, ������: ��� �������
(long)(&refs.DCMspeed_ref),	//[5185h.01h], ��������: ������� �������� (����. ���.), �������: ���. ����., ������: ��� ����. ���.
(long)(&refs.ua_ref),	//[5185h.02h], ��������: �������� ���������� �����, �������: Ua_ref, ������: ��� ����. ���.
(long)(&refs.uf_ref),	//[5185h.03h], ��������: �������� ���������� ��, �������: Uf_ref, ������: ��� ����. ���.
(long)(&RotorObserver.Tr),	//[5B04h.01h], ��������: ����. ������� ������, �������: Tr, ������: ����������� ������ ��
(long)(&RotorObserver.FluxCurrentRatio),	//[5B04h.02h], ��������: ����������� ���� ����. X � ���� Y, �������: FluxCurrentRatio, ������: ����������� ������ ��
(long)(&RotorObserver.FluxCurrentMin),	//[5B04h.03h], ��������: ����������� ��� �����������, �������: FluxCurrentMin, ������: ����������� ������ ��
(long)(&RotorObserver.id),	//[5B04h.04h], ��������: ��� ������� �� ��� D, �������: IsD, ������: ����������� ������ ��
(long)(&RotorObserver.iq),	//[5B04h.05h], ��������: ��� ������� �� ��� Q, �������: IsQ, ������: ����������� ������ ��
(long)(&RotorObserver.psi_d),	//[5B04h.06h], ��������: ����� ������ �� ��� D, �������: PsiRD, ������: ����������� ������ ��
(long)(&RotorObserver.psi_q),	//[5B04h.07h], ��������: ����� ������ �� ��� Q, �������: PsiRQ, ������: ����������� ������ ��
(long)(&RotorObserver.theta_psi_elec),	//[5B04h.08h], ��������: ���� ������ ������, �������: psiRalpha, ������: ����������� ������ ��
(long)(&udControl.StateOn),	//[5B05h.01h], ��������: ������� ��������� ����, �������: Relay_state, ������: ������� ����� ���
(long)(&udControl.Timeout_on),	//[5B05h.02h], ��������: ������� ��������� ����, ��, �������: relay on-delay, ������: ������� ����� ���
(long)(&udControl.U_on),	//[5B05h.03h], ��������: ���������� ���������, �, �������: on-voltage, ������: ������� ����� ���
(long)(&udControl.U_off),	//[5B05h.04h], ��������: ���������� ����������, �, �������: off-voltage, ������: ������� ����� ���
(long)(&udControl.deriv_time_ZPT),	//[5B05h.05h], ��������: ����������� ���������� ���, �������: derivative_voltage, ������: ������� ����� ���
(long)(&udControl.deriv_const),	//[5B05h.06h], ��������: ������� �� ����������� ���, �������: derivative_const, ������: ������� ����� ���
(long)(&input_vect),	//[5B06h.01h], ��������: ���������� �����, �������: �����, ������: ���������� ����� � ������, ���� � 0 �� 7: 0000000011111111b
(long)(&output_vect),	//[5B06h.02h], ��������: ���������� ������, �������: dout, ������: ���������� ����� � ������, ���� � 0 �� 7: 0000000011111111b
(long)(&fanControl.StateOn),	//[5B07h.01h], ��������: ������� ��������� �����������, �������: fan_state, ������: ������� ����������
(long)(&fanControl.T_on),	//[5B07h.02h], ��������: ����������� ��������� �����������, �������: t_on, ������: ������� ����������
(long)(&fanControl.T_off),	//[5B07h.03h], ��������: ����������� ���������� �����������, �������: t_off, ������: ������� ����������
(long)(&fanControl.T_alarm),	//[5B07h.04h], ��������: ����������� ������ �������������� � ���������, �������: t_alarm, ������: ������� ����������
(long)(&fanControl.temperature),	//[5B07h.05h], ��������: �����������, �������: t, ������: ������� ����������
(long)(&fanControl.manualOn),	//[5B07h.06h], ��������: �������� �������������, �������: (null), ������: ������� ����������
(long)(&brakeResistor.enabled),	//[5B08h.01h], ��������: �������, �������: ���, ������: ��������� ��������
(long)(&brakeResistor.upperLevel),	//[5B08h.02h], ��������: ���������� ���������, �, �������: on-voltage, ������: ��������� ��������
(long)(&brakeResistor.bottomLevel),	//[5B08h.03h], ��������: ���������� ����������, �, �������: off-voltage, ������: ��������� ��������
(long)(&brakeResistor.state),	//[5B08h.04h], ��������: ���������, �������: ���������, ������: ��������� ��������
};
Uint16 const CO1_OD_TBL2[] = {
32045, 1, 0,
31021, 2, 1,
32041, 3, 2,
32013, 4, 3,

28814,
5,
3,
64769, 5, 4,
(Uint16)(2000), (((Uint32)2000)>>16),
64257, 6, 5,
(Uint16)(1000),

28801,
7,
1,
32013, 8, 6,
32013, 9, 7,
32013, 10, 8,
32013, 11, 9,

19631,
12,
1,
31021, 13, 10,
31021, 14, 11,

19632,
15,
1,
30765, 16, 12,
30765, 17, 13,
29741, 18, 14,

18607,
19,
3,
64813, 20, 15,
(Uint16)(0x180), (((Uint32)0x180)>>16),
28973, 21, 16,
0,
0,

18607,
22,
3,
64813, 23, 17,
(Uint16)(0x280), (((Uint32)0x280)>>16),
28973, 21, 18,
0,
0,

18607,
24,
3,
64809, 25, 19,
(Uint16)(0x0401), (((Uint32)0x0401)>>16),
28969, 21, 20,
0,
0,

18607,
26,
3,
64809, 27, 21,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),
28969, 21, 22,
0,
0,

18607,
28,
3,
64813, 29, 23,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),
28973, 21, 24,
0,
0,

18607,
30,
3,
64813, 31, 25,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),
28973, 21, 26,
0,
0,

18607,
32,
3,
64801, 33, 27,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),
28961, 21, 28,
0,
0,

18607,
34,
3,
64801, 35, 29,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),
28961, 21, 30,
0,
0,

19633,
36,
3,
61741, 37, 31,
(Uint16)(0), (((Uint32)0)>>16),
61741, 38, 32,
(Uint16)(0), (((Uint32)0)>>16),
61741, 39, 33,
(Uint16)(0), (((Uint32)0)>>16),
61741, 40, 34,
(Uint16)(0), (((Uint32)0)>>16),

19633,
41,
3,
61741, 42, 35,
(Uint16)(0), (((Uint32)0)>>16),
61741, 43, 36,
(Uint16)(0), (((Uint32)0)>>16),
61741, 44, 37,
(Uint16)(0), (((Uint32)0)>>16),
61741, 45, 38,
(Uint16)(0), (((Uint32)0)>>16),

19629,
46,
3,
61737, 47, 39,
(Uint16)(0), (((Uint32)0)>>16),
61737, 48, 40,
(Uint16)(0), (((Uint32)0)>>16),
61737, 49, 41,
(Uint16)(0), (((Uint32)0)>>16),
61737, 50, 42,
(Uint16)(0), (((Uint32)0)>>16),

19629,
51,
3,
61737, 52, 43,
(Uint16)(0), (((Uint32)0)>>16),
61737, 53, 44,
(Uint16)(0), (((Uint32)0)>>16),
61737, 54, 45,
(Uint16)(0), (((Uint32)0)>>16),
61737, 55, 46,
(Uint16)(0), (((Uint32)0)>>16),

19625,
56,
3,
61741, 57, 47,
(Uint16)(0), (((Uint32)0)>>16),
61741, 58, 48,
(Uint16)(0), (((Uint32)0)>>16),
61741, 59, 49,
(Uint16)(0), (((Uint32)0)>>16),
61741, 60, 50,
(Uint16)(0), (((Uint32)0)>>16),

19625,
61,
3,
61741, 62, 51,
(Uint16)(0), (((Uint32)0)>>16),
61741, 63, 52,
(Uint16)(0), (((Uint32)0)>>16),
61741, 64, 53,
(Uint16)(0), (((Uint32)0)>>16),
61741, 65, 54,
(Uint16)(0), (((Uint32)0)>>16),

19629,
66,
3,
61729, 67, 55,
(Uint16)(0), (((Uint32)0)>>16),
61729, 68, 56,
(Uint16)(0), (((Uint32)0)>>16),
61729, 69, 57,
(Uint16)(0), (((Uint32)0)>>16),
61729, 70, 58,
(Uint16)(0), (((Uint32)0)>>16),

19629,
71,
3,
61729, 72, 59,
(Uint16)(0), (((Uint32)0)>>16),
61729, 73, 60,
(Uint16)(0), (((Uint32)0)>>16),
61729, 74, 61,
(Uint16)(0), (((Uint32)0)>>16),
61729, 75, 62,
(Uint16)(0), (((Uint32)0)>>16),

16562,
76,
2,
32045, 77, 63,
0,
31021, 21, 64,
0,
64301, 78, 65,
(Uint16)(100),
47405, 79, 66,
(Uint16)(0),
64301, 80, 67,
(Uint16)(100),

16560,
81,
2,
32045, 82, 68,
0,
31021, 21, 69,
0,
64301, 83, 70,
(Uint16)(100),
47405, 79, 71,
(Uint16)(0),
64301, 84, 72,
(Uint16)(1000),

16562,
85,
2,
32041, 86, 73,
0,
31017, 21, 74,
0,
64297, 87, 75,
(Uint16)(100),
47401, 79, 76,
(Uint16)(0),
64297, 88, 77,
(Uint16)(1000),

16556,
89,
2,
32041, 90, 78,
0,
31017, 21, 79,
0,
64297, 91, 80,
(Uint16)(100),
47401, 79, 81,
(Uint16)(0),
64297, 92, 82,
(Uint16)(1000),

16554,
93,
2,
32045, 94, 83,
0,
31021, 21, 84,
0,
64301, 95, 85,
(Uint16)(100),
47405, 79, 86,
(Uint16)(0),
64301, 96, 87,
(Uint16)(1000),

16552,
97,
2,
32045, 98, 88,
0,
31021, 21, 89,
0,
64301, 99, 90,
(Uint16)(100),
47405, 79, 91,
(Uint16)(0),
64301, 100, 92,
(Uint16)(1000),

16554,
101,
2,
32033, 102, 93,
0,
31009, 21, 94,
0,
64289, 103, 95,
(Uint16)(100),
47393, 79, 96,
(Uint16)(0),
64289, 104, 97,
(Uint16)(1000),

16556,
105,
2,
32033, 106, 98,
0,
31009, 21, 99,
0,
64289, 107, 100,
(Uint16)(100),
47393, 79, 101,
(Uint16)(0),
64289, 108, 102,
(Uint16)(1000),

19633,
109,
3,
63789, 110, 103,
(Uint16)(0), (((Uint32)0)>>16),
63789, 111, 104,
(Uint16)(0), (((Uint32)0)>>16),
63789, 112, 105,
(Uint16)(0), (((Uint32)0)>>16),
63789, 113, 106,
(Uint16)(0), (((Uint32)0)>>16),

19633,
114,
3,
63789, 115, 107,
(Uint16)(0), (((Uint32)0)>>16),
63789, 116, 108,
(Uint16)(0), (((Uint32)0)>>16),
63789, 117, 109,
(Uint16)(0), (((Uint32)0)>>16),
63789, 118, 110,
(Uint16)(0), (((Uint32)0)>>16),

19629,
119,
3,
63785, 120, 111,
(Uint16)(0), (((Uint32)0)>>16),
63785, 121, 112,
(Uint16)(0), (((Uint32)0)>>16),
63785, 122, 113,
(Uint16)(0), (((Uint32)0)>>16),
63785, 123, 114,
(Uint16)(0), (((Uint32)0)>>16),

19629,
124,
3,
63785, 125, 115,
(Uint16)(0), (((Uint32)0)>>16),
63785, 126, 116,
(Uint16)(0), (((Uint32)0)>>16),
63785, 127, 117,
(Uint16)(0), (((Uint32)0)>>16),
63785, 128, 118,
(Uint16)(0), (((Uint32)0)>>16),

19625,
129,
3,
63789, 130, 119,
(Uint16)(0), (((Uint32)0)>>16),
63789, 131, 120,
(Uint16)(0), (((Uint32)0)>>16),
63789, 132, 121,
(Uint16)(0), (((Uint32)0)>>16),
63789, 133, 122,
(Uint16)(0), (((Uint32)0)>>16),

19625,
134,
3,
63789, 135, 123,
(Uint16)(0), (((Uint32)0)>>16),
63789, 136, 124,
(Uint16)(0), (((Uint32)0)>>16),
63789, 137, 125,
(Uint16)(0), (((Uint32)0)>>16),
63789, 138, 126,
(Uint16)(0), (((Uint32)0)>>16),

19629,
139,
3,
63777, 140, 127,
(Uint16)(0), (((Uint32)0)>>16),
63777, 141, 128,
(Uint16)(0), (((Uint32)0)>>16),
63777, 142, 129,
(Uint16)(0), (((Uint32)0)>>16),
63777, 143, 130,
(Uint16)(0), (((Uint32)0)>>16),

19629,
144,
3,
63777, 145, 131,
(Uint16)(0), (((Uint32)0)>>16),
63777, 146, 132,
(Uint16)(0), (((Uint32)0)>>16),
63777, 147, 133,
(Uint16)(0), (((Uint32)0)>>16),
63777, 148, 134,
(Uint16)(0), (((Uint32)0)>>16),
64173, 149, 135,
(Uint16)(1),
(Uint16)(1), (Uint16)(127),
53469, 150, 136,
(Uint16)(3),

28845,
7,
1,
32041, 8, 137,
32041, 9, 138,
32041, 10, 139,
32041, 11, 140,

28845,
151,
1,
31529, 152, 141,
31529, 153, 142,
31529, 154, 143,
31529, 155, 144,
64813, 156, 145,
(Uint16)(0), (((Uint32)0)>>16),
20669, 157, 146,

28845,
158,
1,
32033, 159, 147,
32033, 160, 148,
32033, 161, 149,
32033, 162, 150,

28849,
163,
1,
32013, 164, 151,
32013, 165, 152,
32013, 166, 153,
32013, 167, 154,

28849,
168,
3,
64781, 169, 155,
(Uint16)(0), (((Uint32)0)>>16),
64781, 170, 156,
(Uint16)(0), (((Uint32)0)>>16),
64781, 171, 157,
(Uint16)(0), (((Uint32)0)>>16),
64781, 172, 158,
(Uint16)(0), (((Uint32)0)>>16),
53433, 173, 159,
(Uint16)(1),
53437, 174, 160,
(Uint16)(1),
30989, 175, 161,
31489, 176, 162,
32001, 177, 163,

28859,
178,
2,
47661, 179, 164,
(Uint16)(0),
47661, 180, 165,
(Uint16)(0x2000),
47661, 181, 166,
(Uint16)(0),
31277, 182, 167,
0,
31277, 183, 168,
0,
31277, 184, 169,
0,
31277, 185, 170,
0,
31277, 186, 171,
0,
31277, 187, 172,
0,
31277, 188, 173,
0,
31277, 189, 174,
0,
31277, 190, 175,
0,
31277, 190, 176,
0,
31277, 191, 177,
0,
31277, 192, 178,

28847,
193,
3,
48169, 194, 179,
(Uint16)(0x30000000), (((Uint32)0x30000000)>>16),
48169, 195, 180,
(Uint16)(0x30000000), (((Uint32)0x30000000)>>16),

28857,
196,
2,
36905, 197, 181,
(Uint16)(0),
36913, 198, 182,
(Uint16)(0),
36905, 199, 183,
(Uint16)(0),
36913, 200, 184,
(Uint16)(0),
36905, 201, 185,
(Uint16)(0),
36913, 202, 186,
(Uint16)(0),
36905, 203, 187,
(Uint16)(0),
36913, 204, 188,
(Uint16)(0),
36905, 205, 189,
(Uint16)(0),
36913, 206, 190,
(Uint16)(0),
36905, 207, 191,
(Uint16)(0),
36913, 208, 192,
(Uint16)(0),
36905, 209, 193,
(Uint16)(0),
36913, 210, 194,
(Uint16)(0),
36905, 211, 195,
(Uint16)(0),
36913, 212, 196,
(Uint16)(0),

28339,
213,
2,
31533, 214, 197,
0,
47917, 215, 198,
(Uint16)(32),
37117, 216, 199,
(Uint16)(0),
37074, 217, 200,
(Uint16)(1),
36580, 218, 201,
(Uint16)(0),
37143, 219, 202,
(Uint16)(0),

28339,
220,
2,
31533, 221, 203,
0,
47917, 222, 204,
(Uint16)(4128),
37117, 216, 205,
(Uint16)(0),
37072, 217, 206,
(Uint16)(1),
36578, 218, 207,
(Uint16)(0),
37143, 219, 208,
(Uint16)(4),

28339,
223,
2,
31529, 224, 209,
0,
47913, 225, 210,
(Uint16)(3136),
37113, 216, 211,
(Uint16)(0),
37074, 217, 212,
(Uint16)(2),
36576, 218, 213,
(Uint16)(0),
37143, 219, 214,
(Uint16)(3),

28339,
226,
2,
31529, 227, 215,
0,
47913, 228, 216,
(Uint16)(2112),
37113, 216, 217,
(Uint16)(0),
37068, 217, 218,
(Uint16)(2),
36578, 218, 219,
(Uint16)(0),
37143, 219, 220,
(Uint16)(2),

28331,
229,
2,
31533, 230, 221,
0,
47917, 231, 222,
(Uint16)(1056),
37117, 216, 223,
(Uint16)(0),
37066, 217, 224,
(Uint16)(1),
36580, 218, 225,
(Uint16)(0),
37143, 219, 226,
(Uint16)(1),

28331,
232,
2,
31533, 233, 227,
0,
47917, 234, 228,
(Uint16)(1056),
37117, 216, 229,
(Uint16)(0),
37064, 217, 230,
(Uint16)(1),
36570, 218, 231,
(Uint16)(0),
37143, 219, 232,
(Uint16)(1),

28331,
235,
2,
31521, 236, 233,
0,
47905, 237, 234,
(Uint16)(1088),
37105, 216, 235,
(Uint16)(0),
37066, 217, 236,
(Uint16)(2),
36568, 218, 237,
(Uint16)(0),
37143, 219, 238,
(Uint16)(1),

28331,
238,
2,
31521, 239, 239,
0,
47905, 240, 240,
(Uint16)(2112),
37105, 216, 241,
(Uint16)(0),
37068, 217, 242,
(Uint16)(2),
36570, 218, 243,
(Uint16)(0),
37143, 219, 244,
(Uint16)(2),

28323,
241,
2,
31533, 242, 245,
0,
47917, 243, 246,
(Uint16)(9286),
37117, 216, 247,
(Uint16)(6),
37058, 217, 248,
(Uint16)(2),
36564, 218, 249,
(Uint16)(0),
37127, 219, 250,
(Uint16)(9),

28323,
244,
2,
31533, 245, 251,
0,
47917, 246, 252,
(Uint16)(5184),
37117, 216, 253,
(Uint16)(0),
37056, 217, 254,
(Uint16)(2),
36562, 218, 255,
(Uint16)(0),
37127, 219, 256,
(Uint16)(5),

28323,
247,
2,
31529, 248, 257,
0,
47913, 249, 258,
(Uint16)(12320),
37113, 216, 259,
(Uint16)(0),
37058, 217, 260,
(Uint16)(1),
36560, 218, 261,
(Uint16)(0),
37127, 219, 262,
(Uint16)(12),

28323,
250,
2,
31529, 251, 263,
0,
47913, 252, 264,
(Uint16)(6144),
37113, 216, 265,
(Uint16)(0),
37068, 217, 266,
(Uint16)(0),
36562, 218, 267,
(Uint16)(0),
37127, 219, 268,
(Uint16)(6),

28331,
253,
2,
31533, 254, 269,
0,
47917, 255, 270,
(Uint16)(7168),
37117, 216, 271,
(Uint16)(0),
37066, 217, 272,
(Uint16)(0),
36564, 218, 273,
(Uint16)(0),
37127, 219, 274,
(Uint16)(7),

28331,
256,
2,
31533, 257, 275,
0,
47917, 258, 276,
(Uint16)(2048),
37117, 216, 277,
(Uint16)(0),
37064, 217, 278,
(Uint16)(0),
36570, 218, 279,
(Uint16)(0),
37127, 219, 280,
(Uint16)(2),

28331,
259,
2,
31505, 260, 281,
0,
47889, 261, 282,
(Uint16)(1024),
37089, 216, 283,
(Uint16)(0),
37066, 217, 284,
(Uint16)(0),
36568, 218, 285,
(Uint16)(0),
37127, 219, 286,
(Uint16)(1),

28331,
262,
2,
31505, 263, 287,
0,
47889, 264, 288,
(Uint16)(96),
37089, 216, 289,
(Uint16)(0),
37068, 217, 290,
(Uint16)(3),
36570, 218, 291,
(Uint16)(0),
37127, 219, 292,
(Uint16)(0),

28339,
265,
2,
31501, 266, 293,
0,
47885, 267, 294,
(Uint16)(3136),
37117, 216, 295,
(Uint16)(0),
37074, 217, 296,
(Uint16)(2),
36548, 218, 297,
(Uint16)(0),
37143, 219, 298,
(Uint16)(3),

28339,
268,
2,
31501, 269, 299,
0,
47885, 270, 300,
(Uint16)(9408),
37117, 216, 301,
(Uint16)(0),
37072, 217, 302,
(Uint16)(2),
36546, 218, 303,
(Uint16)(1),
37143, 219, 304,
(Uint16)(9),

28339,
271,
2,
31497, 272, 305,
0,
47881, 273, 306,
(Uint16)(9414),
37113, 216, 307,
(Uint16)(6),
37074, 217, 308,
(Uint16)(2),
36544, 218, 309,
(Uint16)(1),
37143, 219, 310,
(Uint16)(9),

28339,
274,
2,
31497, 275, 311,
0,
47881, 276, 312,
(Uint16)(12352),
37113, 216, 313,
(Uint16)(0),
37036, 217, 314,
(Uint16)(2),
36546, 218, 315,
(Uint16)(0),
37143, 219, 316,
(Uint16)(12),

28299,
277,
2,
31501, 278, 317,
0,
47885, 279, 318,
(Uint16)(13344),
37117, 216, 319,
(Uint16)(0),
37034, 217, 320,
(Uint16)(1),
36548, 218, 321,
(Uint16)(0),
37143, 219, 322,
(Uint16)(13),

28299,
280,
2,
31501, 281, 323,
0,
47885, 282, 324,
(Uint16)(10240),
37117, 216, 325,
(Uint16)(0),
37032, 217, 326,
(Uint16)(0),
36570, 218, 327,
(Uint16)(0),
37143, 219, 328,
(Uint16)(10),

28299,
283,
2,
31489, 284, 329,
0,
47873, 285, 330,
(Uint16)(14400),
37105, 216, 331,
(Uint16)(0),
37034, 217, 332,
(Uint16)(2),
36568, 218, 333,
(Uint16)(0),
37143, 219, 334,
(Uint16)(14),

28299,
286,
2,
31489, 287, 335,
0,
47873, 288, 336,
(Uint16)(15430),
37105, 216, 337,
(Uint16)(6),
37036, 217, 338,
(Uint16)(2),
36570, 218, 339,
(Uint16)(0),
37143, 219, 340,
(Uint16)(15),

28291,
289,
2,
31501, 290, 341,
0,
47885, 291, 342,
(Uint16)(16448),
37117, 216, 343,
(Uint16)(0),
37026, 217, 344,
(Uint16)(2),
36564, 218, 345,
(Uint16)(0),
36583, 219, 346,
(Uint16)(16),

28291,
292,
2,
31501, 293, 347,
0,
47885, 294, 348,
(Uint16)(13312),
37117, 216, 349,
(Uint16)(0),
37024, 217, 350,
(Uint16)(0),
36562, 218, 351,
(Uint16)(0),
36583, 219, 352,
(Uint16)(13),

28291,
295,
2,
31497, 296, 353,
0,
47881, 297, 354,
(Uint16)(14336),
37113, 216, 355,
(Uint16)(0),
37026, 217, 356,
(Uint16)(0),
36560, 218, 357,
(Uint16)(0),
36583, 219, 358,
(Uint16)(14),

28291,
298,
2,
31497, 299, 359,
0,
47881, 300, 360,
(Uint16)(12384),
37113, 216, 361,
(Uint16)(0),
37036, 217, 362,
(Uint16)(3),
36562, 218, 363,
(Uint16)(0),
36583, 219, 364,
(Uint16)(12),

28299,
301,
2,
31501, 302, 365,
0,
47885, 303, 366,
(Uint16)(0),
37117, 216, 367,
(Uint16)(0),
37034, 217, 368,
(Uint16)(0),
36564, 218, 369,
(Uint16)(0),
36583, 219, 370,
(Uint16)(0),

28299,
304,
2,
31501, 305, 371,
0,
47885, 306, 372,
(Uint16)(0),
37117, 216, 373,
(Uint16)(0),
37032, 217, 374,
(Uint16)(0),
36570, 218, 375,
(Uint16)(0),
36583, 219, 376,
(Uint16)(0),

28333,
307,
4,
36537, 308, 377,
(Uint16)(256),
0,
0,
36542, 309, 378,
(Uint16)(256),
0,
0,
36543, 310, 379,
(Uint16)(256),
0,
0,
45225, 307, 380,
(Uint16)(0),
(Uint16)(0), (Uint16)(1),

28333,
756,
3,
48417, 581, 381,
(Uint16)(0), (((Uint32)0)>>16),
48417, 582, 382,
(Uint16)(0), (((Uint32)0)>>16),
48417, 754, 383,
(Uint16)(0), (((Uint32)0)>>16),
48417, 753, 384,
(Uint16)(0), (((Uint32)0)>>16),

28236,
312,
1,
20169, 313, 385,
18737, 314, 386,
20153, 312, 387,

28238,
315,
2,
45261, 316, 388,
(Uint16)(15),

27822,
577,
3,
45357, 577, 389,
(Uint16)(0x11111111), (((Uint32)0x11111111)>>16),
20749, 317, 390,

3762,
312,
2,
47917, 318, 391,
(Uint16)(58002),
47917, 319, 392,
(Uint16)(14349),
47917, 320, 393,
(Uint16)(64364),
47917, 321, 394,
(Uint16)(3745),
47917, 322, 395,
(Uint16)(1832),

28848,
323,
7,
58853, 324, 396,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(_IQ(120.0)), (((Uint32)_IQ(120.0))>>16),
26437, 325, 397,
0,
0,
0,
0,
0,
0,
26437, 326, 398,
0,
0,
0,
0,
0,
0,

20154,
327,
7,
25925, 328, 399,
0,
0,
0,
0,
0,
0,
25925, 329, 400,
0,
0,
0,
0,
0,
0,
9381, 330, 401,
(Uint16)(335544), (((Uint32)335544)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9509, 331, 402,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(_IQ(-1.0)), (((Uint32)_IQ(-1.0))>>16), (Uint16)(_IQ(1.0)), (((Uint32)_IQ(1.0))>>16),
9509, 332, 403,
(Uint16)(-16777216), (((Uint32)-16777216)>>16),
(Uint16)(_IQ(-1.0)), (((Uint32)_IQ(-1.0))>>16), (Uint16)(_IQ(1.0)), (((Uint32)_IQ(1.0))>>16),
9381, 333, 404,
(Uint16)(2684354), (((Uint32)2684354)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9381, 334, 405,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9381, 335, 406,
(Uint16)(8388608), (((Uint32)8388608)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
25925, 336, 407,
0,
0,
0,
0,
0,
0,
25893, 337, 408,
0,
0,
0,
0,
0,
0,
25893, 338, 409,
0,
0,
0,
0,
0,
0,
25893, 339, 410,
0,
0,
0,
0,
0,
0,
25893, 340, 411,
0,
0,
0,
0,
0,
0,

20155,
341,
7,
26437, 342, 412,
0,
0,
0,
0,
0,
0,
26437, 343, 413,
0,
0,
0,
0,
0,
0,
9381, 330, 414,
(Uint16)(3355443), (((Uint32)3355443)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9541, 331, 415,
(Uint16)(13421772), (((Uint32)13421772)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9541, 332, 416,
(Uint16)(-13421772), (((Uint32)-13421772)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9381, 333, 417,
(Uint16)(16777), (((Uint32)16777)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9381, 344, 418,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9381, 335, 419,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
26437, 336, 420,
0,
0,
0,
0,
0,
0,
25925, 345, 421,
0,
0,
0,
0,
0,
0,
25925, 338, 422,
0,
0,
0,
0,
0,
0,
25925, 339, 423,
0,
0,
0,
0,
0,
0,
25925, 340, 424,
0,
0,
0,
0,
0,
0,
25925, 346, 425,
0,
0,
0,
0,
0,
0,

20154,
347,
7,
25921, 348, 426,
0,
0,
0,
0,
0,
0,
25921, 349, 427,
0,
0,
0,
0,
0,
0,
9377, 350, 428,
(Uint16)(335544), (((Uint32)335544)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9505, 351, 429,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(_IQ(-1.0)), (((Uint32)_IQ(-1.0))>>16), (Uint16)(_IQ(1.0)), (((Uint32)_IQ(1.0))>>16),
9505, 352, 430,
(Uint16)(-16777216), (((Uint32)-16777216)>>16),
(Uint16)(_IQ(-1.0)), (((Uint32)_IQ(-1.0))>>16), (Uint16)(_IQ(1.0)), (((Uint32)_IQ(1.0))>>16),
9377, 353, 431,
(Uint16)(2684354), (((Uint32)2684354)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9377, 354, 432,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9377, 335, 433,
(Uint16)(8388608), (((Uint32)8388608)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
25921, 336, 434,
0,
0,
0,
0,
0,
0,
25889, 355, 435,
0,
0,
0,
0,
0,
0,
25889, 338, 436,
0,
0,
0,
0,
0,
0,
25889, 339, 437,
0,
0,
0,
0,
0,
0,
25889, 340, 438,
0,
0,
0,
0,
0,
0,

20157,
356,
7,
15401, 342, 439,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,
10017, 342, 440,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
26401, 343, 441,
0,
0,
0,
0,
0,
0,
31785, 343, 442,
0,
0,
0,
0,
0,
0,
9377, 330, 443,
(Uint16)(1174405120), (((Uint32)1174405120)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
10049, 331, 444,
(Uint16)(100663296), (((Uint32)100663296)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
10049, 332, 445,
(Uint16)(-100663296), (((Uint32)-100663296)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9377, 333, 446,
(Uint16)(83886), (((Uint32)83886)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9377, 344, 447,
(Uint16)(167772160), (((Uint32)167772160)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
15401, 357, 448,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,
9377, 358, 449,
(Uint16)(8388608), (((Uint32)8388608)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9377, 335, 450,
(Uint16)(8388608), (((Uint32)8388608)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
10017, 359, 451,
(Uint16)(13981), (((Uint32)13981)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
26401, 336, 452,
0,
0,
0,
0,
0,
0,
25761, 346, 453,
0,
0,
0,
0,
0,
0,
26433, 345, 454,
0,
0,
0,
0,
0,
0,
26433, 338, 455,
0,
0,
0,
0,
0,
0,
26433, 339, 456,
0,
0,
0,
0,
0,
0,
26433, 340, 457,
0,
0,
0,
0,
0,
0,
26401, 360, 458,
0,
0,
0,
0,
0,
0,

20156,
362,
7,
25893, 363, 459,
0,
0,
0,
0,
0,
0,
25893, 364, 460,
0,
0,
0,
0,
0,
0,
8901, 365, 461,
(Uint16)(14529069), (((Uint32)14529069)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0x01000000), (((Uint32)0x01000000)>>16),
31533, 366, 462,
0,
0,
0,
0,
0,
0,
31533, 367, 463,
0,
0,
0,
0,
0,
0,
31533, 368, 464,
0,
0,
0,
0,
0,
0,
31533, 369, 465,
0,
0,
0,
0,
0,
0,
11429, 370, 466,
(Uint16)(33554432), (((Uint32)33554432)>>16),
(Uint16)(_IQ(2.0)), (((Uint32)_IQ(2.0))>>16), (Uint16)(_IQ(10.0)), (((Uint32)_IQ(10.0))>>16),
11429, 371, 467,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(_IQ(10)), (((Uint32)_IQ(10))>>16),
8901, 372, 468,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
11965, 373, 469,
(Uint16)(1),
0,
0,
0,
0,
0,
15149, 374, 470,
(Uint16)(1),
0,
0,
0,
0,
0,
31661, 375, 471,
0,
0,
0,
0,
0,
0,
9367, 376, 472,
(Uint16)(20480), (((Uint32)20480)>>16),
(Uint16)(2048), (((Uint32)2048)>>16), (Uint16)(10240), (((Uint32)10240)>>16),
31277, 377, 473,
0,
0,
0,
0,
0,
0,
25893, 378, 474,
0,
0,
0,
0,
0,
0,
31533, 379, 475,
0,
0,
0,
0,
0,
0,

20143,
380,
2,
31273, 381, 476,
0,
53545, 382, 477,
(Uint16)(1),

20132,
383,
7,
15121, 384, 478,
(Uint16)(0),
0,
0,
0,
0,
0,
15121, 385, 479,
(Uint16)(0),
0,
0,
0,
0,
0,
53265, 386, 480,
(Uint16)(255),
0,
0,
0,
0,
0,
53289, 387, 481,
(Uint16)(255),
0,
0,
0,
0,
0,
53265, 388, 482,
(Uint16)(255),
0,
0,
0,
0,
0,
53289, 389, 483,
(Uint16)(255),
0,
0,
0,
0,
0,
9529, 390, 484,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9625, 391, 485,
(Uint16)(18454938), (((Uint32)18454938)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9625, 392, 486,
(Uint16)(6990506), (((Uint32)6990506)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
10041, 393, 487,
(Uint16)(100663296), (((Uint32)100663296)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9721, 639, 488,
(Uint16)(75497472), (((Uint32)75497472)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20146,
394,
7,
10017, 395, 489,
(Uint16)(67108), (((Uint32)67108)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9505, 396, 490,
(Uint16)(3355443), (((Uint32)3355443)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9505, 397, 491,
(Uint16)(3355443), (((Uint32)3355443)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9985, 398, 492,
(Uint16)(720992), (((Uint32)720992)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9601, 559, 493,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20144,
399,
7,
15241, 400, 494,
(Uint16)(2),
(Uint16)(1), (Uint16)(50),
0,
0,
0,
8265, 401, 495,
(Uint16)(5),
(Uint16)(0), (Uint16)(0),
0,
0,
0,
24617, 402, 496,
0,
0,
0,
0,
0,
0,
9129, 403, 497,
(Uint16)(500),
(Uint16)(0), (Uint16)(0),
0,
0,
0,
8233, 404, 498,
(Uint16)(36),
(Uint16)(0), (Uint16)(1000),
0,
0,
0,
10113, 405, 499,
(Uint16)(1048576), (((Uint32)1048576)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
10145, 406, 500,
(Uint16)(16777), (((Uint32)16777)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
24713, 407, 501,
0,
0,
0,
0,
0,
0,
11993, 408, 502,
(Uint16)(1),
0,
0,
0,
0,
0,

20106,
409,
2,
15117, 411, 503,
(Uint16)(4),
53693, 412, 504,
(Uint16)(0),
53695, 413, 505,
(Uint16)(1),
53694, 414, 506,
(Uint16)(256),
53688, 710, 507,
(Uint16)(256),

20149,
415,
4,
8257, 416, 508,
(Uint16)(81),
(Uint16)(0), (Uint16)(0),
16001, 417, 509,
(Uint16)(-14592),
(Uint16)(0), (Uint16)(0),
25913, 418, 510,
0,
0,
0,
8257, 419, 511,
(Uint16)(81),
(Uint16)(0), (Uint16)(0),
16001, 420, 512,
(Uint16)(-14592),
(Uint16)(0), (Uint16)(0),
25913, 421, 513,
0,
0,
0,
25913, 424, 514,
0,
0,
0,
8225, 425, 515,
(Uint16)(2050),
(Uint16)(0), (Uint16)(0),
16001, 426, 516,
(Uint16)(0),
(Uint16)(0), (Uint16)(0),
26009, 427, 517,
0,
0,
0,
16001, 711, 518,
(Uint16)(15),
(Uint16)(0), (Uint16)(0),
25273, 641, 519,
0,
0,
0,

20096,
428,
7,
26417, 429, 520,
0,
0,
0,
0,
0,
0,
25873, 430, 521,
0,
0,
0,
0,
0,
0,
10033, 431, 522,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9489, 432, 523,
(Uint16)(419430), (((Uint32)419430)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
10033, 433, 524,
(Uint16)(100663296), (((Uint32)100663296)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9489, 434, 525,
(Uint16)(12582912), (((Uint32)12582912)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
10033, 435, 526,
(Uint16)(100663296), (((Uint32)100663296)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20037,
436,
1,
26421, 437, 527,
26037, 438, 528,
25909, 439, 529,
25813, 440, 530,
25813, 441, 531,
25909, 442, 532,
28141, 613, 533,
28141, 614, 534,

20023,
443,
7,
14477, 444, 535,
(Uint16)(0),
0,
0,
0,
0,
0,
14989, 445, 536,
(Uint16)(192), (((Uint32)192)>>16),
0,
0,
0,
0,
14989, 446, 537,
(Uint16)(1359151123), (((Uint32)1359151123)>>16),
0,
0,
0,
0,
14989, 447, 538,
(Uint16)(1359085569), (((Uint32)1359085569)>>16),
0,
0,
0,
0,
14989, 448, 539,
(Uint16)(1359151122), (((Uint32)1359151122)>>16),
0,
0,
0,
0,
14989, 449, 540,
(Uint16)(1359020033), (((Uint32)1359020033)>>16),
0,
0,
0,
0,
53645, 450, 541,
(Uint16)(0),
0,
0,
0,
0,
0,
53685, 451, 542,
(Uint16)(1),
0,
0,
0,
0,
0,
11837, 452, 543,
(Uint16)(0),
0,
0,
0,
0,
0,
10949, 453, 544,
(Uint16)(6710886), (((Uint32)6710886)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
15757, 454, 545,
(Uint16)(50461787), (((Uint32)50461787)>>16),

20001,
455,
7,
14985, 456, 546,
(Uint16)(1000), (((Uint32)1000)>>16),
0,
0,
0,
0,
11839, 457, 547,
(Uint16)(2),
0,
0,
0,
0,
0,
14473, 458, 548,
(Uint16)(1),
0,
0,
0,
0,
0,
9345, 459, 549,
(Uint16)(9298387), (((Uint32)9298387)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
31369, 460, 550,
0,
0,
0,
0,
0,
0,
30857, 460, 551,
0,
0,
0,
0,
0,
0,
25761, 461, 552,
0,
0,
0,
0,
0,
0,
25729, 462, 553,
0,
0,
0,
0,
0,
0,
25729, 463, 554,
0,
0,
0,
0,
0,
0,
53565, 464, 555,
(Uint16)(0),
0,
0,
0,
0,
0,
9217, 465, 556,
(Uint16)(838860), (((Uint32)838860)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(65535), (((Uint32)65535)>>16),
30857, 466, 557,
0,
0,
0,
0,
0,
0,
30857, 467, 558,
0,
0,
0,
0,
0,
0,
30857, 468, 559,
0,
0,
0,
0,
0,
0,
31369, 469, 560,
0,
0,
0,
0,
0,
0,
30857, 469, 561,
0,
0,
0,
0,
0,
0,
30857, 470, 562,
0,
0,
0,
0,
0,
0,
15241, 471, 563,
(Uint16)(0),
0,
0,
0,
0,
0,
15241, 472, 564,
(Uint16)(7),
0,
0,
0,
0,
0,
15241, 472, 565,
(Uint16)(7335),
0,
0,
0,
0,
0,
15753, 472, 566,
(Uint16)(1973415), (((Uint32)1973415)>>16),
0,
0,
0,
0,
25729, 473, 567,
0,
0,
0,
0,
0,
0,
25729, 474, 568,
0,
0,
0,
0,
0,
0,
14473, 714, 569,
(Uint16)(0),
0,
0,
0,
0,
0,

20027,
475,
7,
15245, 589, 570,
(Uint16)(0),
0,
0,
0,
0,
0,
25733, 441, 571,
0,
0,
0,
0,
0,
0,
25765, 461, 572,
0,
0,
0,
0,
0,
0,
9381, 476, 573,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
25733, 477, 574,
0,
0,
0,
0,
0,
0,
11837, 478, 575,
(Uint16)(81),
0,
0,
0,
0,
0,
14989, 479, 576,
(Uint16)(500), (((Uint32)500)>>16),
0,
0,
0,
0,
25765, 480, 577,
0,
0,
0,
0,
0,
0,
30861, 481, 578,
0,
0,
0,
0,
0,
0,
4573, 482, 579,
0,
0,
0,
0,
0,
0,
9349, 459, 580,
(Uint16)(4869970), (((Uint32)4869970)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
30861, 483, 581,
0,
0,
0,
0,
0,
0,
30861, 484, 582,
0,
0,
0,
0,
0,
0,
30861, 485, 583,
0,
0,
0,
0,
0,
0,
30861, 486, 584,
0,
0,
0,
0,
0,
0,
53567, 487, 585,
(Uint16)(0),
0,
0,
0,
0,
0,
14477, 488, 586,
(Uint16)(10),
0,
0,
0,
0,
0,
30861, 489, 587,
0,
0,
0,
0,
0,
0,
30861, 490, 588,
0,
0,
0,
0,
0,
0,
30861, 491, 589,
0,
0,
0,
0,
0,
0,
30861, 492, 590,
0,
0,
0,
0,
0,
0,
30861, 493, 591,
0,
0,
0,
0,
0,
0,

20019,
455,
7,
14977, 494, 592,
(Uint16)(4096), (((Uint32)4096)>>16),
0,
0,
0,
0,
9369, 459, 593,
(Uint16)(9298387), (((Uint32)9298387)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
30849, 460, 594,
0,
0,
0,
0,
0,
0,
25785, 461, 595,
0,
0,
0,
0,
0,
0,
25753, 462, 596,
0,
0,
0,
0,
0,
0,
25753, 463, 597,
0,
0,
0,
0,
0,
0,
25753, 495, 598,
0,
0,
0,
0,
0,
0,
9241, 496, 599,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
15233, 471, 600,
(Uint16)(0),
0,
0,
0,
0,
0,
15745, 472, 601,
(Uint16)(1973415), (((Uint32)1973415)>>16),
0,
0,
0,
0,
15233, 472, 602,
(Uint16)(7),
0,
0,
0,
0,
0,
15233, 472, 603,
(Uint16)(7335),
0,
0,
0,
0,
0,
25753, 473, 604,
0,
0,
0,
0,
0,
0,
25753, 474, 605,
0,
0,
0,
0,
0,
0,

20025,
497,
7,
25669, 498, 606,
0,
0,
0,
0,
0,
0,
32205, 498, 607,
0,
0,
0,
0,
0,
0,
25669, 499, 608,
0,
0,
0,
0,
0,
0,
32205, 499, 609,
0,
0,
0,
0,
0,
0,
30925, 500, 610,
0,
0,
0,
0,
0,
0,
31693, 500, 611,
0,
0,
0,
0,
0,
0,
30925, 501, 612,
0,
0,
0,
0,
0,
0,
31693, 501, 613,
0,
0,
0,
0,
0,
0,
9285, 502, 614,
(Uint16)(16777), (((Uint32)16777)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
15821, 502, 615,
(Uint16)(16777), (((Uint32)16777)>>16),
0,
0,
0,
0,
9285, 503, 616,
(Uint16)(-190048), (((Uint32)-190048)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
15821, 503, 617,
(Uint16)(-190048), (((Uint32)-190048)>>16),
0,
0,
0,
0,
9285, 504, 618,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
15821, 504, 619,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,
9285, 505, 620,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
15821, 505, 621,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,
50253, 506, 622,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
50253, 507, 623,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
50253, 508, 624,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
50253, 509, 625,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20142,
556,
7,
9285, 557, 626,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9637, 558, 627,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
9637, 559, 628,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20149,
399,
7,
12453, 571, 629,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
12453, 572, 630,
(Uint16)(5033165), (((Uint32)5033165)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
12613, 573, 631,
(Uint16)(5033165), (((Uint32)5033165)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
28997, 574, 632,
0,
0,
0,
0,
0,
0,
28997, 575, 633,
0,
0,
0,
0,
0,
0,
28837, 536, 634,
0,
0,
0,
0,
0,
0,
28837, 537, 635,
0,
0,
0,
0,
0,
0,
30501, 576, 636,
0,
0,
0,
0,
0,
0,

20139,
626,
7,
17709, 631, 637,
0,
0,
0,
0,
0,
0,
15149, 627, 638,
(Uint16)(2000),
0,
0,
0,
0,
0,
10661, 628, 639,
(Uint16)(15099494), (((Uint32)15099494)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
10661, 629, 640,
(Uint16)(11744051), (((Uint32)11744051)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
28837, 630, 641,
0,
0,
0,
0,
0,
0,
12453, 632, 642,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20143,
482,
2,
27681, 482, 643,
0,
11297, 694, 644,
(Uint16)(0),

20139,
635,
7,
31521, 636, 645,
0,
0,
0,
0,
0,
0,
12793, 637, 646,
(Uint16)(41943040), (((Uint32)41943040)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
12793, 638, 647,
(Uint16)(25165824), (((Uint32)25165824)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
12793, 640, 648,
(Uint16)(67108864), (((Uint32)67108864)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
29177, 634, 649,
0,
0,
0,
0,
0,
0,
15137, 712, 650,
(Uint16)(0),
0,
0,
0,
0,
0,

20129,
713,
7,
15149, 589, 651,
(Uint16)(0),
0,
0,
0,
0,
0,
12693, 628, 652,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
12693, 629, 653,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),
31533, 570, 654,
0,
0,
0,
0,
0,
0,
};

int16 const CO1_OD_TBL1[] = {
4096, 0,
4097, 3,
4098, 6,
4116, 9,
4118, 12,
4119, 20,
4120, 24,
4608, 39,
4736, 48,
5120, 60,
5121, 73,
5122, 86,
5123, 99,
5124, 112,
5125, 125,
5126, 138,
5127, 151,
5632, 164,
5633, 187,
5634, 210,
5635, 233,
5636, 256,
5637, 279,
5638, 302,
5639, 325,
6144, 348,
6145, 371,
6146, 394,
6147, 417,
6148, 440,
6149, 463,
6150, 486,
6151, 509,
6656, 532,
6657, 555,
6658, 578,
6659, 601,
6660, 624,
6661, 647,
6662, 670,
6663, 693,
8192, 716,
8193, 722,
8194, 726,
8195, 741,
8196, 756,
8197, 761,
8199, 764,
8208, 779,
8209, 794,
8210, 817,
8212, 821,
8213, 825,
8214, 828,
8215, 831,
8320, 834,
8321, 893,
8322, 896,
8323, 909,
8448, 976,
8449, 1003,
8450, 1030,
8451, 1057,
8452, 1084,
8453, 1111,
8454, 1138,
8455, 1165,
8456, 1192,
8457, 1219,
8458, 1246,
8459, 1273,
8460, 1300,
8461, 1327,
8462, 1354,
8463, 1381,
8464, 1408,
8465, 1435,
8466, 1462,
8467, 1489,
8468, 1516,
8469, 1543,
8470, 1570,
8471, 1597,
8472, 1624,
8473, 1651,
8474, 1678,
8475, 1705,
8476, 1732,
8477, 1759,
9474, 1786,
9478, 1813,
9522, 1836,
9524, 1848,
9728, 1855,
12288, 1863,
12544, 1866,
20480, 1889,
20736, 1919,
20737, 2039,
20738, 2168,
20739, 2288,
20741, 2471,
20747, 2627,
20750, 2638,
20754, 2740,
20755, 2788,
20756, 2872,
20758, 2895,
20762, 2970,
20792, 3036,
20816, 3063,
20817, 3156,
20818, 3161,
20821, 3380,
20823, 3581,
20852, 3710,
20869, 3893,
23300, 3923,
23301, 3998,
23302, 4055,
23303, 4066,
23304, 4123,
};
Uint16 const co1_SPIrange1rw = CO1_SPI_START_ADDR+0;
Uint16 const co1_SPIrange1rwCRC = CO1_SPI_START_ADDR+8;
Uint16 const co1_SPIrange1rwp = CO1_SPI_START_ADDR+10;
Uint16 const co1_SPIrange1rwpCRC = CO1_SPI_START_ADDR+336;
Uint16 const co1_SPIrange1rwps = CO1_SPI_START_ADDR+338;
Uint16 const co1_SPIrange1rwpsCRC = CO1_SPI_START_ADDR+338;
Uint16 const co1_SPIrange2rw = CO1_SPI_START_ADDR+340;
Uint16 const co1_SPIrange2rwCRC = CO1_SPI_START_ADDR+577;
Uint16 const co1_SPIrange2rwp = CO1_SPI_START_ADDR+579;
Uint16 const co1_SPIrange2rwpCRC = CO1_SPI_START_ADDR+604;
Uint16 const co1_SPIrange2rwps = CO1_SPI_START_ADDR+606;
Uint16 const co1_SPIrange2rwpsCRC = CO1_SPI_START_ADDR+606;
Uint16 const co1_SPIrange3rw = CO1_SPI_START_ADDR+608;
Uint16 const co1_SPIrange3rwCRC = CO1_SPI_START_ADDR+618;
Uint16 const co1_SPIrange3rwp = CO1_SPI_START_ADDR+620;
Uint16 const co1_SPIrange3rwpCRC = CO1_SPI_START_ADDR+620;
Uint16 const co1_SPIrange3rwps = CO1_SPI_START_ADDR+622;
Uint16 const co1_SPIrange3rwpsCRC = CO1_SPI_START_ADDR+622;
Uint16 const co1_SPIrange4rw = CO1_SPI_START_ADDR+624;
Uint16 const co1_SPIrange4rwCRC = CO1_SPI_START_ADDR+624;
Uint16 const co1_SPIrange4rwp = CO1_SPI_START_ADDR+626;
Uint16 const co1_SPIrange4rwpCRC = CO1_SPI_START_ADDR+626;
Uint16 const co1_SPIrange4rwps = CO1_SPI_START_ADDR+628;
Uint16 const co1_SPIrange4rwpsCRC = CO1_SPI_START_ADDR+628;
Uint16 const co1_SPIrange5rw = CO1_SPI_START_ADDR+630;
Uint16 const co1_SPIrange5rwCRC = CO1_SPI_START_ADDR+1087;
Uint16 const co1_SPIrange5rwp = CO1_SPI_START_ADDR+1089;
Uint16 const co1_SPIrange5rwpCRC = CO1_SPI_START_ADDR+1093;
Uint16 const co1_SPIrange5rwps = CO1_SPI_START_ADDR+1095;
Uint16 const co1_SPIrange5rwpsCRC = CO1_SPI_START_ADDR+1095;
Uint16 const co1_first1000 = 0;
Uint16 const co1_first2000 = 82;
Uint16 const co1_first3000 = 188;
Uint16 const co1_first4000 = 192;
Uint16 const co1_first5000 = 192;
// ������� �����
Uint16 const CO1_TYPE_DEF_TABLE[] = {
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)5,\
    (Uint16)0,\
    (Uint16)10,\
    (Uint16)4,\
    (Uint16)0,\
    (Uint16)0,\
    (Uint16)40,\
    (Uint16)17,\
    (Uint16)6,\
    (Uint16)8,\
    (Uint16)7,\
    (Uint16)9,\
    (Uint16)15,\
    (Uint16)36,\
    (Uint16)16,\
    (Uint16)1,\
    (Uint16)13,\
    (Uint16)12,\
    (Uint16)14,\
    (Uint16)18,\
    (Uint16)-1,\
    (Uint16)28,\
    (Uint16)0,\
    (Uint16)24,\
    (Uint16)23,\
    (Uint16)25,\
    (Uint16)27,\
    (Uint16)19,\
    (Uint16)20,\
    (Uint16)46,\
    (Uint16)2,\
    (Uint16)45,\
    (Uint16)44,\
};
// ������� CALLBACK-�������
//**************************************************************
long const CO1_OD_CALLBACK_TBL[]={
0, // 1000h.00h
0, // 1001h.00h
0, // 1002h.00h
0, // 1014h.00h
0, // 1016h.00h
0, // 1017h.00h
0, // 1018h.00h
0, // 1200h.00h
0, // 1280h.00h
0, // 1400h.00h
0, // 1401h.00h
0, // 1402h.00h
0, // 1403h.00h
0, // 1404h.00h
0, // 1405h.00h
0, // 1406h.00h
0, // 1407h.00h
0, // 1600h.00h
0, // 1601h.00h
0, // 1602h.00h
0, // 1603h.00h
0, // 1604h.00h
0, // 1605h.00h
0, // 1606h.00h
0, // 1607h.00h
0, // 1800h.00h
0, // 1801h.00h
0, // 1802h.00h
0, // 1803h.00h
0, // 1804h.00h
0, // 1805h.00h
0, // 1806h.00h
0, // 1807h.00h
0, // 1A00h.00h
0, // 1A01h.00h
0, // 1A02h.00h
0, // 1A03h.00h
0, // 1A04h.00h
0, // 1A05h.00h
0, // 1A06h.00h
0, // 1A07h.00h
0, // 2000h.00h
0, // 2001h.00h
0, // 2002h.00h
0, // 2003h.00h
0, // 2004h.00h
0, // 2005h.00h
0, // 2007h.00h
0, // 2010h.00h
0, // 2011h.00h
0, // 2012h.00h
0, // 2014h.00h
0, // 2015h.00h
0, // 2016h.00h
0, // 2017h.00h
0, // 2080h.00h
0, // 2081h.00h
0, // 2082h.00h
0, // 2083h.00h
0, // 2100h.00h
0, // 2101h.00h
0, // 2102h.00h
0, // 2103h.00h
0, // 2104h.00h
0, // 2105h.00h
0, // 2106h.00h
0, // 2107h.00h
0, // 2108h.00h
0, // 2109h.00h
0, // 210Ah.00h
0, // 210Bh.00h
0, // 210Ch.00h
0, // 210Dh.00h
0, // 210Eh.00h
0, // 210Fh.00h
0, // 2110h.00h
0, // 2111h.00h
0, // 2112h.00h
0, // 2113h.00h
0, // 2114h.00h
0, // 2115h.00h
0, // 2116h.00h
0, // 2117h.00h
0, // 2118h.00h
0, // 2119h.00h
0, // 211Ah.00h
0, // 211Bh.00h
0, // 211Ch.00h
0, // 211Dh.00h
0, // 2502h.00h
0, // 2506h.00h
0, // 2532h.00h
0, // 2534h.00h
0, // 2600h.00h
0, // 3000h.00h
0, // 3100h.00h
0, // 5000h.00h
0, // 5100h.00h
0, // 5101h.00h
0, // 5102h.00h
0, // 5103h.00h
0, // 5105h.00h
0, // 510Bh.00h
0, // 510Eh.00h
0, // 5112h.00h
0, // 5113h.00h
0, // 5114h.00h
0, // 5116h.00h
0, // 511Ah.00h
0, // 5138h.00h
0, // 5150h.00h
(long)((void(*)(long))callback_dlog), // 5151h.00h
0, // 5152h.00h
0, // 5155h.00h
0, // 5157h.00h
0, // 5174h.00h
0, // 5185h.00h
0, // 5B04h.00h
0, // 5B05h.00h
0, // 5B06h.00h
0, // 5B07h.00h
0, // 5B08h.00h
};

// ������ ������ ��� �������� CANopen ����������� �����������
#ifdef COOD_LINKS__5000
long const CO1_LINKS[]={(long)&co1_numOfInd,
                        (long)&CO1_OD_TBL1,
                        (long)&CO1_OD_TBL2,
                        (long)&CO1_OD_TBL3,
                        (long)&CO1_TYPE_DEF_TABLE,
                        (long)&CO1_OD_CALLBACK_TBL,
                        (long)&co1_SPIrange1rw,
                        (long)&co1_SPIrange1rwCRC,
                        (long)&co1_SPIrange1rwp,
                        (long)&co1_SPIrange1rwpCRC,
                        (long)&co1_SPIrange1rwps,
                        (long)&co1_SPIrange1rwpsCRC,
                        (long)&co1_SPIrange2rw,
                        (long)&co1_SPIrange2rwCRC,
                        (long)&co1_SPIrange2rwp,
                        (long)&co1_SPIrange2rwpCRC,
                        (long)&co1_SPIrange2rwps,
                        (long)&co1_SPIrange2rwpsCRC,
                        (long)&co1_SPIrange3rw,
                        (long)&co1_SPIrange3rwCRC,
                        (long)&co1_SPIrange3rwp,
                        (long)&co1_SPIrange3rwpCRC,
                        (long)&co1_SPIrange3rwps,
                        (long)&co1_SPIrange3rwpsCRC,
                        (long)&co1_SPIrange4rw,
                        (long)&co1_SPIrange4rwCRC,
                        (long)&co1_SPIrange4rwp,
                        (long)&co1_SPIrange4rwpCRC,
                        (long)&co1_SPIrange4rwps,
                        (long)&co1_SPIrange4rwpsCRC,
                        (long)&co1_SPIrange5rw,
                        (long)&co1_SPIrange5rwCRC,
                        (long)&co1_SPIrange5rwp,
                        (long)&co1_SPIrange5rwpCRC,
                        (long)&co1_SPIrange5rwps,
                        (long)&co1_SPIrange5rwpsCRC,
                        (long)&co1_first1000,
                        (long)&co1_first2000,
                        (long)&co1_first3000,
                        (long)&co1_first4000,
                        (long)&co1_first5000
};

STATIC_ASSERT(((sizeof(CO1_LINKS)/sizeof(CO1_LINKS[0])) == (COOD_LINKS__5000 + 1)),m);
#endif