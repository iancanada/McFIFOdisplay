#include "FifoMessage.hpp"

//constructor
CfifoMessage::CfifoMessage()   
{
  state=WAITINGHEAD;
  newPackageFlag=0;
  finishInitialFlag=0;
}

//receiving precess
void CfifoMessage::processReceiving(char ch)
{
  switch(state)
  {
    case WAITINGHEAD:
      if(ch=='@')                      //head received
      {
        receivingPackage.command=' ';  //empty command is initialed
        state=GETTINGCOMMAND;
      }
      break;
    case GETTINGCOMMAND:
      if(ch=='#')                      //recover from ending flag
        state=WAITINGHEAD;
      else if(ch=='$')                 //got command finishing flag
      {
        receivingPackage.valueStr="";  //initial as empty string
        state=GETTINGVALUE;
      }
      else                             //receiving command
        receivingPackage.command=ch;        
      break;
    case GETTINGVALUE:
      if(ch=='$')                      //recover from this flag
        state=WAITINGHEAD;
      else if(ch=='#')                 //got ending flag
      {
        receivedPackage=receivingPackage;
        newPackageFlag=1;
        state=WAITINGHEAD;
      }
      else                             //receiving value string
        receivingPackage.valueStr+=ch;
      break;
    default:
      state=WAITINGHEAD;
      break;
  }
} 
  
//2017-02-01 normalize string length to len, cut or fill in space
String normalizeStrLen(String str,int len)
{
  int i;
  int strLength=str.length();
  if(strLength>len)            //cut str if greater
    str.remove(len);
  else if(strLength<len)       //add " " if shorter
  {
    for(i=0;i<(len-strLength);i++)
      str+=" ";
  }
  return str;
}

