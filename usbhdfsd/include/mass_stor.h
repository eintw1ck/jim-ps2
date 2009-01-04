#ifndef _MASS_STOR_H
#define _MASS_STOR_H 1

typedef struct _mass_dev
{
	int controlEp;		//config endpoint id
	int bulkEpI;		//in endpoint id
	unsigned char bulkEpIAddr; // in endpoint address
	int bulkEpO;		//out endpoint id
	unsigned char bulkEpOAddr; // out endpoint address
	int packetSzI;		//packet size in
	int packetSzO;		//packet size out
	int devId;		//device id
	int configId;	//configuration id
	int status;
	int interfaceNumber;	//interface number
	int interfaceAlt;	//interface alternate setting
	unsigned sectorSize; // = 512; // store size of sector from usb mass
	unsigned maxLBA;
} mass_dev;

int InitUSB();
int mass_stor_disconnect(int devId);
int mass_stor_connect(int devId);
int mass_stor_probe(int devId);
int mass_stor_readSector4096(mass_dev* mass_device, unsigned int sector, unsigned char* buffer);
int mass_stor_writeSector4096(mass_dev* mass_device, unsigned int sector, unsigned char* buffer);
int mass_stor_getStatus(mass_dev* mass_device);
void mass_stor_clearDisconnected(mass_dev* mass_device);
mass_dev* mass_stor_getDevice(int device);

#endif