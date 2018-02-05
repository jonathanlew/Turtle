#include <Servo.h>

Servo servo[10];

void setup() {
  // put your setup code here, to run once:

  //set up servos
  for (int i = 2; i <= 9; i ++) {
    servo[i].attach(i);

  }

  Serial.begin(9600);


  //set all servos to middle position (stand up)
  reset();
  //  delay(2000);
  //  tiltbr(65);
  //  delay(4000);
  //  tiltbl(65);
  //  delay(4000);
  //  tiltfl(65);
  //  delay(4000);
  //  tiltfr(65);

  //  servo[6].write(35);
  //  servo[2].write(135);
  //  servo[9].write(0);
  //  delay(500);
  //  servo[9].write(70);
  //  delay(200);
  //  servo[6].write(85);
  //  servo[2].write(85);

  //  for (int i = 2; i <= 9; i += 2) {
  //    //knees
  //    servo[i].write(30);
  //    delay(500);
  //    //ankles
  //    servo[i + 1].write(30);
  //    delay(500);
  //
  //  }


}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // read the incoming byte:
    int in = Serial.parseInt();
    if (in == 0) {
      reset();
    } else if (in == 1) {
      tiltbr(65);
    } else if (in == 2) {
      tiltbl(65);
    } else if (in == 3) {
      tiltfl(65);
    } else if (in == 4) {
      tiltfr(65);
    } else if (in == 5) {
      dropdown(0, 0);
    } else if (in == 6) {
      dropdown(1, 0);
    }  else if (in == 7) {
      dropdown(0, 1);
    } else if (in == 8) {
      dropdown(1, 1);
    } else if (in == 9) {
      rotate(1);
    } else if (in == 10) {
      rotate(0);
    } else if (in == 11) {
      while  (Serial.available() <= 0) {
        turnaround(1);
      }
    } else if (in == 12) {
      while  (Serial.available() <= 0) {
        turnaround(0);
      }
    } else if (in == 13) {
      stepforward();
    } else if (in == 14) {
      crossdropdown(1);
    } else if (in == 15) {
      crossdropdown(0);
    } else if (in == 16) {
      walk_start();
    } else if (in == 17) {
      while  (Serial.available() <= 0) {
        walk_tick_alt();
      }
    }
  }

  //    stepforward();
  //    reset();
  //    delay(200);
  walk_tick_alt();
}

void stepforward() {
  dropdown(1, 1);
  delay(200);
  servo[6].write(40);
  delay(100);
  servo[2].write(150);
  delay(100);
  servo[4].write(130);
  delay(100);
  servo[8].write(20);
  delay(200);
}

void walk_start() {
  int drag = 0;
  legf(6, drag);
  delay(100);
  legf(2, drag);
  delay(100);
  legf(4, drag);
  legb(2, drag);
  delay(100);
  legf(8, drag);
  legb(6, drag);
  delay(100);



  //  crossdropdown(1);
  //  delay(1000);
  //  servo[6].write(40);
  //  delay(1000);
  //  servo[2].write(150);
  //
  //
  //  crossdropdown(0);
  //  delay(1000);
  //  servo[4].write(130);
  //  delay(1000);
  //  servo[8].write(20);
  //  delay(1000);

}

void walk_tick() {
  int drag = 0;
  legf(6, drag);
  legb(8, drag);
  delay(1000);
  legf(2, drag);
  legb(4, drag);
  delay(1000);
  legf(4, drag);
  legb(2, drag);
  delay(1000);
  legf(8, drag);
  legb(6, drag);
  delay(1000);
}

void walk_tick_alt() {
  int drag = 100;
  legf(6, drag);
  legb(4, drag);
  delay(200);
  legf(2, drag);
  legb(8, drag);
  delay(200);
  legf(4, drag);
  legb(6, drag);
  delay(200);
  legf(8, drag);
  legb(2, drag);
  delay(200);
}

/**
   leg- which leg? (2,4,6,or 8)
   drag- delay between knee mvmt and ankle mvmt
*/
void legf(int leg, int drag) {
  switch (leg) {
    case 2:
      servo[2].write(150);
      delay(drag);
      servo[3].write(140 - 35);
      break;
    case 4:
      servo[4].write(130);
      delay(drag);
      servo[5].write(140 - 35);
      break;
    case 6:
      servo[6].write(40);
      delay(drag);
      servo[7].write(0 + 35);
      break;
    case 8:
      servo[8].write(20);
      delay(drag);
      servo[9].write(0 + 35);
      break;
  }
}

/**
   leg- which leg? (2,4,6,or 8)
   drag- delay between knee mvmt and ankle mvmt
*/
void legb(int leg, int drag) {
  switch (leg) {
    case 2:
      servo[2].write(40);
      delay(drag);
      servo[3].write(0 + 50);
      break;
    case 4:
      servo[4].write(20);
      delay(drag);
      servo[5].write(0 + 50);
      break;
    case 6:
      servo[6].write(150);
      delay(drag);
      servo[7].write(140 - 50);
      break;
    case 8:
      servo[8].write(130);
      delay(drag);
      servo[9].write(140 - 50);
      break;
  }
}

void crossdropdown(bool diagonal) {
  if (diagonal) {
    servo[9].write(0 + 35);
    servo[5].write(140 - 35);
    servo[3].write(0 + 50);
    servo[7].write(140 - 50);
  } else {
    servo[7].write(0 + 35);
    servo[3].write(140 - 35);
    servo[5].write(0 + 50);
    servo[9].write(140 - 50);
  }
}

void turnaround(bool clockwise) {
  dropdown(1, 1);
  delay(200);
  rotate(clockwise);
  for (int i = 2; i <= 9; i += 2) {
    //knees
    servo[i].write(85);

  }
  delay(100);

}

void reset() {
  for (int i = 2; i <= 9; i += 2) {
    //knees
    servo[i].write(85);
    //ankles
    servo[i + 1].write(70);
  }
}

void rotate (bool clockwise) {
  //reset();
  if (clockwise) {
    servo[8].write(150);
    delay(100);
    servo[6].write(150);
    delay(100);
    servo[4].write(150);
    delay(100);
    servo[2].write(150);
    delay(200);

  } else {
    servo[8].write(20);  delay(100);
    servo[6].write(20);  delay(100);
    servo[4].write(20);  delay(100);
    servo[2].write(20);  delay(200);
  }
}

/*
   tilt legs forward or backward
*/
void dropdown(bool forward, bool halfway) {
  reset();
  if (forward) {
    servo[9].write(0 + halfway * 35);
    servo[7].write(0 + halfway * 35);
    servo[5].write(140 - halfway * 35);
    servo[3].write(140 - halfway * 35);
  } else {
    servo[5].write(0 + halfway * 35);
    servo[3].write(0 + halfway * 35);
    servo[9].write(140 - halfway * 35);
    servo[7].write(140 - halfway * 35);
  }
}

/*
   tilt goes from 0 to 65 (65 most tilted, 0 is kinda tilted)
*/
void tiltbr( int tilt ) {
  reset();
  servo[6].write(52.5 - tilt / 2);
  servo[2].write(117.5 + tilt / 2);
  servo[9].write(65 - tilt);
}

/*
   tilt goes from 0 to 65 (65 most tilted, 0 is kinda tilted)
*/
void tiltbl( int tilt ) {
  reset();
  servo[8].write(52.5 - tilt / 2);
  servo[4].write(117.5 + tilt / 2);
  servo[3].write(75 + tilt);
}

/*
   tilt goes from 0 to 65 (65 most tilted, 0 is kinda tilted)
*/
void tiltfr( int tilt ) {
  reset();

  servo[2].write(52.5 - tilt / 2);
  servo[6].write(117.5 + tilt / 2);
  servo[5].write(75 + tilt);
}

/*
   tilt goes from 0 to 65 (65 most tilted, 0 is kinda tilted)
*/
void tiltfl( int tilt ) {
  reset();

  servo[4].write(52.5 - tilt / 2);
  servo[8].write(117.5 + tilt / 2);
  servo[7].write(75 - tilt);
}

