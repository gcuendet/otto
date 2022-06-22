//----------------------------------------------------------------
//-- Otto sings songs
//-- With this code Otto will walk 5 steps and then sing a song before doing it again
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------
#include <Otto.h>
Otto Otto;

#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5 
#define Buzzer  13 

int speakerPin = Buzzer;
int length = 35; // the number of notes in each song

//              |Frere Jacques                     |Happy Birthday                    |Au clair de la lune            
char notes[] = "cdeccdecefgefggagfecgagfecdGcdGc   GGAGcB GGAGdc GGgecBA ffecdc       cccdedceddc cccdedceddc ddddAAdcBAG";
//              | Frere Jacques
char beats[]  = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8,20, 8, 8,20, 2, 2, 2, 2, 8, 8, 2, 2, 2, 2, 8, 8, 8, 8,20, 8, 8,32, 1, 1, 1,
//              | Happy Birthday
                 2, 2, 8, 8, 8,16, 1, 2, 2, 8, 8, 8,16, 1, 2, 2, 8, 8, 8, 8,16, 1, 2, 2, 8, 8, 8,16, 1, 1, 1, 1, 1, 1, 1,
//              | Au clair de la lune
                 8, 8, 8, 8,20,20, 8, 8, 8, 8,32, 1, 8, 8, 8, 8,20,20, 8, 8, 8, 8,32, 1, 8, 8, 8, 8,20,20, 8, 8, 8, 8,32};

int tempo = 150;
int number_songs = 3;
int song = 0;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
     digitalWrite(speakerPin, HIGH);
     delayMicroseconds(tone);
     digitalWrite(speakerPin, LOW);
     delayMicroseconds(tone);
  }
}

// 2 scales: C4 -> B5
char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',
                'c', 'd', 'e', 'f', 'g', 'a', 'b'};

// Contains half-period of each note in microseconds
// tone = 1/(2f) * 10E6, where f is the frequency of the note in Hertz
int tones[] = { 1911, 1703, 1517, 1432, 1276, 1136, 1012,
                 956,  851,  758,  716,  638,  568,  506};

int SPEE = 5; 

// play the tone corresponding to the note name
void playNote(char note, int duration) {
  for (int i = 0; i < sizeof(names); i++) {
     if (names[i] == note) {
       int newduration = duration/SPEE;
       playTone(tones[i], newduration);
     }
  }
}

void setup() {
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  for (int l = song; l < number_songs; l++) {
    Otto.walk(5,1300,1); 
    Otto.playGesture(OttoSuperHappy);
    for (int i = l*length; i < (l + 1)*length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        playNote(notes[i], beats[i] * tempo);
      }
      // pause between notes
      delay(tempo);   
    }
  }
}
