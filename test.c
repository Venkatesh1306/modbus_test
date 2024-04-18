/*
 * File:   test.c
 * Author: Green2
 *
 * Created on 9 April, 2024, 11:13 AM
 * developed for testing the inputs 
 */
#include"Z:\MPLAB File\ModbusFn03\Version5.X\GenericTypeDefs_1.h"
#include"Z:\MPLAB File\ModbusFn03\Version5.X\testingdata.h"
#include <stdio.h>

#define illegal_address  ENOREG
#define Function_error ENOFUNC
#define Illegal_data_value EILLDATA
#define test_ing
#define INR_SIZE 20



typedef enum
{
    NOERR    = 0,        /*!< no error. */
    ENOFUNC  = 1,       /*<Function error*/
    ENOREG   = 2,      /*!< illegal register address. */
    EILLDATA = 3
} ErrorCode;


BYTE ModbusTcpRxBuf[16];
BYTE ModbusTcpTxBuf[25];
BYTE Test_TX[25];
int increment; 
int Test_Res;
int inc;
WORD_VAL Mod[0];

BYTE ModbusRXbuftest[INR_SIZE][16] = {
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x09, 0x00, 0x08},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x03, 0x00, 0x04},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x03, 0x00, 0x01},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x09, 0x00, 0x07, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x28, 0x00, 0x03},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x27, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x02, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x09, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x28, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x0E, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x01, 0x00, 0x04},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x09, 0x00, 0x02, 0x00, 0x04},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x05, 0x00, 0x01},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x07, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x10, 0x00, 0x9},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x35, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x1A, 0x00, 0x07},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x09, 0x00, 0x20, 0x00, 0x08},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x04, 0x00, 0x09},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x03, 0x00, 0x02}
};
WORD DataRegister[100] = {0x3A2B, 0x3c7e, 0x0302, 0xFFFF, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e};
WORD error_1test(ErrorCode error);
WORD processexpecteddata( BYTE *ModbusTcpRxBuf,BYTE *Test_TX,WORD DataRegister[]);
WORD Test_ing(const BYTE ModbusTcpTxBuf[], const BYTE Test_TX[]);

parse1 parse;

WORD frame_function (BYTE *ModbusTcpRxBuf , WORD *DataRegister, parse1 *parse , BYTE *ModbusTcpTxBuf);
int main ()
{
    int j;
    for(inc = 0;inc< INR_SIZE; inc++){
    for( j = 0;j< 12; j++){
          Mod[0].Val = 0;
          ModbusTcpRxBuf[j] = ModbusRXbuftest[inc][j];
    }
    if(ModbusTcpRxBuf[7]==0x16){
        
        Mod[0].v[1] = ModbusRXbuftest[inc][10];
        Mod[0].v[0] = ModbusRXbuftest[inc][11];
    for( j = 0;j< 0xC + (Mod[0].Val*2); j++){
          ModbusTcpRxBuf[j] = ModbusRXbuftest[inc][j];
    }
    }
   processexpecteddata(ModbusTcpRxBuf,Test_TX,DataRegister);
   frame_function(&ModbusTcpRxBuf[0] ,&DataRegister[0], &parse , &ModbusTcpTxBuf[0]);
   Test_ing(ModbusTcpTxBuf,Test_TX);

   
#ifdef test_ing


printf("\nQuery Packet:%d", inc + 1);
    if (ModbusTcpTxBuf[7] > 0x80) {
        switch(ModbusTcpTxBuf[8]) {
            case 1:
                printf(" - Function Error");
                break;
            case 2:
                printf(" - Address Error");
                break;
            case 3:
                printf(" - Data Error");
                break;
        }
    }
printf("\n");
for (int i = 0; i < 0xC + (Mod[0].Val * 2); i++)
    printf("%02X ", ModbusTcpRxBuf[i]);
printf("\n");

printf("Expected Response:\n");
int responseLength = (ModbusTcpTxBuf[7] == 0x06) ? 0x0C : ((ModbusTcpTxBuf[7] < 0x80) ? 0x09 + ModbusTcpTxBuf[8] : 0x09);
for (int i = 0; i < responseLength; i++)
    printf("%02X ", Test_TX[i]);
printf("\n");

printf("Actual Response:\n");
for (int i = 0; i < responseLength; i++)
    printf("%02X ", ModbusTcpTxBuf[i]);
printf("\n");

if (Test_Res == 1) {

        printf("Test Passed\n", inc + 1);
} else {
    printf("Test failed\n", inc + 1);
}



#endif
    
}

}

WORD processexpecteddata( BYTE *ModbusTcpRxBuf,BYTE *Test_TX,WORD DataRegister[]){
        ErrorCode error;
        Test_TX[0]  = ModbusTcpRxBuf[0];
        Test_TX[1]  = ModbusTcpRxBuf[1];
        Test_TX[2]  = ModbusTcpRxBuf[2];
        Test_TX[3]  = ModbusTcpRxBuf[3];
        Test_TX[4]  = ModbusTcpRxBuf[4];
        Test_TX[5]  = ModbusTcpRxBuf[5];
        Test_TX[6]  = ModbusTcpRxBuf[6];
        Test_TX[7]  = ModbusTcpRxBuf[7];
        Test_TX[8]  = ModbusTcpRxBuf[8];
        Test_TX[9]  = ModbusTcpRxBuf[9];
        Test_TX[10] = ModbusTcpRxBuf[10];
        Test_TX[11] = ModbusTcpRxBuf[11];

if(ModbusTcpRxBuf[7]==0x03){   
        Test_TX[8] = ModbusTcpRxBuf[11] * 2;
        Test_TX[5] = Test_TX[8] + 0x03;
 for (increment = 0; increment < ModbusTcpRxBuf[11]; increment++) {
        Test_TX[9 + increment * 2] = DataRegister[ModbusTcpRxBuf[9] + increment] / 0x100;   // High byte
        Test_TX[10 + increment * 2] = DataRegister[ModbusTcpRxBuf[9] + increment] % 0x100; // Low byte
    }
      
}
if(ModbusTcpRxBuf[7]!=0x03 && ModbusTcpRxBuf[7]!=0x06 ){
    error = 1;
    error_1test(error);
}
else if(ModbusTcpRxBuf[9] > 0x19){
    error = 2;
    error_1test(error);
}
if(ModbusTcpRxBuf[7] == 6){
    if(ModbusTcpRxBuf[10]>253 &&  ModbusTcpRxBuf[10]>232){
        error = 3;
        error_1test(error);

    }
}        return 0;
}



WORD error_1test(ErrorCode error) {
        //testing
        Test_TX[5]  =  0x03;
        Test_TX[7]  =  0x80 + Test_TX[7];
        Test_TX[8]  =  error;
    return error; // Return error code or consider if another return type or handling is needed
}




//function for testing the output with the expected output
WORD Test_ing(const BYTE ModbusTcpTxBuf[], const BYTE Test_TX[]) {

    Test_Res = 1; 
    if(ModbusTcpTxBuf[7] < 0x80){
    for (increment = 0; increment < 0x08 + ModbusTcpTxBuf[8]; increment++) {
        if (ModbusTcpTxBuf[increment] != Test_TX[increment]) {
            Test_Res = 0; 
            break; 
        }
    }
    }
    else{
        for (increment = 0; increment < 0x09 ; increment++) {
        if (ModbusTcpTxBuf[increment] != Test_TX[increment]) {
            Test_Res = 0; 
            break; 
        } 
    }
    }
    return Test_Res;
}
