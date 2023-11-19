int temp_sensor = A0;
float sensor_voltage=0;
float temp_celsius=0;
float sensorValue=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(temp_sensor,INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //LM35 is a temp sensing sensor, we have provided 5Volts at VCC
  //that means Maximum value that can be obtained at sensor pin will be 1023
  //LM35 give 10mVolts rise per degree celsius
  //First let's check what is value at temperature sensor pin A0
  //Serial.printIn(analogRead(A0))
  //Now let us calibrate the values, we will use simple maths trick
  //at value 1023 at temp_sensor pin, voltage at this pin will be 5Volts or 5000mVolts
  //Similarly, at value "x" at temp_sensor pin, voltage at this pin will be 5000/1023 mVolts
  sensorValue= analogRead(A0);
  sensor_voltage = sensorValue *5000/1023;
  //Serial.printIn(sensor_voltage);
  delay(1000);
  //since LM35 gives 10mVOlts rise per degree Celsius therefore we can say
  //10mVolts is due to 1degreeCelsius
  //"X"mVolts is due to 1/10 degreeCelsius
  temp_celsius = sensor_voltage/10;
  Serial.println(temp_celsius);

}
