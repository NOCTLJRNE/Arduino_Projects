#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
unsigned long now;                        // timing variables to update data at a regular interval                  
unsigned long rc_update;
const int channels = 4;                   // specify the number of receiver channels
float RC_in[channels];                    // an array to store the calibrated input from receiver 
float RC_in_trim[channels];                 // an array to store the trimmed input from receiver
enum movement {
  N,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  UPLEFT,
  UPRIGHT,
  DOWNRIGHT,
  DOWNLEFT,
  SPINLEFT,
  SPINRIGHT
};
movement bot_mov = N;
void setup() {
    setup_pwmRead();                      
    Serial.begin(9600);
    //setup input H bridge pin
    pinMode(PIN6, OUTPUT);
    pinMode(PIN7, OUTPUT);    
    pinMode(PIN8, OUTPUT);
    pinMode(PIN9, OUTPUT);
    pinMode(PIN10, OUTPUT);
    pinMode(PIN11, OUTPUT);    
    pinMode(PIN12, OUTPUT);
    pinMode(PIN13, OUTPUT);    
    //digitalWrite(8, LOW);
    //digitalWrite(9, HIGH);    
}

void loop() {  
    
    now = millis();
    
    if(RC_avail() || now - rc_update > 25){   // if RC data is available or 25ms has passed since last update (adjust to be equal or greater than the frame rate of receiver)
      
      rc_update = now;                           
      
      //print_RCpwm();                        // uncommment to print raw data from receiver to serial
      
      for (int i = 0; i<channels; i++){       // run through each RC channel
        int CH = i+1;
        
        RC_in[i] = RC_decode(CH);             // decode receiver channel and apply failsafe
        RC_in_trim[i] = RC_decode_trim(RC_in[i]);
        
        //print_decimal2percentage(RC_in[i]);   // uncomment to print calibrated receiver input (+-100%) to serial  
        print_decimal2percentage(RC_in_trim[i]);   // uncomment to print calibrated receiver input (+-100%) to serial     
      }
      // set bot movement state
      if (RC_in_trim[2] == 1.0){
        if (RC_in_trim[3] == 0.0){
          bot_mov = UP;
        } else if (RC_in_trim[3] == -1.0){
          bot_mov = UPLEFT;
        } else if (RC_in_trim[3] == 1.0){
          bot_mov = UPRIGHT;
        }
      } else if (RC_in_trim[2] == -1.0){
        if (RC_in_trim[3] == 0.0){
          bot_mov = DOWN;
        } else if (RC_in_trim[3] == -1.0){
          bot_mov = DOWNLEFT;
        } else if (RC_in_trim[3] == 1.0){
          bot_mov = DOWNRIGHT;
        }        
      } else if (RC_in_trim[2] == 0.0) {
        if (RC_in_trim[3] == 0.0){
          bot_mov = N;
        } else if (RC_in_trim[3] == -1.0){
          bot_mov = LEFT;
        } else if (RC_in_trim[3] == 1.0){
          bot_mov = RIGHT;
        }  
      } else {
        if (RC_in_trim[1] == -1.0){
          bot_mov = SPINLEFT;  
        } else if (RC_in_trim[1] == 1.0){
          bot_mov = SPINRIGHT;   
        } else {
          bot_mov = N;
        }        
      }
      //set digital output
      if (bot_mov == UP) {
        // FL roll forward
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, HIGH);
        // FR roll forward
        digitalWrite(PIN8, LOW);
        digitalWrite(PIN9, HIGH);
        // RL roll forward
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, HIGH);
        // RR roll forward
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);                                   
      } else if (bot_mov == DOWN) {
        // FL roll backward
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, LOW);
        // FR roll backward
        digitalWrite(PIN8, HIGH);
        digitalWrite(PIN9, LOW);
        // RL roll backward
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, LOW);
        // RR roll backward
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);                              
      } else if (bot_mov == LEFT) {
        // FL roll backward
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, LOW);
        // FR roll forward
        digitalWrite(PIN8, LOW);
        digitalWrite(PIN9, HIGH);
        // RL roll forward
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, HIGH);
        // RR roll backward
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);                                
      } else if (bot_mov == RIGHT) {
        // FL roll forward
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, HIGH);
        // FR roll backward
        digitalWrite(PIN8, HIGH);
        digitalWrite(PIN9, LOW);
        // RL roll backward
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, LOW);
        // RR roll forward
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);                               
      } else if (bot_mov == UPLEFT) {
        // FL not rolling
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, LOW);  
        // FR roll forward
        digitalWrite(PIN8, LOW);
        digitalWrite(PIN9, HIGH);
        // RL roll forward
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, HIGH);
        // RR not rolling
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);                                     
      } else if (bot_mov == UPRIGHT) {
        // FL roll forward
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, HIGH);
        // FR not rolling
        digitalWrite(PIN8, LOW);
        digitalWrite(PIN9, LOW); 
        // RL not rolling
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW); 
        // RR roll forward
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, HIGH);                                   
      } else if (bot_mov == DOWNRIGHT) {
        // FL not rolling
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, LOW);  
        // FR roll backward
        digitalWrite(PIN8, HIGH);
        digitalWrite(PIN9, LOW); 
        // RL roll backward
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, LOW);
        // RR not rolling
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);                                     
      } else if (bot_mov == DOWNLEFT) {
        // FL roll backward
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, LOW);
        // FR not rolling
        digitalWrite(PIN8, LOW);
        digitalWrite(PIN9, LOW); 
        // RL not rolling
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW); 
         // RR roll backward
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);                                     
      } else {
        // FL not rolling
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, LOW);
        // FR not rolling
        digitalWrite(PIN8, LOW);
        digitalWrite(PIN9, LOW);
        // RL not rolling
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW);
        // RR not rolling
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);                                 
      }
      Serial.println();                       // uncomment when printing calibrated receiver input to serial.
    }
}
