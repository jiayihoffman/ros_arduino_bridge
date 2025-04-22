/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined(ARDUINO_ENC_COUNTER)
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT and RIGHT encoder, taking care of actual counting */
  ISR(PCINT1_vect) {
    static uint8_t enc_last_left = 0;
    static uint8_t enc_last_right = 0;

    uint8_t pins = PINC;  // Read the entire PORTC once

    // --- LEFT encoder (on PC2=A2 and PC3=A3) ---
    // Shift previous state to make room for 2 new bits
    enc_last_left <<= 2;

    // Mask out the bits for LEFT_ENC_PIN_A and LEFT_ENC_PIN_B
    // and shift them down to bit 0 and 1
    enc_last_left |= (pins & ((1 << LEFT_ENC_PIN_A) | (1 << LEFT_ENC_PIN_B))) >> LEFT_ENC_PIN_A;

    // Lookup the direction and update position
    left_enc_pos += ENC_STATES[enc_last_left & 0x0F];

    // --- RIGHT encoder (on PC4=A4 and PC5=A5) ---
    enc_last_right <<= 2;
    enc_last_right |= (pins & ((1 << RIGHT_ENC_PIN_A) | (1 << RIGHT_ENC_PIN_B))) >> RIGHT_ENC_PIN_A;
    right_enc_pos += ENC_STATES[enc_last_right & 0x0F];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif

