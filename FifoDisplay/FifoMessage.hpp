/**
  **************************************************************************************
  * File Name          : FifoMessage.cpp
  * Date of create     : 2017-06-10
  * Author             : Ian Jin  
  *                    : iancanada.mail@gmail.com
  *                    : Twitter: @iancanadaTT
  *                    
  * Description        : Open source Arduino based McFIFO display project
  * 
  * This program is a free software: you can redistribute it and/or modify it
  * under the terms of the GNU Lesser General Public License as published by the
  * Free Software Foundation, either version 3 of the License, or any later
  * version.
  *
  * This program is distributed in the hope that it will be useful, but WITHOUT
  * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
  * for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.        
  * **************************************************************************************
  * COPYRIGHT(c) Ian Jin All rights reserved
  */

#ifndef FIFOMESSAGE_H_
#define FIFOMESSAGE_H_
#include <arduino.h>

typedef struct
{
  char command;
  String valueStr;
}package_t;

class CfifoMessage
{
  enum{
    WAITINGHEAD=0,
    GETTINGCOMMAND,
    GETTINGVALUE 
  } state;
  int finishInitialFlag;           //set when receiv first package to indicate in working mode and to clear screen
  package_t receivingPackage,receivedPackage;
  int newPackageFlag;
public:
  CfifoMessage();                   //constructor
  void processReceiving(char ch);   //receiving
  int getNewPackageFlag(){return newPackageFlag;};
  int getFinishInitialFlag(){return finishInitialFlag;};
  void setFinishInitialFlag(){finishInitialFlag=1;};
  package_t getPackage(){newPackageFlag=0;return receivedPackage;}   
};

//commands list
#define UNLOCK      '0'
#define NOSIGNAL    '1'
#define WRONGSIGNAL '2'
#define I2S         '3'
#define DSD         '4'
#define DELAYTIME   '5'
#define XONUMBER    '6'
#define MASTER      '7'
#define SLAVE       '8'
#define FMCK        '9'
#define CLEAR       'a'

//functions
String normalizeStrLen(String str,int len);

#endif  //FIFOMESSAGE_H_


