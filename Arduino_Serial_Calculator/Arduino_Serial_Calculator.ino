float a;
 float b;

char calSignal;
void setup() {
 
  Serial.begin(2000000);
  Serial.println("Enter the Calculation");
  while (Serial.available()==0){}                    
  a = Serial.parseInt(); 
  Serial.print(a);
  calSignal = Serial.read();
  Serial.print(calSignal);
  b = Serial.parseInt();
  Serial.print(b);
  Serial.println(" ");

  Serial.print(solve(a,b),5);
  Serial.println("");
  Serial.println("To Do Another Calculation Press The Red Reset Button!");
}
float solve(float a,float b) { 
  
  float result;
  switch (calSignal) {

    case '+' : 
    result = a + b; 
    return result;
 
    break; 
    case '-' : 
    result = a - b; 
    return result;
    
    break; 
    case 'x' : 
    result = a * b;
    return result; 
    
    break; 
    case '/' : 
    result = a / b;
    return result;
    break; 
    
    case '*' : 
    result = a * b;
    return result; 
    
    break; 
    
    case '.' : 
    result = a * b;
    return result; 
    
    break;
    
    
    default : 
    Serial.println("What was that? Invalid Operator");
  }
}
void loop() {

   
   
  
}
