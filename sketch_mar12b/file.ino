// IBridge lite and Nokia 5110 LCD part
#include <avr/pgmspace.h>
#include "font.h"
extern unsigned char font6_8[92][6];

int IBridge_Column_Pin0 = 5;
int IBridge_Column_Pin1 = 6;
int IBridge_Column_Pin2 = 7;
//int IBridge_Column_Pin3 = 4;

//int IBridge_Row_Pin0 = 2;
int IBridge_Row_Pin1 = 3;
int IBridge_Row_Pin2 = 4;
//int IBridge_Row_Pin3 = 19;

int IBridge_LCD5110_SCK_PIN = 8;
int IBridge_LCD5110_MO_PIN = 9;
int IBridge_LCD5110_DC_PIN = 10;
int IBridge_LCD5110_RST_PIN = 11;
int IBridge_LCD5110_CS_PIN = 12;

//Define the LCD Operation function
void IBridge_LCD5110_LCD_write_byte(unsigned char dat,unsigned char IBridge_LCD5110_Mode);


//Define the hardware operation function
void IBridge_GPIO_Config(void);
void IBridge_LCD5110_SCK(unsigned char temp);
void IBridge_LCD5110_MO(unsigned char temp);
void IBridge_LCD5110_CS(unsigned char temp);
void IBridge_LCD5110_RST(unsigned char temp);
void IBridge_LCD5110_DC(unsigned char temp);

void IBridge_init()
{
  IBridge_GPIO_Config();

  IBridge_LCD5110_DC(1);//LCD_DC = 1;
  IBridge_LCD5110_MO(1);//SPI_MO = 1;
  IBridge_LCD5110_SCK(1);//SPI_SCK = 1;
  IBridge_LCD5110_CS(1);//SPI_CS = 1;
  
  IBridge_LCD5110_RST(0);//LCD_RST = 0;
  delay(10);
  IBridge_LCD5110_RST(1);//LCD_RST = 1;

  IBridge_LCD5110_LCD_write_byte(0x21,0);
  IBridge_LCD5110_LCD_write_byte(0xc6,0);
  IBridge_LCD5110_LCD_write_byte(0x06,0);
  IBridge_LCD5110_LCD_write_byte(0x13,0);
  IBridge_LCD5110_LCD_write_byte(0x20,0);
  IBridge_LCD5110_clear();
  IBridge_LCD5110_LCD_write_byte(0x0c,0);
}

void IBridge_LCD5110_LCD_write_byte(unsigned char dat,unsigned char mode)
{
  unsigned char i;

  IBridge_LCD5110_CS(0);//SPI_CS = 0;

  if (0 == mode)
    IBridge_LCD5110_DC(0);//LCD_DC = 0;
  else
    IBridge_LCD5110_DC(1);//LCD_DC = 1;

  for(i=0;i<8;i++)
  {
    IBridge_LCD5110_MO(dat & 0x80);//SPI_MO = dat & 0x80;
    dat = dat<<1;
    IBridge_LCD5110_SCK(0);//SPI_SCK = 0;
    IBridge_LCD5110_SCK(1);//SPI_SCK = 1;
  }

  IBridge_LCD5110_CS(1);//SPI_CS = 1;

}

void IBridge_LCD5110_write_char(unsigned char c)
{
  unsigned char line;
  unsigned char ch = 0;

  c = c - 32;

  for(line=0;line<6;line++)
  {
    ch = pgm_read_byte(&(font6_8[c][line]));
    IBridge_LCD5110_LCD_write_byte(ch,1);
    
  }
}
void IBridge_LCD5110_write_char_reg(unsigned char c)
{
  unsigned char line;
  unsigned char ch = 0;

  c = c - 32;

  for(line=0;line<6;line++)
  {
    ch = ~(pgm_read_byte(&(font6_8[c][line])));
    IBridge_LCD5110_LCD_write_byte(ch,1);
    
  }
}

void IBridge_LCD5110_write_string(char *s)
{
  unsigned char ch;
    while(*s!='\0')
  {
    ch = *s;
    IBridge_LCD5110_write_char(ch);
    s++;
  }
}


void IBridge_LCD5110_clear()
{
  unsigned char i,j;
  for(i=0;i<6;i++)
    for(j=0;j<84;j++)
      IBridge_LCD5110_LCD_write_byte(0,1);
}

void IBridge_LCD5110_set_XY(unsigned char X,unsigned char Y)
{
  unsigned char x;
  x = 6*X;
  //y = 8*Y;

  IBridge_LCD5110_LCD_write_byte(0x40|Y,0);
  IBridge_LCD5110_LCD_write_byte(0x80|x,0);
}

void IBridge_LCD5110_Write_Dec(unsigned int b)
{
  unsigned char datas[3];

  datas[0] = b/1000;
  b = b - datas[0]*1000;
  datas[1] = b/100;
  b = b - datas[1]*100;
  datas[2] = b/10;
  b = b - datas[2]*10;
  datas[3] = b;

  datas[0]+=48;
  datas[1]+=48;
  datas[2]+=48;
  datas[3]+=48;

  IBridge_LCD5110_write_char(datas[0]);
  IBridge_LCD5110_write_char(datas[1]);
  IBridge_LCD5110_write_char(datas[2]);
  IBridge_LCD5110_write_char(datas[3]);

  
}

void IBridge_GPIO_Config()
{
  pinMode(IBridge_LCD5110_SCK_PIN, OUTPUT);
  pinMode(IBridge_LCD5110_MO_PIN, OUTPUT);
  pinMode(IBridge_LCD5110_DC_PIN, OUTPUT);
  pinMode(IBridge_LCD5110_RST_PIN, OUTPUT);
  pinMode(IBridge_LCD5110_CS_PIN, OUTPUT);
  
  pinMode(IBridge_Column_Pin0, OUTPUT);
  pinMode(IBridge_Column_Pin1, OUTPUT);
  pinMode(IBridge_Column_Pin2, OUTPUT);
  //pinMode(IBridge_Column_Pin3, OUTPUT);

  //pinMode(IBridge_Row_Pin0, INPUT);
  pinMode(IBridge_Row_Pin1, INPUT);
  pinMode(IBridge_Row_Pin2, INPUT);
  //pinMode(IBridge_Row_Pin3, INPUT);
}

void IBridge_LCD5110_CS(unsigned char temp)
{
  if (temp) digitalWrite(IBridge_LCD5110_CS_PIN, HIGH);
  else digitalWrite(IBridge_LCD5110_CS_PIN, LOW);
}

void IBridge_LCD5110_RST(unsigned char temp)
{
  if (temp) digitalWrite(IBridge_LCD5110_RST_PIN, HIGH);
  else digitalWrite(IBridge_LCD5110_RST_PIN, LOW);
}

void IBridge_LCD5110_DC(unsigned char temp)
{
  if (temp) digitalWrite(IBridge_LCD5110_DC_PIN, HIGH);
  else digitalWrite(IBridge_LCD5110_DC_PIN, LOW);
}

void IBridge_LCD5110_MO(unsigned char temp)
{
  if (temp) digitalWrite(IBridge_LCD5110_MO_PIN, HIGH);
  else digitalWrite(IBridge_LCD5110_MO_PIN, LOW);
}

void IBridge_LCD5110_SCK(unsigned char temp)
{
  if (temp) digitalWrite(IBridge_LCD5110_SCK_PIN, HIGH);
  else digitalWrite(IBridge_LCD5110_SCK_PIN, LOW);
}

unsigned char IBridge_Read_Key()
{
  //unsigned char i = 10;

  //Column 0 scan

  digitalWrite(IBridge_Column_Pin0, HIGH);  
  digitalWrite(IBridge_Column_Pin1, LOW);
  digitalWrite(IBridge_Column_Pin2, LOW);
  //digitalWrite(IBridge_Column_Pin3, LOW);

 
  //i=10;
  //while(i--);
  delay(1);

  //if((digitalRead(IBridge_Row_Pin0)) &&
  //  !(digitalRead(IBridge_Row_Pin1))  &&
  if((digitalRead(IBridge_Row_Pin1)) && !(digitalRead(IBridge_Row_Pin2))) return (1);
  if(!(digitalRead(IBridge_Row_Pin1)) && (digitalRead(IBridge_Row_Pin2))) return (2);
  digitalWrite(IBridge_Column_Pin0, LOW);
  digitalWrite(IBridge_Column_Pin1, HIGH);
  digitalWrite(IBridge_Column_Pin2, LOW);
  //digitalWrite(IBridge_Column_Pin3, LOW);

  //i=10;
  //while(i--);
  delay(1);

  //if((digitalRead(IBridge_Row_Pin0)) &&
  //  !(digitalRead(IBridge_Row_Pin1))  &&
  if((digitalRead(IBridge_Row_Pin1)) &&  
    !(digitalRead(IBridge_Row_Pin2)))
    //!(digitalRead(IBridge_Row_Pin2))  &&
    //!(digitalRead(IBridge_Row_Pin3)))
    //return (5);
    //return (4);
    return (3);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //    (digitalRead(IBridge_Row_Pin1))  &&
  if(!(digitalRead(IBridge_Row_Pin1)) &&    
      (digitalRead(IBridge_Row_Pin2)))
     //!(digitalRead(IBridge_Row_Pin2))  &&
     //!(digitalRead(IBridge_Row_Pin3)))
    //return (6);
    //return (5);
    return (4);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //   !(digitalRead(IBridge_Row_Pin1))  &&
  //    (digitalRead(IBridge_Row_Pin2)))
  //   // (digitalRead(IBridge_Row_Pin2))  &&
  //   //!(digitalRead(IBridge_Row_Pin3)))
  //  //return (7);
  //  return (6);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //   !(digitalRead(IBridge_Row_Pin1))  &&
  //   !(digitalRead(IBridge_Row_Pin2))  &&
  //    (digitalRead(IBridge_Row_Pin3)))
  //  return (8);

  //Column 3 Scan

  digitalWrite(IBridge_Column_Pin0, LOW);
  digitalWrite(IBridge_Column_Pin1, LOW);
  digitalWrite(IBridge_Column_Pin2, HIGH);
  //digitalWrite(IBridge_Column_Pin3, LOW);

  //i=10;
  //while(i--);
  delay(1);

  //if((digitalRead(IBridge_Row_Pin0)) &&
  //  !(digitalRead(IBridge_Row_Pin1))  &&
  if((digitalRead(IBridge_Row_Pin1)) &&  
    !(digitalRead(IBridge_Row_Pin2)))
    //!(digitalRead(IBridge_Row_Pin2))  &&
    //!(digitalRead(IBridge_Row_Pin3)))
    //return (9);
    //return (7);
    return (5);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //    (digitalRead(IBridge_Row_Pin1))  &&
  if(!(digitalRead(IBridge_Row_Pin1)) &&    
      (digitalRead(IBridge_Row_Pin2)))
     //!(digitalRead(IBridge_Row_Pin2))  &&
     //!(digitalRead(IBridge_Row_Pin3)))
    //return (10);
    //return (8);
    return (6);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //   !(digitalRead(IBridge_Row_Pin1))  &&
  //    (digitalRead(IBridge_Row_Pin2)))
  //   // (digitalRead(IBridge_Row_Pin2))  &&
  //   //!(digitalRead(IBridge_Row_Pin3)))
  //  //return (11);
  //  return (9);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //   !(digitalRead(IBridge_Row_Pin1))  &&
  //   !(digitalRead(IBridge_Row_Pin2))  &&
  //    (digitalRead(IBridge_Row_Pin3)))
  //  return (12);

  //Column 4 Scan

  //digitalWrite(IBridge_Column_Pin0, LOW);
  //digitalWrite(IBridge_Column_Pin1, LOW);
  //digitalWrite(IBridge_Column_Pin2, LOW);
  //digitalWrite(IBridge_Column_Pin3, HIGH);


  //delay(1);

  //if((digitalRead(IBridge_Row_Pin0)) &&
  //  !(digitalRead(IBridge_Row_Pin1))  &&
  //  !(digitalRead(IBridge_Row_Pin2))  &&
  //  !(digitalRead(IBridge_Row_Pin3)))
  //  return (13);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //    (digitalRead(IBridge_Row_Pin1))  &&
  //   !(digitalRead(IBridge_Row_Pin2))  &&
  //   !(digitalRead(IBridge_Row_Pin3)))
  //  return (14);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //   !(digitalRead(IBridge_Row_Pin1))  &&
  //    (digitalRead(IBridge_Row_Pin2))  &&
  //   !(digitalRead(IBridge_Row_Pin3)))
  //  return (15);

  //if(!(digitalRead(IBridge_Row_Pin0)) &&
  //   !(digitalRead(IBridge_Row_Pin1))  &&
  //   !(digitalRead(IBridge_Row_Pin2))  &&
  //    (digitalRead(IBridge_Row_Pin3)))
  //  return (16);

  return(0);

}

unsigned char IBridge_Read_Key_debounce()
{
  unsigned char temp = 0;
  unsigned char key = 0;
  int count = 0;
  
  while(count >= 0)
  {
    temp = IBridge_Read_Key();
    if((temp > 0) && (temp < 10))
    {
      if(count == 2)
      {
        if(key == temp)
        {
          break;
        }
        else
        {
          key = 0;
          break; 
        }    
      } 
      else if(count > 0)
      {
        if(key != temp)
        {
          key = 0;
          break; 
        }        
      }
      else
      {
        key = temp;
      }
    }  
    else
    {
      break;
    }  
    
    count++;
    delay(200);
  }
  
  return key;
}

// BT Shield part
unsigned int timeout=0;
unsigned char state=0;

int inByte = 0;         // incoming serial byte
//int cntByte = 0;        // number of incoming serial byte

//unsigned char RxData[50];
//int RxDataLength = 0;
unsigned char RxData;

ISR(TIMER2_OVF_vect) //Timer2 Service
{
  TCNT2 = 0;
  timeout++;
  if (timeout>61)
  {
    state=1;
    timeout=0;
  }
}

void init_timer2(void)
{
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  TCCR2B |= 0x07; // by clk/1024
  ASSR |= (0<<AS2); // Use internal clock - external clock not used in Arduino
  TIMSK2 |= 0x01; //Timer2 Overflow Interrupt Enable
  TCNT2 = 0;
  sei();
}

void cleantime()
{
  timeout=0;
  state=0;
}

void BT_init()
{
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(13,OUTPUT);
  //attachInterrupt(0,cleantime,FALLING);
  detachInterrupt(0);
  //init_timer2();  
}

void setup()
{
  unsigned char X;
  unsigned char Y;
  
  IBridge_init();
  BT_init();
  
  X = 4;
  Y = 2;
  IBridge_LCD5110_set_XY(X,Y);
  
  IBridge_LCD5110_write_string("Funchip");
  //delay(1000);
  delay(5000);
  IBridge_LCD5110_clear();
  
  X = 0;
  Y = 0;
  IBridge_LCD5110_set_XY(X,Y);   
}

void loop()
{
  unsigned char temp = 0;
  while(1)
  {
    // IBridge lite and Nokia 5110 LCD part
    //temp = IBridge_Read_Key();
    temp = IBridge_Read_Key_debounce();
    
    switch (temp)
    {
      case 0:
        //IBridge_LCD5110_write_char('0');
        break;
        case 1:
        IBridge_LCD5110_write_char('0');
        break;
      case 2:
        IBridge_LCD5110_write_char('1');
        break;
      case 3:
        IBridge_LCD5110_write_char('2');
        break;
      case 4:
        IBridge_LCD5110_write_char('3');
        break;
      case 5:
        IBridge_LCD5110_write_char('4');
        break;
      case 6:
        IBridge_LCD5110_write_char('5');
        break;
      case 7:
        IBridge_LCD5110_write_char('6');
        break;
      case 8:
        IBridge_LCD5110_write_char('7');
        break;
      case 9:
        IBridge_LCD5110_write_char('8');
        break;
      case 10:
        IBridge_LCD5110_write_char('9');
        break;
      case 11:
        IBridge_LCD5110_write_char('A');
        break;
      case 12:
        IBridge_LCD5110_write_char('B');
        break;
      case 13:
        IBridge_LCD5110_write_char('C');
        break;
      case 14:
        IBridge_LCD5110_write_char('D');
        break;
      case 15:
        IBridge_LCD5110_write_char('E');
        break;
      case 16:
        IBridge_LCD5110_write_char('F');
        break;

      default:
        break;
    }
      temp = 0;
      
    // BT Shield part  
    switch(state)
    {
      case 0:
          digitalWrite(13,LOW);
          break;
      case 1:
          digitalWrite(13,HIGH);
          //IBridge_LCD5110_write_string("Hellow BT ! ");
          //Serial.print("Hellow BT ! ");
          break;
    }      
    
    if (Serial.available() > 0) 
    {
      //cntByte = Serial.available();     
      
      // get incoming byte:
      inByte = Serial.read();    
      //RxData[0] = char(inByte);
      //IBridge_LCD5110_write_char(RxData[0]);
      //Serial.write(RxData[0]);
      RxData = char(inByte);
      IBridge_LCD5110_write_char(RxData);
      Serial.write(RxData);      
    }
    
  }
}
