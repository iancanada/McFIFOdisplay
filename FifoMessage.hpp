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


