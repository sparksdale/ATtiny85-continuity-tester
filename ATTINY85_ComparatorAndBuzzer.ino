#include<avr/io.h>
#include<avr/sleep.h>
#include<avr/power.h>

#define LED_PIN PB2
#define BUZZER_PIN PB4
//const unsigned long Timeout = (unsigned long)60*1000; //60,000ms or 60 seconds
//volatile unsigned long Time; //Declared as volatile because we want to read the Time value from RAM everytime it is called upon rather

//Interrupt Service Routine - Resets timer each time probe is activated
/* ISR(PCINT0_vect){
  Time = millis();

} */

void beep(){
  TCCR1 |= 3; //Set CS10 and CS11 bits
}

void noBeep(){
  TCCR1 &= ~3; //Clear CS10 and CS11 bits
}

void setup() {
  DDRB |= (1<<LED_PIN) | (1<<BUZZER_PIN); //Data Direction Register B = Setting LED & BUZZER pins as OUTPUTS
  DDRB &= ~((1 << PB0 ) | (1 << PB1)); // Set PB0 and PB1 as INPUTS

  PORTB |= ((1 << PB0) | (1 << PB1)); // Enable internal pull-up resistors for input pins

  //By disabling Analog Comparator MUX, we set AIN1 as our (-) input for our analog comparator
  //ADCSRB &= ~(1 << ACME); //Disabling Analog Comparator MUX
  ADCSRA = 0x00;
  ADCSRB = 0x00;

  TCCR1 = (1 << CTC1) | (0 << COM1A0) | (0 << CS10); // Timer/Counter1 Control Register -> Set Clear Timer/Counter on Compare Match 
  //AKA Reset timer once desired value is hit 
  //We're also explicitly turning off the output by clearing COM1A0 and CS10
  GTCCR |= (1 << COM1B0); //General Timer/Counter1 Control Register-> Set Comparator B output Mode
  //AKA Enable output to pin from timer toggle
  OCR1C = 119;

  //Set MCU into Power-Down mode by setting MCUCR register SM1 & SM0 bits to 1 0
  /* MCUCR |= (1 << SM1);
  MCUCR &= ~(1 << SM0);

  PCMSK |= (1 << PCINT0); //Change interrupt pin to physical pin 5 aka our + comparator input
 
  GIMSK |= (1 << PCIE);  //Enable pin change interrput

  //Power Saving
  ADCSRA &= ~(1 << ADEN); //Disable ADC
  PRR = (1 << PRUSI) | (1 << PRADC); //Disabling Power Reduction USI and ADC Clocks

  Time = millis();
 */
}

/* void sleep_check(){
  if(millis() - Time > Timeout){
    MCUCR |= (1 << SE); //Enable sleep
    sleep_cpu(); //Executes sleep instruction
    
    //Program resumes here
    MCUCR &= ~(1 << SE);
  }

 
} */

void loop() {
  // put your main code here, to run repeatedly:

    bool comp_out = (ACSR & (1 << ACO)); //Reading comparator output ACO

      if(comp_out == 1){
        PORTB |= (1<<LED_PIN); //Drive PB2 HIGH aka Turn on LED
        beep();
      }
      else{
        PORTB &= ~(1<<LED_PIN); //Drive PB2 LOW aka Turn off LED
        noBeep();
      }
  
   // sleep_check();
}
