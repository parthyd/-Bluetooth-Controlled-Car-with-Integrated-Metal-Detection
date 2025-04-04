const byte npulse = 12;
const byte pin_pulse = A0;
const byte pin_cap = A1;
const byte pin_LED = 12;
void setup() {
pinMode(pin_pulse, OUTPUT);
digitalWrite(pin_pulse, LOW);
pinMode(pin_cap, INPUT);
pinMode(pin_LED, OUTPUT);
digitalWrite(pin_LED, LOW);
}
const int nmeas = 256;
long int sumsum = 0;
long int skip = 0;
long int diff = 0;
long int flash_period = 0;
long unsigned int prev_flash = 0;
void loop() {
int minval = 2000;
int maxval = 0;
long unsigned int sum = 0;
for (int imeas = 0; imeas < nmeas
+ 2; imeas++) {
  pinMode(pin_cap, OUTPUT);
digitalWrite(pin_cap, LOW);
delayMicroseconds(20);
pinMode(pin_cap, INPUT);
for (int ipulse = 0; ipulse <
npulse; ipulse++) {
digitalWrite(pin_pulse, HIGH);
delayMicroseconds(3);
digitalWrite(pin_pulse, LOW);
delayMicroseconds(3);
}
int val = analogRead(pin_cap);
minval = min(val, minval);
maxval = max(val, maxval);
sum += val;
long unsigned int timestamp =
millis();
byte ledstat = 0;
if (timestamp < prev_flash +12)
{
if (diff > 0)ledstat = 1;
if (diff < 0)ledstat = 2;
}
if (timestamp > prev_flash +
flash_period) {
if (diff > 0)ledstat = 1;
if (diff < 0)ledstat = 2;
prev_flash = timestamp;
}
if (flash_period > 1000)
ledstat = 0;
if (ledstat = = 0) {
digitalWrite(pin_LED, LOW);
}
if (ledstat == 1) {
digitalWrite(pin_LED, LOW);
}
if (ledstat == 2) {
digitalWrite(pin_LED, HIGH);
}
}
sum -= minval; sum -= maxval;
if (sumsum == 0) sumsum = sum
<< 6;
long int avgsum = (sumsum + 32)
>> 6;
diff = sum - avgsum;
if (abs(diff)<avgsum >> 10) {
sumsum = sumsum + sum -
avgsum;
skip = 0;
} else {
skip++;
}
if (skip > 64) {
sumsum = sum << 6;
skip = 0;
}
if (diff == 0) flash_period =
1000000;
else flash_period = avgsum / (2 *
abs(diff));
}