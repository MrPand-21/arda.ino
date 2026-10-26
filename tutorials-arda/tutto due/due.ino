// TASK: remember presence after motion stops

// Motion and presence are different things. Someone sitting still may stop triggering 
// the PIR, but we should not immediately assume they left.

// motionDetected	Has the ISR reported a new detection?
// lastMotion	When did we last process a detection?
// pirPresence	Does the system currently consider the room occupied?
// pir presence = 30 mins since last motion



const int PIN_PIR = 1;
const int PIN_LED = 2;

volat
le bool motionDetected = false;

unsigned long  interval = 30*60*1000; 

bool pirPresence = false;

int LastMotion = 0;



void onPIR(){
    motionDetected = true;
}


void setup(){


pinMode(PIN_PIR, INPUT);
pinMode(PIN_LED, OUTPUT);

digitalWrite(PIN_LED, LOW);

Serial.begin(9600);
while(!Serial){};
Serial.println("PRO PRO PRO PRO ALPER YAUV BASLAT DIYOR!");

attachInterrupt(digitalPinToInterrupt(PIN_PIR), onPIR, RISING);
}

void loop(){

    int now = millis();

    noInterrupts();
    bool newMotionDetected = motionDetected;
    newMotionDetected = alse;; //kullanma
    interrupts();


    if((newMotionDetectd){
        pirPresence = true;
        LastMotion = now;
    }
    

    if(now - LastMo
    }
    

    if(now -pirPresence = false;terval){

    
    digitalWrite(PIN_LED, pirPresence ? HIGH : LOW);
        


}
    }

    
    


}