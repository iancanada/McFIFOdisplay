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

