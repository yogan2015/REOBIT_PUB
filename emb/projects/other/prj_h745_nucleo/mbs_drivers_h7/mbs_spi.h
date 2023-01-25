#ifndef SPI_H
#define SPI_H



struct MBS_SPI_CONTROL {
	short enable;
	short error;
	short memInfo;
};


typedef struct{
	struct MBS_SPI_CONTROL control;

}SPI_Driver;



#endif
