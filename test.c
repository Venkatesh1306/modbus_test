/*
 * File:   test.c
 * Author: Green2
 *
 * Created on 9 April, 2024, 11:13 AM
 * developed for testing the inputs 
 */
#include "D:\Version6\GenericTypeDefs_1.h"
#include"D:\Version6\Modbus1\testingdata.h"
#include <stdio.h>

#define illegal_address  ENOREG
#define Function_error ENOFUNC
#define Illegal_data_value EILLDATA
#define test_ing
#define INR_SIZE 10

// ANSI escape codes for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_ORANGE  "\x1b[33m"  
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef enum
{
    NOERR    = 0,        /*!< no error. */
    ENOFUNC  = 1,       /*<Function error*/
    ENOREG   = 2,      /*!< illegal register address. */
    EILLDATA = 3
} ErrorCode;


unsigned char ModbusTcpRxBuf[100];
unsigned char ModbusTcpTxBuf[25];
unsigned char Test_TX[25];
int increment; 
int Test_Res;
int inc;
int test_c;
WORD_VAL Mod[0];
//unsigned short int DataRegister1[100];
unsigned int ModbusTxLength;
unsigned char ModbusRXbuftest[INR_SIZE][100] = {
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x09, 0x00, 0x08},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x06, 0x00, 0x03, 0x03, 0x04},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x10, 0x00, 0x06, 0x00, 0x02,0x04,0x03,0x04,0x3c,0x7e},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x09, 0x00, 0x07, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x28, 0x00, 0x03},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x06, 0x00, 0x27, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x10, 0x00, 0x30, 0x00, 0x06},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x06, 0x00, 0x09, 0xff, 0xff},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x10, 0x00, 0x0C, 0x00, 0x03,0x06,0xff,0xff,0x06,0x05,0x06,0x05},
{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x10, 0x00, 0x0C, 0x00, 0x03,0x06,0x00,0x06,0x06,0x05,0x06,0x05}
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x0E, 0x00, 0x06},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x01, 0x00, 0x04},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x09, 0x00, 0x02, 0x00, 0x04},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x05, 0x00, 0x01},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x07, 0x00, 0x06},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x10, 0x00, 0x9},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x35, 0x00, 0x06},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x1A, 0x00, 0x07},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x04, 0x00, 0x09},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x06, 0x00, 0x03, 0x00, 0x02},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x10, 0x00, 0x06, 0x00, 0x02,0x04,0x03,0x04,0x3c,0x7e},
//{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x06, 0x00, 0x02}

};
unsigned short int DataRegister[100] = {0x3A2B, 0x3c7e, 0x0302, 0xFFFF, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e};
unsigned short int error_1test(ErrorCode error);
unsigned short int processexpecteddata( unsigned char *ModbusTcpRxBuf,unsigned char *Test_TX,unsigned short int DataRegister[]);
unsigned short int Test_ing(const unsigned char ModbusTcpTxBuf[], const unsigned char Test_TX[]);

parse1 parse;






WORD frame_function (BYTE *ModbusTcpRxBuf ,WORD *DataRegister, parse1 *parse , BYTE *ModbusTcpTxBuf,unsigned int *ModbusTxLength);
int main ()
{
   
    int j;
    for(inc = 0;inc< INR_SIZE; inc++){

    Mod[0].Val = 0;
    for( j = 0;j< 0xc + Mod[0].Val ; j++){
         
          ModbusTcpRxBuf[j] = ModbusRXbuftest[inc][j];
    }

    if(ModbusTcpRxBuf[7] == 0x10){    
        Mod[0].v[1] = ModbusRXbuftest[inc][10];
        Mod[0].v[0] = ModbusRXbuftest[inc][11];
    for( j = 0;j<= 0xC + (Mod[0].Val*2); j++){
          ModbusTcpRxBuf[j] = ModbusRXbuftest[inc][j];
    }
    }



   processexpecteddata(ModbusTcpRxBuf,Test_TX,DataRegister);
   frame_function(&ModbusTcpRxBuf[0] ,&DataRegister[0], &parse , &ModbusTcpTxBuf[0],&ModbusTxLength);
   Test_ing(ModbusTcpTxBuf,Test_TX);

   
#ifdef test_ing
 
    printf(ANSI_COLOR_RESET "\nQuery Packet:%d", inc + 1);
    if (ModbusTcpTxBuf[7] > 0x80) {
        switch(ModbusTcpTxBuf[8]) {
            case 1:
                printf(ANSI_COLOR_ORANGE" - Function Error");
                break;
            case 2:
                printf(ANSI_COLOR_ORANGE " - Address Error");
                break;
            case 3:
                printf(ANSI_COLOR_ORANGE " - Data Error");
                break;
        }
    }
   
    printf(ANSI_COLOR_RESET "\n");
    for (int i = 0; i < 0xc + (Mod[0].Val * 2); i++)
        printf("%02X ", ModbusTcpRxBuf[i]);
    printf("\n");

    printf("Expected Response:\n");
    int responseLength = (ModbusTcpTxBuf[7] == 0x06) ? 0x0C : ((ModbusTcpTxBuf[7] < 0x80) ? 0x09 + ModbusTcpTxBuf[8] : 0x09);
    for (int i = 0; i < responseLength; i++)
        printf("%02X ", Test_TX[i]);
    printf("\n");

    printf("Number of packets: %d\n",ModbusTxLength);

    printf("Actual Response:\n");
    for (int i = 0; i < responseLength; i++)
        printf("%02X ", ModbusTcpTxBuf[i]);
    printf("\n");

    if (Test_Res == 1) {
        printf(ANSI_COLOR_GREEN "Test Passed");
    }
    else {
        printf(ANSI_COLOR_RED "Test failed\n");
    }
    printf(ANSI_COLOR_RESET); // Reset color to default
    if(ModbusTcpRxBuf[7] == 0x6 || ModbusTcpRxBuf[7] == 0x10) {
    if(test_c == 1){
           printf(ANSI_COLOR_RED" - Data not Entered");
        }
        else{
            printf(ANSI_COLOR_GREEN" - Data Entered"); 
        }
    }
    printf("\n");

#endif
    
}

}

unsigned short int processexpecteddata( unsigned char *ModbusTcpRxBuf,unsigned char *Test_TX,unsigned short int DataRegister[]){

for ( increment = 0; increment < 12; increment++) {
    Test_TX[increment] = ModbusTcpRxBuf[increment];
}

if(ModbusTcpRxBuf[7]==0x03){   
        Test_TX[8] = ModbusTcpRxBuf[11] * 2;
        Test_TX[5] = Test_TX[8] + 0x03;
 for (increment = 0; increment < ModbusTcpRxBuf[11]; increment++) {
        Test_TX[9 + increment * 2] = DataRegister[ModbusTcpRxBuf[9] + increment] / 0x100;   // High unsigned char
        Test_TX[10 + increment * 2] = DataRegister[ModbusTcpRxBuf[9] + increment] % 0x100; // Low unsigned char
    }
      
}
if(ModbusTcpRxBuf[7]!=0x03 && ModbusTcpRxBuf[7]!=0x06 && ModbusTcpRxBuf[7]!=0x10){
    error_1test(1);
}
else if(ModbusTcpRxBuf[9] > 0x19){
    error_1test(2);
}
if(ModbusTcpRxBuf[7] == 6){
    if(ModbusTcpRxBuf[10]>253 &&  ModbusTcpRxBuf[11]>232){
        error_1test(3);
    }
    
} 
if(ModbusTcpRxBuf[7] == 0x10){
   for ( increment = 0; increment < ModbusTcpRxBuf[11]*2; increment++) {
    if (ModbusTcpRxBuf[increment*2 + 13] > 253 && ModbusTcpRxBuf[increment*2 + 14] > 232) {
        error_1test(3);
    }
}

}       return 0;
} 




unsigned short int error_1test(ErrorCode error) {
        //testing
        Test_TX[5]  =  0x03;
        Test_TX[7]  =  0x80 + Test_TX[7];
        Test_TX[8]  =  error;
    return error; // Return error code or consider if another return type or handling is needed
}




//function for testing the output with the expected output
unsigned short int Test_ing(const unsigned char ModbusTcpTxBuf[], const unsigned char Test_TX[]) {
    WORD check[100];
    Test_Res = 1;
    test_c = 0;

    int max_iterations = (ModbusTcpTxBuf[7] < 0x80) ? (0x08 + ModbusTcpTxBuf[8]) : 0x09;
    
    if(ModbusTcpRxBuf[7] == 0x06){
        unsigned short int add = ModbusTcpRxBuf[8]*0x100 + ModbusTcpRxBuf[9];
        check[0] = ModbusTcpRxBuf[10]*0x100 + ModbusTcpRxBuf[11];
        //printf("%04x %04x ",DataRegister[add],check[0]);
        if(DataRegister[add] != check[0]){
            test_c = 1;
        }
    } 
 if(ModbusTcpRxBuf[7] == 0x10){
       int add = ModbusTcpRxBuf[8] * 0x100 + ModbusTcpRxBuf[9];
       for(increment = 0;increment< ModbusTcpRxBuf[10] * 0x100 + ModbusTcpRxBuf[11] ; increment++){
       check[increment] = ModbusTcpRxBuf[13 + increment * 2] * 0x100 + ModbusTcpRxBuf[14 +increment * 2];
       //printf("%04x %04x ",DataRegister[add+ increment],check[increment]);
       if(DataRegister[add+increment] != check[increment]){
           test_c = 1;
       }
       }
   } 


    for ( increment = 0; increment < max_iterations; increment++) {

        if (ModbusTcpTxBuf[increment] != Test_TX[increment]) {
            Test_Res = 0;
            break;
        }

    }

    return Test_Res;
}
