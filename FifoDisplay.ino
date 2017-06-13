#include <LiquidCrystal.h>
#include "FifoMessage.hpp"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // select the pins used on the LCD panel on DFR0009
CfifoMessage fifoMessage;
package_t package;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           // start serial port
  lcd.begin(16, 2);              // start16*2 LCD
  lcd.setCursor(0,0);lcd.print("Ian I2S/DSD FIFO");
  lcd.setCursor(0,1);lcd.print("    DISPLAY     ");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(fifoMessage.getNewPackageFlag())                     //there is new package received
  {
    package=fifoMessage.getPackage();
    /*if(!fifoMessage.getFinishInitialFlag())              //it's first time receiving a package
    {
      lcd.setCursor(0,0);lcd.print("                ");   //clear screen
      lcd.setCursor(0,1);lcd.print("                ");
      fifoMessage.setFinishInitialFlag();                 //set the flag
    }*/
    //Serial.println(package.command);
    //Serial.println(package.valueStr);
  
    switch(package.command)
    {
      case UNLOCK:     lcd.setCursor(0,0);lcd.print("UN-LOCK    EMPTY");break;
      case NOSIGNAL:   lcd.setCursor(0,0);lcd.print("NO SIGNAL  EMPTY");break; 
      case WRONGSIGNAL:lcd.setCursor(0,0);lcd.print("UN LOCK    EMPTY");break;
      case I2S:        lcd.setCursor(0,0);lcd.print("I2S ");
                       lcd.print(normalizeStrLen(package.valueStr,8));break; 
      case DSD:        lcd.setCursor(0,0);lcd.print("DSD ");
                       lcd.print(normalizeStrLen(package.valueStr,8));break;
      case DELAYTIME:  lcd.setCursor(12,0);//lcd.print("t");
                       package.valueStr.remove(4);lcd.print(package.valueStr);break;    
      case XONUMBER:   lcd.setCursor(0,1);lcd.print("XO");
                       package.valueStr.remove(2);lcd.print(package.valueStr);break;  
      case MASTER:     lcd.setCursor(14,1);lcd.print("  ");break;            //'MA' master mode is default, so no need to display
      case SLAVE:      lcd.setCursor(14,1);lcd.print("SL");break; 
      case FMCK:       lcd.setCursor(4,1);package.valueStr.remove(10);lcd.print(package.valueStr);break;
      case CLEAR:      if(package.valueStr.charAt(0)=='0')                   //clear one line on lcd
                       {
                         lcd.setCursor(0,0);lcd.print("                ");   //clear screen line1
                       }
                       else if(package.valueStr.charAt(0)=='1')
                       {
                         lcd.setCursor(0,1);lcd.print("                ");   //clear screen line2
                       }                         
                       break;
      default:         break;                         
    }
  }
}

void serialEvent()
{
  while(Serial.available())
  {
    if(fifoMessage.getNewPackageFlag()==0)   //any possible package was processed
      fifoMessage.processReceiving((char)Serial.read());    
  }  
}
