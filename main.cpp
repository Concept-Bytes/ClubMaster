#include "thingProperties.h"
#include <Arduino_LSM6DSOX.h>

float Ax, Ay, Az;
float velocity = 0;
bool toggle = true;
unsigned long previousMillis = 0;  // Store the last update time
unsigned long currentMillis = millis();
float deltaTime = (currentMillis - previousMillis) / 1000.0;  // Delta time in seconds
float accel;

const float conversionFactor = 2.237; 

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
  Serial.println();

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println("Hz");
  Serial.println();


  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  max_mph = 0;
}

void loop() {
  ArduinoCloud.update();  // Update any cloud-related functions

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(Ax, Ay, Az);
    

    // Calculate the magnitude of the acceleration vector
    // This is a more accurate representation than just summing the components
    accel_magnitude = (sqrt(Ax * Ax + Ay * Ay + Az * Az) - 1)*10;  // Subtract gravity
    currentMillis = millis();
    deltaTime = (currentMillis - previousMillis) / 1000.0;  // Delta time in seconds
    

    if (abs(accel_magnitude) > 0.5) {
        velocity += accel_magnitude * deltaTime;
    } else {
        velocity = 0;  // or apply some decay factor to velocity
    }
    
    // Convert to MPH
    mph = velocity * conversionFactor;
    
    // Check if the acceleration exceeds a threshold and the toggle is true
    if (accel_magnitude > 4.0 && toggle == true) {
      stroke_Count += 1;  // Increment the hit counter
      toggle = false;  // Reset toggle to avoid counting the same hit multiple times
    }
    else if (accel_magnitude <= 4.0 && toggle == false) {
      toggle = true;  // Reset toggle when acceleration is back to normal
    }
  }
  previousMillis = currentMillis;
  if(mph > max_mph){
    max_mph = mph;
  }
  Serial.println(accel_magnitude);
  
  delay(100);  // Wait for 100 milliseconds before the next loop iteration
}


/*
  Since AccelMagnitude is READ_WRITE variable, onAccelMagnitudeChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onAccelMagnitudeChange()  {
  // Add your code here to act upon AccelMagnitude change
}

/*
  Since StrokeCount is READ_WRITE variable, onStrokeCountChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onStrokeCountChange()  {
  // Add your code here to act upon StrokeCount change
}

/*
  Since MaxMph is READ_WRITE variable, onMaxMphChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMaxMphChange()  {
  // Add your code here to act upon MaxMph change
}

/*
  Since Mph is READ_WRITE variable, onMphChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMphChange()  {
  // Add your code here to act upon Mph change
}

/*
  Since Reset is READ_WRITE variable, onResetChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onResetChange()  {
  // Add your code here to act upon Reset change
  stroke_Count = 0;
  max_mph = 0;
}
