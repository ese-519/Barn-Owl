// This #include statement was automatically added by the Particle IDE.
#include "PietteTech_DHT/PietteTech_DHT.h"

// This #include statement was automatically added by the Particle IDE.
#include "blynk/blynk.h"

// system defines
#define DHTTYPE  DHT11              // Sensor type DHT11/21/22/AM2301/AM2302
#define DHTPIN4  7              // Digital pin for communications
#define DHTPIN3  6              // Digital pin for communications
#define DHTPIN2  5              // Digital pin for communications
#define DHTPIN1  4              // Digital pin for communications
#define DHT_SAMPLE_INTERVAL   3000  // Sample every minute
#define Temp_Limit 29
#define Humidity_Limit 20
#define Light_Limit 75
#define Soil_NoPlant 2700



int Moist_Limit_Slot1=Soil_NoPlant;
int Moist_Limit_Slot2=Soil_NoPlant;
int Moist_Limit_Slot3=Soil_NoPlant;
int Moist_Limit_Slot4=Soil_NoPlant;
int Mux_Pin = A0;
//declaration
void dht_wrapper(); // must be declared before the lib initialization

// Lib instantiate
PietteTech_DHT DHT1(DHTPIN1, DHTTYPE, dht_wrapper1);
PietteTech_DHT DHT2(DHTPIN2, DHTTYPE, dht_wrapper2);
PietteTech_DHT DHT3(DHTPIN3, DHTTYPE, dht_wrapper3);
PietteTech_DHT DHT4(DHTPIN4, DHTTYPE, dht_wrapper4);

// globals
unsigned int DHTnextSampleTime;     // Next time we want to start sample
bool bDHTstarted;           // flag to indicate we started acquisition
int n;                              // counter
int Power_Loss=0;


int Kyle_Moist=3000;
int Tomato_Moist=3050;
int RoseMary_Moist=3150;
int Thyme_Moist=3200;
int Broccoli_Moist=3250;
int Mode=1;
int Plant_Choice_Slot1=1;
int Plant_Choice_Slot2=1;
int Plant_Choice_Slot3=1;
int Plant_Choice_Slot4=1;
int Sys_Pre_Light_Time=0;
int Sys_Cur_Light_Time=0;







char tempInChar_slot1[32];
char HumInChar_slot1[32];
float humid_slot1;
float temp_slot1;
char tempInChar_slot2[32];
char HumInChar_slot2[32];
float humid_slot2;
float temp_slot2;
char tempInChar_slot3[32];
char HumInChar_slot3[32];
float humid_slot3;
float temp_slot3;
char tempInChar_slot4[32];
char HumInChar_slot4[32];
float humid_slot4;
float temp_slot4;

float  Avg_Humidity;
float Avg_Temp;
float Avg_Light;

int Soil_Moist_Slot1;
int Light_Slot1;
int Soil_Moist_Slot2;
int Light_Slot2;
int Soil_Moist_Slot3;
int Light_Slot3;
int Soil_Moist_Slot4;
int Light_Slot4;

//this is coming from http://www.instructables.com/id/Datalogging-with-Spark-Core-Google-Drive/?ALLSTEPS
char resultstr[64]; //String to store the sensor data

char auth[] = "93d681ed76724d2c88171bf7a816340e";


char VERSION[64] = "0.04";

#define READ_INTERVAL 5000



void setup()
{
    Time.zone(-5);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(DHTPIN1, OUTPUT);     //D4
    pinMode(DHTPIN2, OUTPUT);     //D5
    pinMode(DHTPIN3, OUTPUT);    //D6
    pinMode(DHTPIN4, OUTPUT);   //D7
    pinMode(A0, INPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(A6, OUTPUT);
    pinMode(A7, OUTPUT);
    Serial.begin(9600);
    delay(5000);
    Blynk.begin(auth);
    DHTnextSampleTime = 0;  // Start the first sample immediately
    Particle.variable("result", resultstr, STRING);
}



void dht_wrapper1()
{
    DHT1.isrCallback();
}

void dht_wrapper2()
{
    DHT2.isrCallback();
}

void dht_wrapper3()
{
    DHT3.isrCallback();
}

void dht_wrapper4()
{
    DHT4.isrCallback();
}



BLYNK_WRITE(V41)
{
    Plant_Choice_Slot1 = param.asInt();
    // Serial.println(Plant_Choice_Slot3);
    //Serial.println("Only Once");

    switch (Plant_Choice_Slot1) {
        case 1: {
            // Serial.println("Slot3:No Plant Chosen");
            Moist_Limit_Slot1 = Soil_NoPlant;
        }
        break;
        case 2: {
            // Serial.println("Slot3:Kyle Chosen");
            Moist_Limit_Slot1 = Kyle_Moist;
            break;
        }
        case 3: {
            // Serial.println("Slot3:Tomato Chosen");
            Moist_Limit_Slot1 = Tomato_Moist;
            break;
        }
        case 4: {
            // Serial.println("Slot3:RoseMary Chosen");
            Moist_Limit_Slot1 = RoseMary_Moist;
            break;
        }
        case 5: {
            // Serial.println("Slot3:Thyme Chosen");
            Moist_Limit_Slot1 = Thyme_Moist;
            break;
        }
        case 6: {
            // Serial.println("Slot3:Broccoli Chosen");
            Moist_Limit_Slot1 = Broccoli_Moist;
            break;
        }
        default:  {
            break;
            Moist_Limit_Slot1 = Soil_NoPlant;
        }

    }
//  Serial.println(Moist_Limit);
}



BLYNK_WRITE(V42)
{
    Plant_Choice_Slot1 = param.asInt();
    // Serial.println(Plant_Choice_Slot3);
    //Serial.println("Only Once");

    switch (Plant_Choice_Slot2) {
        case 1: {
            // Serial.println("Slot3:No Plant Chosen");
            Moist_Limit_Slot2 = Soil_NoPlant;
        }
        break;
        case 2: {
            // Serial.println("Slot3:Kyle Chosen");
            Moist_Limit_Slot2 = Kyle_Moist;
            break;
        }
        case 3: {
            // Serial.println("Slot3:Tomato Chosen");
            Moist_Limit_Slot2 = Tomato_Moist;
            break;
        }
        case 4: {
            // Serial.println("Slot3:RoseMary Chosen");
            Soil_Moist_Slot2 = RoseMary_Moist;
            break;
        }
        case 5: {
            // Serial.println("Slot3:Thyme Chosen");
            Moist_Limit_Slot2 = Thyme_Moist;
            break;
        }
        case 6: {
            // Serial.println("Slot3:Broccoli Chosen");
            Moist_Limit_Slot2 = Broccoli_Moist;
            break;
        }
        default:  {
            break;
            Moist_Limit_Slot2 = Soil_NoPlant;
        }

    }
// Serial.println(Moist_Limit);
}



BLYNK_WRITE(V43)
{
    Plant_Choice_Slot3 = param.asInt();
    // Serial.println(Plant_Choice_Slot3);
    //Serial.println("Only Once");

    switch (Plant_Choice_Slot3) {
        case 1: {
            // Serial.println("Slot3:No Plant Chosen");
            Moist_Limit_Slot3 = Soil_NoPlant;
        }
        break;
        case 2: {
            // Serial.println("Slot3:Kyle Chosen");
            Moist_Limit_Slot3 = Kyle_Moist;
            break;
        }
        case 3: {
            // Serial.println("Slot3:Tomato Chosen");
            Moist_Limit_Slot3 = Tomato_Moist;
            break;
        }
        case 4: {
            // Serial.println("Slot3:RoseMary Chosen");
            Moist_Limit_Slot3 = RoseMary_Moist;
            break;
        }
        case 5: {
            // Serial.println("Slot3:Thyme Chosen");
            Moist_Limit_Slot3 = Thyme_Moist;
            break;
        }
        case 6: {
            // Serial.println("Slot3:Broccoli Chosen");
            Moist_Limit_Slot3 = Broccoli_Moist;
            break;
        }
        default:  {
            break;
            Moist_Limit_Slot3 = Soil_NoPlant;
        }

    }
// Serial.println(Moist_Limit);
}




BLYNK_WRITE(V44)
{
    Plant_Choice_Slot4 = param.asInt();
    // Serial.println(Plant_Choice_Slot3);
    //Serial.println("Only Once");

    switch (Plant_Choice_Slot4) {
        case 1: {
            // Serial.println("Slot4:No Plant Chosen");
            Moist_Limit_Slot4 = Soil_NoPlant;
        }
        break;
        case 2: {
            // Serial.println("Slot4:Kyle Chosen");
            Moist_Limit_Slot4 = Kyle_Moist;
            break;
        }
        case 3: {
            // Serial.println("Slot4:Tomato Chosen");
            Moist_Limit_Slot4 = Tomato_Moist;
            break;
        }
        case 4: {
            // Serial.println("Slot4:RoseMary Chosen");
            Moist_Limit_Slot4 = RoseMary_Moist;
            break;
        }
        case 5: {
            // Serial.println("Slot4:Thyme Chosen");
            Moist_Limit_Slot4 = Thyme_Moist;
            break;
        }
        case 6: {
            // Serial.println("Slot4:Broccoli Chosen");
            Moist_Limit_Slot4 = Broccoli_Moist;
            break;
        }
        default:  {
            break;
            Soil_Moist_Slot4 = Soil_NoPlant;
        }

    }
// Serial.println(Moist_Limit);
}

BLYNK_WRITE(V45)
{
    Mode = param.asInt();
    Blynk.virtualWrite(V45, Mode);
    Blynk.virtualWrite(V46, Mode);
    Blynk.virtualWrite(V47, Mode);
    Blynk.virtualWrite(V48, Mode);
    if (Mode==1) {
        // Serial.println("Auto Mode Chosen from 1");
    }
    if (Mode==2) {
        // Serial.println("Manual Mode Chosen from 1");
    }
}

BLYNK_WRITE(V46)
{
    Mode = param.asInt();
    Blynk.virtualWrite(V45, Mode);
    Blynk.virtualWrite(V46, Mode);
    Blynk.virtualWrite(V47, Mode);
    Blynk.virtualWrite(V48, Mode);
    if (Mode==1) {
        Serial.println("Auto Mode Chosen from 2");
    }
    if (Mode==2) {
        Serial.println("Manual Mode Chosen from 2");
    }
}

BLYNK_WRITE(V47)
{
    Mode = param.asInt();
    Blynk.virtualWrite(V45, Mode);
    Blynk.virtualWrite(V46, Mode);
    Blynk.virtualWrite(V47, Mode);
    Blynk.virtualWrite(V48, Mode);
    if (Mode==1) {
        Serial.println("Auto Mode Chosen from 3");
    }
    if (Mode==2) {
        Serial.println("Manual Mode Chosen from 3");
    }
}

BLYNK_WRITE(V48)
{
    Mode = param.asInt();
    Blynk.virtualWrite(V45, Mode);
    Blynk.virtualWrite(V46, Mode);
    Blynk.virtualWrite(V47, Mode);
    Blynk.virtualWrite(V48, Mode);
    if (Mode==1) {
        Serial.println("Auto Mode Chosen from 4");
    }
    if (Mode==2) {
        Serial.println("Manual Mode Chosen from 4");
    }
}


void Auto_To_Manual()
{
    if (Mode==1 && Power_Loss>=7) {
        Blynk.virtualWrite(V45, 2);
        Mode=2;
        Serial.println("In Mode Change at 51");
        Blynk.virtualWrite(V46, 2);
        Mode=2;
        Serial.println("Power_Loss2");
        Serial.println(Power_Loss);
        Blynk.virtualWrite(V47, 2);
        Mode=2; // Serial.println("In Mode Change");
        Blynk.virtualWrite(V48, 2);
        Mode=2; // Serial.println("In Mode Change");
    } else {
        Power_Loss++;
    }

}



BLYNK_WRITE(V51)
{
    int status51 = param.asInt();
    //    Serial.println("status51");
//Serial.println(status51);
    //     Serial.println("Power_Loss");
    //           Serial.println(Power_Loss);
    Auto_To_Manual();
    if (status51==1) {
        digitalWrite(A1, HIGH);
        Blynk.virtualWrite(V51, HIGH);
    } else if (status51==0)  {
        digitalWrite(A1, LOW);
        Blynk.virtualWrite(V51, LOW);
    }

    delay(50);
}

BLYNK_WRITE(V52)
{
    int status52 = param.asInt();
//   Serial.println(status52);
    Auto_To_Manual();
    if (status52==1)      {
        digitalWrite(A2, HIGH);
        Blynk.virtualWrite(V52, HIGH);
    } else if (status52==0)  {
        digitalWrite(A2, LOW);
        Blynk.virtualWrite(V52, LOW);
    }
    delay(50);

}

BLYNK_WRITE(V53)
{
    int status53 = param.asInt();
    //  Serial.println("status53");
//Serial.println(status53);
    //     Serial.println("in 53 Power_Loss");
    //           Serial.println(Power_Loss);
    Auto_To_Manual();
    if (status53==1)      {
        digitalWrite(A3, HIGH);
        Blynk.virtualWrite(V53, HIGH);
    } else if (status53==0)  {
        digitalWrite(A3, LOW);
        Blynk.virtualWrite(V53, LOW);
    }
    delay(50);

}


BLYNK_WRITE(V54)
{
    int status54 = param.asInt();
    //     Serial.println("Mode_Slot3");
    //Serial.println(Mode_Slot3);
    // Serial.println(" Before Power_Loss 54");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    // Serial.println(" After Power_Loss 54");
    // Serial.println(Power_Loss);

    if (status54==1)      {
        digitalWrite(A4, HIGH);
        // Serial.println("Updaing Loop");
        Blynk.virtualWrite(V54, HIGH);
    } else if (status54==0)  {
        digitalWrite(A4, LOW);
        // Serial.println("Updaing Loop2");
        Blynk.virtualWrite(V54, LOW);

    }
    delay(50);

}


BLYNK_WRITE(V55)
{
    int status55 = param.asInt();
    Serial.println("status55");
    Serial.println(status55);
    Serial.println("in 55 Power_Loss");
    Serial.println(Power_Loss);
    Auto_To_Manual();
    if (status55==1)      {
        digitalWrite(A5, HIGH);
        Blynk.virtualWrite(V55, HIGH);
        Blynk.virtualWrite(V65, HIGH);
        Blynk.virtualWrite(V66, HIGH);
        Blynk.virtualWrite(V67, HIGH);
    } else if (status55==0)  {
        digitalWrite(A5, LOW);
        Blynk.virtualWrite(V55, LOW);
        Blynk.virtualWrite(V65, LOW);
        Blynk.virtualWrite(V66, LOW);
        Blynk.virtualWrite(V67, LOW);
    }
    delay(50);

}


BLYNK_WRITE(V65)
{
    int status65 = param.asInt();
    Serial.println("status57");
    Serial.println(status65);
    Serial.println("in status65 Power_Loss");
    Serial.println(Power_Loss);
    Auto_To_Manual();
    Serial.println("post 57 Power_Loss");
    Serial.println(Power_Loss);

    if (status65==1)      {
        digitalWrite(A5, HIGH);
        Blynk.virtualWrite(V55, HIGH);
        Blynk.virtualWrite(V66, HIGH);
        Blynk.virtualWrite(V67, HIGH);
        Blynk.virtualWrite(V65, HIGH);
    } else if (status65==0)  {
        digitalWrite(A5, LOW);
        Blynk.virtualWrite(V65, LOW);
        Blynk.virtualWrite(V55, LOW);
        Blynk.virtualWrite(V66, LOW);
        Blynk.virtualWrite(V67, LOW);
    }
    delay(50);

}



BLYNK_WRITE(V66)
{
    int status66 = param.asInt();
    Serial.println("status66");
    Serial.println(status66);
    Serial.println("in 57 Power_Loss");
    Serial.println(Power_Loss);
    Auto_To_Manual();
    Serial.println("status66 Power_Loss");
    Serial.println(Power_Loss);

    if (status66==1)      {
        digitalWrite(A5, HIGH);
        Blynk.virtualWrite(V66, HIGH);
        Blynk.virtualWrite(V55, HIGH);
        Blynk.virtualWrite(V67, HIGH);
        Blynk.virtualWrite(V65, HIGH);
    } else if (status66==0)  {
        digitalWrite(A5, LOW);
        Blynk.virtualWrite(V55, LOW);
        Blynk.virtualWrite(V66, LOW);
        Blynk.virtualWrite(V67, LOW);
        Blynk.virtualWrite(V65, LOW);
    }
    delay(50);

}


BLYNK_WRITE(V67)
{
    int status67 = param.asInt();
    Serial.println("status67");
    Serial.println(status67);
    Serial.println("in 57 Power_Loss");
    Serial.println(Power_Loss);
    Auto_To_Manual();
    Serial.println("post 57 Power_Loss");
    Serial.println(Power_Loss);

    if (status67==1)      {
        digitalWrite(A5, HIGH);
        Blynk.virtualWrite(V67, HIGH);
        Blynk.virtualWrite(V66, HIGH);
        Blynk.virtualWrite(V55, HIGH);
        Blynk.virtualWrite(V65, HIGH);
    } else if (status67==0)  {
        digitalWrite(A5, LOW);
        Blynk.virtualWrite(V67, LOW);
        Blynk.virtualWrite(V66, LOW);
        Blynk.virtualWrite(V55, LOW);
        Blynk.virtualWrite(V65, LOW);
    }
    delay(50);

}



BLYNK_WRITE(V56)
{
    int status56 = param.asInt();
//  Serial.println("status56");
//Serial.println(status56);
    //  Serial.println("in 56 Power_Loss");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    if (status56==1)      {
        digitalWrite(A6, HIGH);
        Blynk.virtualWrite(V56,HIGH);
        Blynk.virtualWrite(V75,HIGH);
        Blynk.virtualWrite(V76,HIGH);
        Blynk.virtualWrite(V77,HIGH);
    } else if (status56==0)  {
        digitalWrite(A6, LOW);
        Blynk.virtualWrite(V56,LOW);
        Blynk.virtualWrite(V75,LOW);
        Blynk.virtualWrite(V76,LOW);
        Blynk.virtualWrite(V77,LOW);
    }
    delay(50);

}


BLYNK_WRITE(V75)
{
    int status75 = param.asInt();
//  Serial.println("status56");
//Serial.println(status56);
    //  Serial.println("in 56 Power_Loss");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    if (status75==1)      {
        digitalWrite(A6, HIGH);
        Blynk.virtualWrite(V56,HIGH);
        Blynk.virtualWrite(V75,HIGH);
        Blynk.virtualWrite(V76,HIGH);
        Blynk.virtualWrite(V77,HIGH);
    } else if (status75==0)  {
        digitalWrite(A6, LOW);
        Blynk.virtualWrite(V56,LOW);
        Blynk.virtualWrite(V75,LOW);
        Blynk.virtualWrite(V76,LOW);
        Blynk.virtualWrite(V77,LOW);
    }
    delay(50);

}


BLYNK_WRITE(V76)
{
    int status76 = param.asInt();
//  Serial.println("status56");
//Serial.println(status56);
    //  Serial.println("in 56 Power_Loss");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    if (status76==1)      {
        digitalWrite(A6, HIGH);
        Blynk.virtualWrite(V56,HIGH);
        Blynk.virtualWrite(V75,HIGH);
        Blynk.virtualWrite(V76,HIGH);
        Blynk.virtualWrite(V77,HIGH);
    } else if (status76==0)  {
        digitalWrite(A6, LOW);
        Blynk.virtualWrite(V56,LOW);
        Blynk.virtualWrite(V75,LOW);
        Blynk.virtualWrite(V76,LOW);
        Blynk.virtualWrite(V77,LOW);
    }
    delay(50);

}

BLYNK_WRITE(V77)
{
    int status77 = param.asInt();
//  Serial.println("status56");
//Serial.println(status56);
    //  Serial.println("in 56 Power_Loss");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    if (status77==1)      {
        digitalWrite(A6, HIGH);
        Blynk.virtualWrite(V56,HIGH);
        Blynk.virtualWrite(V75,HIGH);
        Blynk.virtualWrite(V76,HIGH);
        Blynk.virtualWrite(V77,HIGH);
    } else if (status77==0)  {
        digitalWrite(A6, LOW);
        Blynk.virtualWrite(V56,LOW);
        Blynk.virtualWrite(V75,LOW);
        Blynk.virtualWrite(V76,LOW);
        Blynk.virtualWrite(V77,LOW);
    }
    delay(50);

}


BLYNK_WRITE(V57)
{
    int status57 = param.asInt();
    //  Serial.println("status57");
//    Serial.println(status57);
    // Serial.println("in 57 Power_Loss");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    // Serial.println("post 57 Power_Loss");
    // Serial.println(Power_Loss);

    if (status57==1)      {
        digitalWrite(A7, HIGH);
        Blynk.virtualWrite(V57,HIGH);
        Blynk.virtualWrite(V85,HIGH);
        Blynk.virtualWrite(V86,HIGH);
        Blynk.virtualWrite(V87,HIGH);

    } else if (status57==0)  {
        digitalWrite(A7, LOW);
        Blynk.virtualWrite(V57,LOW);
        Blynk.virtualWrite(V85,LOW);
        Blynk.virtualWrite(V86,LOW);
        Blynk.virtualWrite(V87,LOW);
    }
    delay(50);

}

BLYNK_WRITE(V85)
{
    int status85 = param.asInt();
    //  Serial.println("status57");
//    Serial.println(status57);
    // Serial.println("in 57 Power_Loss");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    // Serial.println("post 57 Power_Loss");
    // Serial.println(Power_Loss);

    if (status85==1)      {
        digitalWrite(A7, HIGH);
        Blynk.virtualWrite(V57,HIGH);
        Blynk.virtualWrite(V85,HIGH);
        Blynk.virtualWrite(V86,HIGH);
        Blynk.virtualWrite(V87,HIGH);

    } else if (status85==0)  {
        digitalWrite(A7, LOW);
        Blynk.virtualWrite(V57,LOW);
        Blynk.virtualWrite(V85,LOW);
        Blynk.virtualWrite(V86,LOW);
        Blynk.virtualWrite(V87,LOW);
    }
    delay(50);

}


BLYNK_WRITE(V86)
{
    int status86 = param.asInt();
    //  Serial.println("status57");
//    Serial.println(status57);
    // Serial.println("in 57 Power_Loss");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    // Serial.println("post 57 Power_Loss");
    // Serial.println(Power_Loss);

    if (status86==1)      {
        digitalWrite(A7, HIGH);
        Blynk.virtualWrite(V57,HIGH);
        Blynk.virtualWrite(V85,HIGH);
        Blynk.virtualWrite(V86,HIGH);
        Blynk.virtualWrite(V87,HIGH);

    } else if (status86==0)  {
        digitalWrite(A7, LOW);
        Blynk.virtualWrite(V57,LOW);
        Blynk.virtualWrite(V85,LOW);
        Blynk.virtualWrite(V86,LOW);
        Blynk.virtualWrite(V87,LOW);
    }
    delay(50);

}


BLYNK_WRITE(V87)
{
    int status87 = param.asInt();
    //  Serial.println("status57");
//    Serial.println(status57);
    // Serial.println("in 57 Power_Loss");
    // Serial.println(Power_Loss);
    Auto_To_Manual();
    // Serial.println("post 57 Power_Loss");
    // Serial.println(Power_Loss);

    if (status87==1)      {
        digitalWrite(A7, HIGH);
        Blynk.virtualWrite(V57,HIGH);
        Blynk.virtualWrite(V85,HIGH);
        Blynk.virtualWrite(V86,HIGH);
        Blynk.virtualWrite(V87,HIGH);

    } else if (status87==0)  {
        digitalWrite(A7, LOW);
        Blynk.virtualWrite(V57,LOW);
        Blynk.virtualWrite(V85,LOW);
        Blynk.virtualWrite(V86,LOW);
        Blynk.virtualWrite(V87,LOW);
    }
    delay(50);

}






BLYNK_WRITE(V61)
{
    Blynk.virtualWrite(V41, 1);
    // Serial.println("Plant previously selected was");
    // Serial.println(Plant_Choice_Slot1);
    Blynk.virtualWrite(V45, 1);
    // Serial.println("Mode previously selected was");
    Blynk.virtualWrite(V51,LOW);
    Blynk.virtualWrite(V57,LOW);
    Blynk.virtualWrite(V67,LOW);
    Blynk.virtualWrite(V77,LOW);
    Blynk.virtualWrite(V87,LOW);

    Blynk.virtualWrite(V56,LOW);
    Blynk.virtualWrite(V66,LOW);
    Blynk.virtualWrite(V76,LOW);
    Blynk.virtualWrite(V86,LOW);
    delay(50);


    Blynk.virtualWrite(V55,LOW);
    Blynk.virtualWrite(V65,LOW);
    Blynk.virtualWrite(V75,LOW);
    Blynk.virtualWrite(V85,LOW);

    digitalWrite(A1, LOW);
    digitalWrite(A5, LOW);
    digitalWrite(A6, LOW);
    digitalWrite(A7, LOW);

    Moist_Limit_Slot1 = Soil_NoPlant;
    Mode=1;
    Plant_Choice_Slot1=1;
    Blynk.virtualWrite(V45, Mode);
    Blynk.virtualWrite(V46, Mode);
    Blynk.virtualWrite(V47, Mode);
    Blynk.virtualWrite(V48, Mode);
    delay(50);

}



BLYNK_WRITE(V62)
{
    Blynk.virtualWrite(V42, 1);
    // Serial.println("Plant previously selected was");
    // Serial.println(Plant_Choice_Slot2);
    Blynk.virtualWrite(V46, 1);
    // Serial.println("Mode previously selected was");
    Blynk.virtualWrite(V52,LOW);
    Blynk.virtualWrite(V57,LOW);
    Blynk.virtualWrite(V67,LOW);
    Blynk.virtualWrite(V77,LOW);
    Blynk.virtualWrite(V87,LOW);

    Blynk.virtualWrite(V56,LOW);
    Blynk.virtualWrite(V66,LOW);
    Blynk.virtualWrite(V76,LOW);
    Blynk.virtualWrite(V86,LOW);

    delay(50);

    Blynk.virtualWrite(V55,LOW);
    Blynk.virtualWrite(V65,LOW);
    Blynk.virtualWrite(V75,LOW);
    Blynk.virtualWrite(V85,LOW);


    digitalWrite(A2,LOW);
    digitalWrite(A5,LOW);
    digitalWrite(A6,LOW);
    digitalWrite(A7,LOW);

    Moist_Limit_Slot2 = Soil_NoPlant;
    Mode=1;
    Plant_Choice_Slot2=1;
    Blynk.virtualWrite(V45, Mode);
    Blynk.virtualWrite(V46, Mode);
    Blynk.virtualWrite(V47, Mode);
    Blynk.virtualWrite(V48, Mode);
    delay(50);

}


BLYNK_WRITE(V63)
{
    Blynk.virtualWrite(V43, 1);
    // Serial.println("Plant previously selected was");
    // Serial.println(Plant_Choice_Slot3);
    Blynk.virtualWrite(V47, 1);
    // Serial.println("Mode previously selected was");
    Blynk.virtualWrite(V53,LOW);
    Blynk.virtualWrite(V57,LOW);
    Blynk.virtualWrite(V67,LOW);
    Blynk.virtualWrite(V77,LOW);
    Blynk.virtualWrite(V87,LOW);
    Blynk.virtualWrite(V56,LOW);
    Blynk.virtualWrite(V66,LOW);
    Blynk.virtualWrite(V76,LOW);
    Blynk.virtualWrite(V86,LOW);
    delay(50);


    Blynk.virtualWrite(V55,LOW);
    Blynk.virtualWrite(V65,LOW);
    Blynk.virtualWrite(V75,LOW);
    Blynk.virtualWrite(V85,LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A5, LOW);
    digitalWrite(A6, LOW);
    digitalWrite(A7, LOW);

    Moist_Limit_Slot3 = Soil_NoPlant;
    Mode=1;
    Plant_Choice_Slot3=1;
    Blynk.virtualWrite(V45, Mode);
    Blynk.virtualWrite(V46, Mode);
    Blynk.virtualWrite(V47, Mode);
    Blynk.virtualWrite(V48, Mode);
    delay(50);

}

BLYNK_WRITE(V64)
{
    Blynk.virtualWrite(V44, 1);
    // Serial.println("Plant previously selected was");
    // Serial.println(Plant_Choice_Slot4);
    Blynk.virtualWrite(V48, 1);
    // Serial.println("Mode previously selected was");
    Blynk.virtualWrite(V54,LOW);
    Blynk.virtualWrite(V57,LOW);
    Blynk.virtualWrite(V67,LOW);
    Blynk.virtualWrite(V77,LOW);
    Blynk.virtualWrite(V87,LOW);

    Blynk.virtualWrite(V56,LOW);
    Blynk.virtualWrite(V66,LOW);
    Blynk.virtualWrite(V76,LOW);
    Blynk.virtualWrite(V86,LOW);

    delay(50);

    Blynk.virtualWrite(V55,LOW);
    Blynk.virtualWrite(V65,LOW);
    Blynk.virtualWrite(V75,LOW);
    Blynk.virtualWrite(V85,LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
    digitalWrite(A6, LOW);
    digitalWrite(A7, LOW);

    Moist_Limit_Slot4 = Soil_NoPlant;
    Mode=1;
    Plant_Choice_Slot4=1;
    Blynk.virtualWrite(V45, Mode);
    Blynk.virtualWrite(V46, Mode);
    Blynk.virtualWrite(V47, Mode);
    Blynk.virtualWrite(V48, Mode);
    delay(50);

}




void Temp_Humid()
{
    if (!DHT1.acquiring()) {
        // has sample completed?

        temp_slot1 = (float)DHT1.getCelsius();
        int temp1_slot1 = (temp_slot1 - (int)temp_slot1) * 100;
        delay(500);



        sprintf(tempInChar_slot1,"%0d.%d", (int)temp_slot1, temp1_slot1);
        // Particle.publish("The temperature from the slot1 is:", tempInChar_slot1, 60, PRIVATE);
        Blynk.virtualWrite(V1, tempInChar_slot1);
        //    Serial.println("Temperature slot1");
        //  Serial.println(tempInChar_slot1);





        humid_slot1 = (float)DHT1.getHumidity();
        int humid1_slot1 = (humid_slot1 - (int)humid_slot1) * 100;
        sprintf(tempInChar_slot1,"%0d.%d", (int)humid_slot1, humid1_slot1);
        Blynk.virtualWrite(V2, tempInChar_slot1);
        //Serial.println("Humidity slot1");
        //Serial.println(tempInChar_slot1);
        // Serial.println(humid_slot1);


    }

    if(!DHT2.acquiring()) {
        delay(500);
        temp_slot2 = (float)DHT2.getCelsius();
        int temp1_slot2 = (temp_slot2 - (int)temp_slot2) * 100;



        sprintf(tempInChar_slot2,"%0d.%d", (int)temp_slot2, temp1_slot2);
        // Particle.publish("The temperature from the slot2 is:", tempInChar_slot2, 60, PRIVATE);
        Blynk.virtualWrite(V3, tempInChar_slot2);
        //Serial.println("Temperature slot2");
        //Serial.println(tempInChar_slot2);


        humid_slot2 = (float)DHT2.getHumidity();
        int humid1_slot2 = (humid_slot2 - (int)humid_slot2) * 100;
        sprintf(tempInChar_slot2,"%0d.%d", (int)humid_slot2, humid1_slot2);
        // Particle.publish("The humidity from the slot2 is:", tempInChar_slot2, 60, PRIVATE);
        Blynk.virtualWrite(V4, tempInChar_slot2);
        //Serial.println("Humidity slot2");
        //Serial.println(tempInChar_slot2);

    }


    if(!DHT3.acquiring()) {
        delay(500);
        temp_slot3 = (float)DHT3.getCelsius();
        int temp1_slot3= (temp_slot3 - (int)temp_slot3) * 100;



        sprintf(tempInChar_slot3,"%0d.%d", (int)temp_slot3, temp1_slot3);
        // Particle.publish("The temperature from the slot3 is:", tempInChar_slot3, 60, PRIVATE);
        Blynk.virtualWrite(V5, tempInChar_slot3);
        //Serial.println("Temperature slot3");
        //Serial.println(tempInChar_slot3);


        humid_slot3 = (float)DHT3.getHumidity();
        int humid1_slot3 = (humid_slot3 - (int)humid_slot3) * 100;
        sprintf(tempInChar_slot3,"%0d.%d", (int)humid_slot3, humid1_slot3);
        // Particle.publish("The humidity from the slot3 is:", tempInChar_slot3, 60, PRIVATE);
        Blynk.virtualWrite(V6, tempInChar_slot3);
        //Serial.println("Humidity slot3");
        //Serial.println(tempInChar_slot3);

    }

    if(!DHT4.acquiring()) {
        delay(500);
        temp_slot4 = (float)DHT4.getCelsius();
        int temp1_slot4 = (temp_slot4 - (int)temp_slot4) * 100;

        sprintf(tempInChar_slot4,"%0d.%d", (int)temp_slot4, temp1_slot4);
        // Particle.publish("The temperature from the slot4 is:", tempInChar_slot4, 60, PRIVATE);
        Blynk.virtualWrite(V7, tempInChar_slot4);
        //Serial.println("Temperature slot4");
        //Serial.println(tempInChar_slot4);


        humid_slot4 = (float)DHT4.getHumidity();
        int humid1_slot4 = (humid_slot4 - (int)humid_slot4) * 100;
        sprintf(tempInChar_slot4,"%0d.%d", (int)humid_slot4, humid1_slot4);
        // Particle.publish("The humidity from the slot4 is:", tempInChar_slot4, 60, PRIVATE);
        Blynk.virtualWrite(V8, tempInChar_slot4);
        //Serial.println("Humidity slot4");
        //Serial.println(tempInChar_slot4);
    }

    if (temp_slot1 <0) {
        temp_slot1= 20;
    }
    if (humid_slot1 <0) {
        humid_slot1=35;
        Serial.println("Check DHT Sensor1");
    }

    if (temp_slot2 <0) {
        temp_slot2= 20;
    }
    if (humid_slot2 <0) {
        humid_slot2=35;
        Serial.println("Check DHT Sensor2");
    }

    if (temp_slot3 <0) {
        temp_slot3= 20;
    }
    if (humid_slot3 <0) {
        humid_slot3=35;
        Serial.println("Check DHT Sensor3");
    }

    if (temp_slot4 <0) {
        temp_slot4= 20;
    }
    if (humid_slot4 <0) {
        humid_slot4=35;
        Serial.println("Check DHT Sensor4");
    }


    Avg_Humidity = (humid_slot1+humid_slot2+humid_slot3+humid_slot4)/4;
    Blynk.virtualWrite(V9, Avg_Humidity);
    // Serial.println("Avg_Humidity");
    // Serial.println(Avg_Humidity);

    Avg_Temp     = (temp_slot1+temp_slot2+temp_slot3+temp_slot4)/4;
    Blynk.virtualWrite(V10, Avg_Humidity);
    //  Serial.println("Avg_Temp");
    //  Serial.println(Avg_Temp);
}



void Soil_Moist()
{
    digitalWrite(D3, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D0, LOW);
    int Analog_Moist_Slot1 = analogRead(Mux_Pin);
    if (Analog_Moist_Slot1<Moist_Limit_Slot1) {
        Soil_Moist_Slot1 = 0;
        Blynk.virtualWrite(V11, LOW);
    } else {
        Soil_Moist_Slot1 = 1;
        Blynk.virtualWrite(V11, HIGH);
    }
    //    Serial.println("Analog_Moist_Slot1");
    //    Serial.println(Analog_Moist_Slot1);
    //    Serial.println(Soil_Moist_Slot1);
    delay(100);

    digitalWrite(D3, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D0, HIGH);
    int Analog_Moist_Slot2 = analogRead(Mux_Pin);
    if (Analog_Moist_Slot2<Moist_Limit_Slot2) {
        Soil_Moist_Slot2 = 0;
        Blynk.virtualWrite(V12, LOW);
    } else {
        Soil_Moist_Slot2 = 1;
        Blynk.virtualWrite(V12, HIGH);
    }
    //  Serial.println("Analog_Moist_Slot2");
    //    Serial.println(Analog_Moist_Slot2);
    //  Serial.println(Soil_Moist_Slot2);
    delay(100);

    digitalWrite(D3, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D1, HIGH);
    digitalWrite(D0, LOW);
    int Analog_Moist_Slot3 = analogRead(Mux_Pin);
    if (Analog_Moist_Slot3<Moist_Limit_Slot3) {
        Soil_Moist_Slot3 = 0;
        Blynk.virtualWrite(V13, LOW);
    } else {
        Soil_Moist_Slot3 = 1;
        Blynk.virtualWrite(V13, HIGH);
    }
    //Serial.println("Analog_Moist_Slot3");
    //Serial.println(Analog_Moist_Slot3);
    //Serial.println(Soil_Moist_Slot3);
    delay(100);

    digitalWrite(D4, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D1, HIGH);
    digitalWrite(D0, HIGH);
    int Analog_Moist_Slot4 = analogRead(Mux_Pin);
    if (Analog_Moist_Slot4<Moist_Limit_Slot4) {
        Soil_Moist_Slot4 = 0;
        Blynk.virtualWrite(V14, LOW);
    } else {
        Soil_Moist_Slot4 = 1;
        Blynk.virtualWrite(V14, HIGH);
    }
    // Serial.println("Analog_Moist_Slot4");
    // Serial.println(Analog_Moist_Slot4);
    // Serial.println(Soil_Moist_Slot4);
    delay(100);

}


void Light_Read()
{
    float light_measurement;
    digitalWrite(D3, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D1, LOW);
    digitalWrite(D0, LOW);
    light_measurement = analogRead(Mux_Pin);
    Light_Slot1 = (int)(light_measurement/4096*100);
    Blynk.virtualWrite(V21, Light_Slot1);
    delay(100);

    digitalWrite(D3, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D1, LOW);
    digitalWrite(D0, HIGH);
    light_measurement = analogRead(Mux_Pin);
    Light_Slot2 = (int)(light_measurement/4096*100);
    Blynk.virtualWrite(V22, Light_Slot2);
    delay(100);

    digitalWrite(D3, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D1, HIGH);
    digitalWrite(D0, LOW);
    light_measurement = analogRead(Mux_Pin);
    Light_Slot3 = (int)(light_measurement/4096*100);
    Blynk.virtualWrite(V23, Light_Slot3);
    delay(100);

    digitalWrite(D3, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D1, HIGH);
    digitalWrite(D0, HIGH);
    light_measurement = analogRead(Mux_Pin);
    Light_Slot4 = (int)(light_measurement/4096*100);
    Blynk.virtualWrite(V24, Light_Slot4);
    delay(100);

    Avg_Light = (Light_Slot1+Light_Slot2+Light_Slot3+Light_Slot4)/4;
    //  Serial.println("Avg_Light");
    //  Blynk.virtualWrite(V25, Avg_Light);
    // Serial.println(Avg_Light);
}

void Water()
{
//      Serial.println(Soil_Moist_Slot1);
//    digitalWrite(D3, HIGH);  digitalWrite(D2, LOW); digitalWrite(D1, LOW); digitalWrite(D0, LOW);
    if (Soil_Moist_Slot1 == 0)  {
        digitalWrite(A1, HIGH);
        //Serial.println("Water A1 on");
        Blynk.virtualWrite(V51, HIGH);
    } else {
        digitalWrite(A1, LOW);
        // Serial.println("Water A1 off");
        Blynk.virtualWrite(V51, LOW);
    }
    delay(100);

//      Serial.println(Soil_Moist_Slot2);
//    digitalWrite(D3, HIGH);  digitalWrite(D2, LOW); digitalWrite(D1, LOW); digitalWrite(D0, HIGH);
    if (Soil_Moist_Slot2 == 0)  {
        digitalWrite(A2, HIGH);
        //Serial.println("Water A2 on");
        Blynk.virtualWrite(V52, HIGH);
    } else {
        digitalWrite(A2, LOW);
        //Serial.println("Water A2 off");
        Blynk.virtualWrite(V52, LOW);
    }
    delay(100);

//      Serial.println(Soil_Moist_Slot3);
//    digitalWrite(D3, HIGH);  digitalWrite(D2, LOW); digitalWrite(D1, HIGH); digitalWrite(D0, LOW);
    if (Soil_Moist_Slot3 == 0)  {
        digitalWrite(A3, HIGH);
        // Serial.println("Water A3 on");
        Blynk.virtualWrite(V53, HIGH);
    } else {
        digitalWrite(A3, LOW);
        //  Serial.println("Water A3 off");
        Blynk.virtualWrite(V53, LOW);
    }
    delay(100);



//    digitalWrite(D3, HIGH);  digitalWrite(D2, LOW); digitalWrite(D1, HIGH); digitalWrite(D0, HIGH);
    if (Soil_Moist_Slot4 == 0)  {
        digitalWrite(A4, HIGH);
        Blynk.virtualWrite(V54, HIGH);//Serial.println("Water A4 on");
    } else {
        digitalWrite(A4, LOW);
        Blynk.virtualWrite(V54, LOW);//Serial.println("Water A4 off");
    }
    delay(100);

}

void Fan()
{
    delay(100);
//    digitalWrite(D3, HIGH);  digitalWrite(D2, HIGH); digitalWrite(D1, LOW); digitalWrite(D0, LOW);

    if (Avg_Humidity > Humidity_Limit) {
        digitalWrite(A5, HIGH);
        Blynk.virtualWrite(V55, HIGH);//Serial.println("Fan A5 on");
        Blynk.virtualWrite(V65, HIGH);
        Blynk.virtualWrite(V66, HIGH);
        Blynk.virtualWrite(V67, HIGH);

    } else {
        digitalWrite(A5, LOW);
        Blynk.virtualWrite(V55, LOW);
        Blynk.virtualWrite(V65, LOW);
        Blynk.virtualWrite(V66, LOW);
        Blynk.virtualWrite(V67, LOW);

    }
}

void  Heater()
{
    delay(100);
//    digitalWrite(D3, HIGH);  digitalWrite(D2, HIGH); digitalWrite(D1, LOW); digitalWrite(D0, HIGH);

    if (Avg_Temp < Temp_Limit)  {
        digitalWrite(A6, HIGH);
        Blynk.virtualWrite(V56, HIGH); //Serial.println("Heater A6 on");
        Blynk.virtualWrite(V75, HIGH);
        Blynk.virtualWrite(V76, HIGH);
        Blynk.virtualWrite(V77, HIGH);
    } else {
        digitalWrite(A6, LOW);
        Blynk.virtualWrite(V56, LOW);//Serial.println("Heater A6 off");
        Blynk.virtualWrite(V75, LOW);
        Blynk.virtualWrite(V76, LOW);
        Blynk.virtualWrite(V77, LOW);

    }
}

void Light_Control()
{
    delay(100);
//    digitalWrite(D3, HIGH);  digitalWrite(D2, HIGH); digitalWrite(D1, HIGH); digitalWrite(D0, LOW);
    Sys_Cur_Light_Time = (Time.hour()*60)+Time.minute();
    if(Sys_Pre_Light_Time==0 || (Sys_Cur_Light_Time-Sys_Pre_Light_Time >=30)  ) {
        if (Avg_Light > Light_Limit)  {
            digitalWrite(A7, LOW);
            Blynk.virtualWrite(V57, LOW);
            Blynk.virtualWrite(V85, LOW);
            Blynk.virtualWrite(V86, LOW);
            Blynk.virtualWrite(V87, LOW);
        }
        Sys_Pre_Light_Time = Sys_Cur_Light_Time;
    }

    if (Avg_Light <= Light_Limit)  {
        digitalWrite(A7, HIGH);
        Blynk.virtualWrite(V57, HIGH);// Serial.println("Light A7 on");
        Blynk.virtualWrite(V85, HIGH);
        Blynk.virtualWrite(V86, HIGH);
        Blynk.virtualWrite(V87, HIGH);

    }


}

BLYNK_CONNECTED()
{
    // Serial.println("Connection Started");
    // Serial.println(Mode);
    delay(100);
    Blynk.syncVirtual(41);
    Blynk.syncVirtual(42);
    Blynk.syncVirtual(43);
    Blynk.syncVirtual(44);
    Blynk.syncVirtual(45);
    Blynk.syncVirtual(46);
    Blynk.syncVirtual(47);
    Blynk.syncVirtual(48);
    Blynk.syncVirtual(51);
    Blynk.syncVirtual(52);
    Blynk.syncVirtual(53);
    Blynk.syncVirtual(54);
    Blynk.syncVirtual(55);
    Blynk.syncVirtual(56);
    Blynk.syncVirtual(57);
    Serial.println("Connection Ended");
    Serial.println(Power_Loss);
}


void Mux()
{


    Soil_Moist();
    Light_Read();
    if(Mode==1) {

        Serial.println("In the Auto Mode");
        Water();
        Fan();
        Heater();
        Light_Control();
    }
}



void loop()
{

    Blynk.run(); // all the Blynk magic happens here


    // Check if we need to start the next sample
    if (millis() > DHTnextSampleTime) {

        if (!bDHTstarted) {
            // start the sample
            DHT1.acquire();
            DHT2.acquire();
            DHT3.acquire();
            DHT4.acquire();
            bDHTstarted = true;
        }

        Temp_Humid();
        Mux();
        n++;  // increment counter
        bDHTstarted = false;  // reset the sample flag so we can take another
        DHTnextSampleTime = millis() + DHT_SAMPLE_INTERVAL;  // set the time for next sample
    }


}