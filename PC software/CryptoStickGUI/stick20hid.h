/*
* Author: Copyright (C) Rudolf Boeddeker  Date: 2013-08-12
*
* This file is part of GPF Crypto Stick 2
*
* GPF Crypto Stick 2  is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* GPF Crypto Stick is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with GPF Crypto Stick. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HID_STICK_20_H

#define HID_STICK_20_H




#ifdef __cplusplus
extern "C" {
#endif

// Offset of status block
#define OUTPUT_CMD_RESULT_STICK20_STATUS_START  20

// Status block
typedef struct {
  unsigned char  CommandCounter_u8;
  unsigned char  LastCommand_u8;
  unsigned char  Status_u8;
  unsigned char  ProgressBarValue_u8;
} HID_Stick20Status_est;




#define OUTPUT_CMD_RESULT_STICK20_DATA_START        25


/** Only for debugging */

#define STICK20_DEBUG_TEXT_LEN          600000

extern char DebugText_Stick20[STICK20_DEBUG_TEXT_LEN];
extern unsigned long DebugTextlen_Stick20;
extern char DebugTextHasChanged;
extern int DebugingActive;
extern int DebugingStick20PoolingActive;

void DebugClearText (void);
void DebugAppendText (char *Text);


/** Only for debugging - End */

#define OUTPUT_CMD_STICK20_SEND_DATA_TYPE_NONE        0
#define OUTPUT_CMD_STICK20_SEND_DATA_TYPE_DEBUG       1
#define OUTPUT_CMD_STICK20_SEND_DATA_TYPE_PW_DATA     2
#define OUTPUT_CMD_STICK20_SEND_DATA_TYPE_STATUS      3
#define OUTPUT_CMD_STICK20_SEND_DATA_TYPE_PROD_INFO   4


#define OUTPUT_CMD_STICK20_SEND_DATA_SIZE            25

typedef struct {
  unsigned char  SendCounter_u8;
  unsigned char  SendDataType_u8;
  unsigned char  FollowBytesFlag_u8;
  unsigned char  SendSize_u8;
  unsigned char  SendData_u8[OUTPUT_CMD_STICK20_SEND_DATA_SIZE];
} HID_Stick20SendData_est;

extern HID_Stick20SendData_est HID_Stick20ReceiveData_st;



#define STICK20_PASSWORD_MATRIX_DATA_LEN 100

#define STICK20_PASSWORD_MATRIX_STATUS_IDLE                 0
#define STICK20_PASSWORD_MATRIX_STATUS_GET_NEW_BLOCK        1
#define STICK20_PASSWORD_MATRIX_STATUS_NEW_BLOCK_RECEIVED   2

typedef struct {
  unsigned char  StatusFlag_u8;
           char  PasswordMatrix_u8[STICK20_PASSWORD_MATRIX_DATA_LEN];
} HID_Stick20MatrixPasswordData_est;

extern HID_Stick20MatrixPasswordData_est HID_Stick20MatrixPasswordData_st;


/* Stick 20 configuration data */

#define READ_WRITE_ACTIVE             0
#define READ_ONLY_ACTIVE              1

#define SD_UNCRYPTED_VOLUME_BIT_PLACE   0
#define SD_CRYPTED_VOLUME_BIT_PLACE     1
#define SD_HIDDEN_VOLUME_BIT_PLACE      2


typedef struct {
  unsigned short  MagicNumber_StickConfig_u16;          // Shows that the structure is valid                  2 byte
  unsigned char   ReadWriteFlagUncryptedVolume_u8;      // Flag stores the read/write flag in the CPU flash   1 byte
  unsigned char   ReadWriteFlagCryptedVolume_u8;        // Flag stores the read/write flag in the CPU flash   1 byte
  unsigned char   VersionInfo_au8[4];                   //                                                    4 byte
  unsigned char   ReadWriteFlagHiddenVolume_u8;         // Flag stores the read/write flag in the CPU flash   1 byte
  unsigned char   FirmwareLocked_u8;                    //                                                    1 byte
  unsigned char   NewSDCardFound_u8;                    // Bit 0 new card found, bit 1-7 change counter       1 byte
  unsigned char   SDFillWithRandomChars_u8;             // Bit 0 new card found, bit 1-7 change counter       1 byte
  unsigned long   ActiveSD_CardID_u32;                  // Not used                                           4 byte
  unsigned char   VolumeActiceFlag_u8;                  // Bit 0 new card found, bit 1-7 change counter       1 byte
  unsigned char   NewSmartCardFound_u8;                 // Bit 0 new card found, bit 1-7 change counter       1 byte  // 20 Byte not packed
  unsigned char   UserPwRetryCount;                     // User password retry count                          1 byte
  unsigned char   AdminPwRetryCount;                    // Admin password retry count                         1 byte
  unsigned long   ActiveSmartCardID_u32;                //                                                    4 byte
  unsigned char   StickKeysNotInitiated;                // No AES keys computed (1 = AES are builded)         1 byte  // 25 Byte not packed
} typeStick20Configuration_st;                                                          // Sum   25 byte


extern int Stick20_ConfigurationChanged;
extern typeStick20Configuration_st HID_Stick20Configuration_st;



/* Look for 4 byte alignment of 32 bit values */
typedef struct {
  unsigned char  FirmwareVersion_au8[4];               //                                                    4 byte  //  4
  unsigned long  CPU_CardID_u32;                       //                                                    4 byte  //  8
  unsigned long  SmartCardID_u32;                      //                                                    4 byte  // 12
  unsigned long  SD_CardID_u32;                        //                                                    4 byte  // 16
  unsigned char  SC_UserPwRetryCount;                  // User password retry count                          1 byte  // 17
  unsigned char  SC_AdminPwRetryCount;                 // Admin password retry count                         1 byte  // 18
  unsigned char  SD_Card_ManufacturingYear_u8;         //                                                    1 byte  // 19
  unsigned char  SD_Card_ManufacturingMonth_u8;        //                                                    1 byte  // 20
  unsigned short SD_Card_OEM_u16;                      //                                                    2 byte  // 22
  unsigned short SD_WriteSpeed_u16;                    // in kbyte / sec                                     2 byte  // 24
  unsigned char  SD_Card_Manufacturer_u8;              //                                                    1 byte  // 25
} typeStick20ProductionInfos_st;                                                          // Sum   25 byte (Max 25 Byte) // not packed

extern int Stick20_ProductionInfosChanged;
extern typeStick20ProductionInfos_st Stick20ProductionInfos_st;



void HID_Stick20Init (void);

int HID_GetStick20Configuration (void);
int HID_GetStick20PasswordMatrixData (void);
int HID_GetStick20DebugData (void);
int HID_GetStick20ReceiveData (unsigned char *data);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // HID_STICK_20_H
