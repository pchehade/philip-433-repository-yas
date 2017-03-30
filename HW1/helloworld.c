#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro

// DEVCFG0
#pragma config DEBUG = 1 // no debugging,disabled
#pragma config JTAGEN = 0 // no jtag, disabled
#pragma config ICESEL = 11 // use PGED1 and PGEC1
#pragma config PWP = 111111111 // no write protect
#pragma config BWP = 1 // no boot write protect
#pragma config CP = 1 // no code protect

// DEVCFG1
#pragma config FNOSC = 011 // use primary oscillator with pll, 011 = Primary Oscillator (POSC) with PLL module (XT+PLL, HS+PLL, EC+PLL)
#pragma config FSOSCEN = 0 // turn off secondary oscillator, 0 = Disable Secondary Oscillator
#pragma config IESO = 0 // no switching clocks, 0 = Internal External Switchover mode is disabled (Two-Speed Start-up is disabled
#pragma config POSCMOD = 10 // high speed crystal mode, 10 = HS Oscillator mode is selected
#pragma config OSCIOFNC = 1 // disable secondary osc, 1 = CLKO output disabled
#pragma config FPBDIV = 00 // divide sysclk freq by 1 for peripheral bus clock, 00 = PBCLK is SYSCLK divided by 1
#pragma config FCKSM = 1 // do not enable clock switch, 1x = Clock switching is disabled, Fail-Safe Clock Monitor is disabled
#pragma config WDTPS = 10100 // use slowest wdt??
#pragma config WINDIS = 1 // wdt no window mode,1 = Watchdog Timer is in non-Window mode
#pragma config FWDTEN = 0 // wdt disabled, 0 = Watchdog Timer is not enabled; it can be enabled in software
#pragma config FWDTWINSZ = 11 // wdt window at 25%, 11 = Window size is 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = 001 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = 111 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = 001 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = 111 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB, 111 = 12x dividera
#pragma config UPLLEN = 0 // USB clock on

// DEVCFG3
#pragma config USERID = 0000000000000000 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = 0 // allow multiple reconfigurations. 0 = Allow multiple reconfigurations
#pragma config IOL1WAY = 0 // allow multiple reconfigurations, 0 = Allow multiple reconfigurations
#pragma config FUSBIDIO = 1 // USB pins controlled by USB module, 1 = USBID pin is controlled by the USB module
#pragma config FVBUSONIO = 1 // USB BUSON controlled by USB module. 1 = VBUSON pin is controlled by the USB module


int main() {
    // Output pins
    TRISBbits.TRISB4=1; //set pushbutton as input pin
    TRISAbits.TRISA4=0; //set LED as output
    __builtin_disable_interrupts();
    
    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    
    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;
    
    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;
    
    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    
    // do your TRIS and LAT commands here
    
    __builtin_enable_interrupts();
    
    while(1) {
        int time,stop;
        LATAbits.LATA4= 1;
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT()<12000) {
        }
        LATAbits.LATA4=0;
        time=_CP0_GET_COUNT();
        stop=time+12000;
        while (_CP0_GET_COUNT()<stop){
        }
        LATAbits.LATA4=0;
        
    }
    
}


