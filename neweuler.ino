//declaring and initializing two terminals for each motor
const int number_of_motors=4;
const int number_of_states=number_of_motors*number_of_motors;
int state_matrix[number_of_motors][number_of_states]={ };
bool just_curled[number_of_motors] = { };
bool just_relaxed[number_of_motors] = { };
int8_t cycle1[]={6,3,13};
int reward_matrix[]={ };
const int motor[] ={3,4,6,7,9,10,11,12};
const int cycle2[]={0,2,15};
//declaring and initializing a matrix of all robot states with all zeros

void define_states();


void setup() {
 Serial.begin(9600);
 define_states();
 //define_arc_numbers();
 //define_euler_tour();
}


void loop() {

 cycle_through_states();

}
void define_states() {

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
    Serial.print("State ");
    Serial.print(m);
    Serial.print(" = ");
    for (int n=0; n<=number_of_motors-1;n++){
      Serial.print(state_matrix[n][m]);
    }
    Serial.println(" ");
    }
}


void cycle_through_states () {

  for (int i=0; i<sizeof(cycle1);i++) {
    Serial.print("Node ");
    Serial.print(cycle1[i]);
    Serial.print(": ");
    for (int j=0; j<=3; j++) {
      Serial.print(state_matrix[j][cycle1[i]]);
      if (state_matrix[j][cycle1[i]] == 0 && just_relaxed[j]==false) {
        digitalWrite(motor[2*j], LOW);
        digitalWrite(motor[2*j+1], HIGH);
        just_relaxed[j] = true;
        just_curled[j] = false;
      }
      else if (state_matrix[j][cycle1[i]] == 1)  {
        digitalWrite(motor[2*j],HIGH);
        digitalWrite(motor[2*j+1], LOW);
        just_relaxed[j] = false;
        just_curled[j] = true;
      }
      if (j==3) {
        delay(50);
        for (int k=0; k<=3; k++) {
          if (state_matrix[k][cycle1[i]] == 0) {
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
