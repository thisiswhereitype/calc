#include "mbed.h"
#include "rtos.h"
#include "C12832.h"
#include "Keypad.h"
#include "NodeTest.hpp"

C12832 lcd(p5, p7, p6, p8, p11);
Serial        PC(USBTX, USBRX);
RtosTimer    *LedTimer;
DigitalOut    Led1(LED1);
DigitalOut    Led2(LED2);
DigitalOut  Led3 (LED3);

void addCharacter(char a);

// Define your own keypad values
char Keytable[] = {
    '=', '0', '+', 'd', // r0
    '1', '3', '-', '2', // r1
    '*', '8', '7', '9', // r2
    '/', '5', '4', '6'  // r3
  // c0   c1   c2   c3
 };

char InputBuffer[20];
int BufferIndex;

int32_t       Index = -1;
int           State;

uint32_t cbAfterInput(uint32_t _index)
{
    Led3 = !Led3;
    Index = _index;
    return 0;
}

void Blink(void const *arg) {
    if (State == 1)  {
        Led1 = 1;
        Led2 = 0;
        State = 2;
    }
    else if (State == 2)  {
        LedTimer->stop();
        Led1 = 0;
        Led2 = 1;
        LedTimer->start(2000); // longer timer alarm
        State = 1;
    }
}
void flushBuffer()
{
    BufferIndex=0;
    for(int i=0; i< sizeof(InputBuffer)/sizeof(InputBuffer[0]); i++)
        InputBuffer[i]= '\0';
}

int main()
{
    lcd.cls();
    lcd.printf("I'm a Demo Keypad\r\n");
    State = 1;
    LedTimer = new RtosTimer(&Blink, osTimerPeriodic, NULL);
    LedTimer->start(500); // short timer alarm
    flushBuffer();
    //            r0   r1   r2   r3   c0   c1   c2   c3
    Keypad keypad(p25, p26, p27, p28, p21, p22, p23, p24);
    keypad.attach(&cbAfterInput);
    keypad.start();  // energize the columns c0-c3 of the keypad

    while (1) {
        __wfi();
        if (Index > -1) {
            addCharacter(Keytable[Index]);
            if(Keytable[Index] != '=')
            {
                lcd.cls();
                lcd.locate(0,0);
                lcd.printf("%s", InputBuffer);
            }
            Index = -1;
        }
    }
}

void addCharacter(char a)
{
    switch(a)
    {
        case 'd':
            if(BufferIndex >= 0)
              InputBuffer[BufferIndex--] = '\0';
              if(BufferIndex < 0) BufferIndex =0;
          break;
        default:
            if(BufferIndex <= 19)
                InputBuffer[BufferIndex++] = a;
            break;
        case '=':
            lcd.cls();
            lcd.locate(0,0);
            lcd.printf("%d", CharEvaluator(InputBuffer, BufferIndex));
            flushBuffer();

//            myItoa(CharEvaluator(InputBuffer, BufferIndex+1), InputBuffer, 10);
//            for(int i=0; i<=19; i++)
//                if(InputBuffer[i] == '\0')
//                {
//                    BufferIndex = i;
//                    break;
//                }
            break;
    }
}
