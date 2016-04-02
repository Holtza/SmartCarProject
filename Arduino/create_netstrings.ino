/*
 * This sketch turns a number of int values into a netstring, and prints it to terminal.
 * To be integrated with the actual sensor output, for communication between Arduino and proxy.
 */
 
int us1 = 5;
int us2 = 20;
int ir1 = 8;
int ir2 = 12;
int ir3 = 11;

void setup() {
  Serial.begin(9600);

}

void loop() {

  String valueString = setString(us1, us2, ir1, ir2, ir3);
  //Serial.println(valueString);

  String encodedString = encodeNetstring(valueString);
  Serial.println(encodedString);
  

}

//Method for turning int values into a string
String setString(int i_1, int i_2, int i_3, int i_4, int i_5){
 String s1 = String(i_1);
 String s2 = String(i_2);
 String s3 = String(i_3);
 String s4 = String(i_4);
 String s5 = String(i_5);

 String valueS = s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5;

 return valueS;
}

String encodeNetstring(String string){
  int len = string.length();
  if (len <= 0) return "empty";
  return len + String(":" + string + ",");
}

