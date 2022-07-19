#include <Arduino.h>
#include <../lib/ArduinoSchedule/src/schedule.h>

// LED Outputs
const short greenLedPin = 10;
const short redLedPin = 9;

// Inputs
const short inputButtonPin = 7;

// Schedules
schedule scheduleTimerRunning = {0, 500};

// Vars
bool runningStatus = false;
bool startedRunningTime;
unsigned short timeRunDuationSeconds = 180;





void setup() 
{
    // Outputs
    pinMode(greenLedPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);

    // Inputs
    pinMode(inputButtonPin, INPUT_PULLUP);

    // Set Default
    digitalWrite(greenLedPin, HIGH);
}

void startTimer()
{
    runningStatus = true;
    startedRunningTime = millis();
    digitalWrite(greenLedPin, LOW);
}

void endTimer()
{
    runningStatus = false;
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
}

void scheduleTimerRunningFunc()
{
    // Nothing to do
    if (!runningStatus) {
        return;
    }

    digitalWrite(redLedPin, !digitalRead(redLedPin));

    if (millis() - startedRunningTime >= timeRunDuationSeconds * 1000) {
        endTimer();
    }
}

// the loop function runs over and over again forever
void loop() 
{

    int buttonState = digitalRead(inputButtonPin);

    if (buttonState == LOW && !runningStatus) {
        startTimer();
    }

    // Schedules
    if (scheduleCheck(&scheduleTimerRunning)) {
        scheduleTimerRunningFunc();
        scheduleRun(&scheduleTimerRunning);
    }
}

