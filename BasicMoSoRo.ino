/* User-defined parameters*/

// define number of motors / actuators
const int number_of_motors=4;
// define motor pin numbers
const int8_t motor[] ={3,4,6,7,9,10,11,12}; 
// define desired input cycles
const int8_t cycle1[]={2,5,8};
const int8_t cycle2[]={0,2,15};
// if you want to use more than 2 cycles make sure to  also add variables to 
// define their lengths

/* Initializations (should not change)*/
// number of robot states  (assuming bang-bang control)
const int number_of_states=pow(2,number_of_motors);
// if more states are desired (e.g. including intermediate actuation states), the exponent base here can be adjusted.
//  zero matrix of all robot states 
int state_matrix[number_of_motors][number_of_states]={ };
// added booleans to avoid reversing a motor if the actuator was already relaxed in the previous state.
bool just_curled[number_of_motors] = { };
bool just_relaxed[number_of_motors] = { };
// define length of each cycle
const int8_t cycle1_size = sizeof(cycle1);
const int8_t cycle2_size = sizeof(cycle2);




void setup() {
 Serial.begin(9600); // baud rate for serial monitor communication
 // when reading from the  serial  monitor, make sure the monitor is set to this baud rate
 define_states();

}


void loop() {
// anything placed inside the loop function will cycle continously forever unless interrupts are added.
// if you want to add any code that should be run only once, put it inside the setup function.
 cycle_through_states(cycle1, cycle1_size);
}
void define_states() {
/* This  function defines a matrix of robot states. Basically, it labels each robot state with a binary number that 
corresponds to which motors are on or off. 1 = on, 0 = off*/

  for (int k=0; k<= number_of_states-1; k++) {
    int spacing=1;
    for (int j=number_of_motors-1; j>=0; j--) {
      if (state_matrix[j][k]==0 && k+spacing<=number_of_states-1){
        state_matrix[j][k+spacing]=1;
      }
      spacing=spacing*2;
    }
  }
  for (int m=0; m<=number_of_states-1; m++) {
    // this part is optional as it just prints the binary value of each state number.
    // this is helpful for debugging.
    Serial.print("State ");
    Serial.print(m);
    Serial.print(" = ");
    for (int n=0; n<=number_of_motors-1;n++){
      Serial.print(state_matrix[n][m]);
    }
    Serial.println(" ");
    }
}


void cycle_through_states (int8_t *cycle, int8_t cycle_size) {
/* This  function controls the motor based on the array of state numbers provided*/
  for (int i=0; i<cycle_size;i++) {
    Serial.print("State ");
    Serial.print(cycle[i]);
    Serial.print(": ");
    for (int j=0; j<=3; j++) {
      Serial.print(state_matrix[j][cycle[i]]);
      if (state_matrix[j][cycle[i]] == 0 && just_relaxed[j]==false) {
        digitalWrite(motor[2*j], LOW);
        digitalWrite(motor[2*j+1], HIGH);
        just_relaxed[j] = true;
        just_curled[j] = false;
      }
      else if (state_matrix[j][cycle[i]] == 1)  {
        digitalWrite(motor[2*j],HIGH);
        digitalWrite(motor[2*j+1], LOW);
        just_relaxed[j] = false;
        just_curled[j] = true;
      }
      if (j==3) {
        delay(50);
        for (int k=0; k<=3; k++) {
          if (state_matrix[k][cycle[i]] == 0) {
            digitalWrite(motor[2*k+1], LOW);
          }
          if (k==3){
            delay(350);
            Serial.println("");
          }
        }
       }
    }
  }
}   
