/*
  ARDUINO BLINKY WORKSHOP
  Made for BYUI Hackathon
  10/22/2025
  Jared Wightman
*/


// Define our pin names and our global variable
#define Button_Pin 2 // This will swap every case of "Button_Pin" in the code for "2", the actual pin number
#define LED_Pin 7
volatile bool running_mode = true; // "volatile" is important for variables changed in interrupts

// Native code setup function, runs once at start
void setup() { 

  pinMode(Button_Pin, INPUT); // Declare pin type INPUT
  pinMode(LED_Pin, OUTPUT); // Declare pin type OUTPUT
  attachInterrupt(digitalPinToInterrupt(Button_Pin), button_interrupt, FALLING); // Declare button pin an "interrupt", link to its function, and choose sampling type (falling-edge)
  Serial.begin(9600); // Declare the serial baud rate (so we can use print() with the serial monitor)

  LED_do_nothing(); // Start our first function - one time use
}

// Native code run function, run repeatedly (like a "while" loop)
void loop() { 
  /*
    Nothing in here for this workshop.
  */
}

// This function is called every time our interrupt is tripped; pauses all other code until task is complete
void button_interrupt() { 

  Serial.print("Button press detected.\n");
  running_mode = false; // Resets global variable which causes functions to exit their loops
}


void LED_do_nothing() {

  Serial.print("LED off.\n");
  digitalWrite(LED_Pin, LOW); // Set LED pin to low, turning LED off.
  while (running_mode)
  {
    delay(100); // delay() function makes program wait for time in milliseconds
  }
  running_mode = true; // Set global variable to run loops inside functions
  LED_blink(); // Call the next function in the chain
}


void LED_blink() {

  Serial.print("LED blinking.\n");
  digitalWrite(LED_Pin, LOW);
  while (running_mode)
  {
    digitalWrite(LED_Pin, !digitalRead(LED_Pin)); // Toggle pin status to opposite of previous status. Turns LED on or off.
    delay(750);
  }
  running_mode = true;
  LED_flash(); // Call the next function in the chain
}


void LED_flash() {

  Serial.print("LED flashing.\n");
  digitalWrite(LED_Pin, LOW);

  int on_time = 0;
  int off_time = 0;
  #define max_time 25

  while (running_mode)
  {
    for (int i = 0; i < max_time; i++) {
      on_time = i;
      off_time = max_time - i;
      digitalWrite(LED_Pin, HIGH);
      delay(on_time);
      digitalWrite(LED_Pin, LOW);
      delay(off_time);
    }
    for (int i = max_time; i > 0; i--) {
      on_time = i;
      off_time = max_time - i;
      digitalWrite(LED_Pin, HIGH);
      delay(on_time);
      digitalWrite(LED_Pin, LOW);
      delay(off_time);
    }
  }
  running_mode = true;
  LED_do_nothing(); // Call the next function in the chain
}

// That's all for the workshop! Thanks for following along.

/*
  QUESTIONS:
  1) What are the limitations of this program? How could it be done more efficiently?
    - LED "flash" stuttering is noticable at the end (not true pulse-width modulation).
    - "running_mode" exits the loop inside the function AFTER it finishes; it doesn't 
      switch right away like an interrupt normally would.
  2) In the serial monitor, you might see the "Button press detected" message happen 
    multiple times with every button press. Why is this happening? How could it be fixed?
    - The button is actually bouncing up and down, and the sensitive voltage spikes are 
      being picked up. Need to enable "debouncing" in either the hardware or software.
  3) Why is there a resistor that attaches the button output to ground?
    - Pull-down resistor
*/