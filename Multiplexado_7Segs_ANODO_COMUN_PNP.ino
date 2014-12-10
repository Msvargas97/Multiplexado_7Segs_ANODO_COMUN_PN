const unsigned int a=5,b=4,c=17,d=18,e=19,f=3,g=2;
#define CA1 6
#define CA2 7
#define CA3 15
#define CA4 16

int BotonIncremento=8;//botón de incremento 
int BotonDecremento=14;//botón de decremento
int timeAntirebote=15;//un valor entre 10 y 15 nos da una lectura correcta del estado del botón.

int cuenta=0;//lleva la cuenta
int EstadoBotonIncremento;
int EstadoBotonDecremento;
int EstadoBotonAnteriorIncremento;
int EstadoBotonAnteriorDecremento;
const int segs[7] = { 
  5, 4, 17, 18, 19, 3, 2 };
const byte numbers[10] = { 
  0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};


int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;
int time=4600;
//Función Antirebote
boolean antirebote(int pin){//esta función nos va a devolver un valor booleano.
  int contador=0;
  boolean estado; //guarda el estado del botón
  boolean estadoAnterior;//guarda el último estado del botón

  do {
    estado=digitalRead(pin);
    if (estado==1){ // invierte los valores debido a la resistencias PulluP

      estado=0;
    }
    else{
      estado=1; 
    }
    if (estado != estadoAnterior){
      contador=0;
      estadoAnterior = estado;
    }
    else{
      contador = contador + 1;
    }
    delayMicroseconds(1000);
  }

  while(contador < timeAntirebote);
  return estado;
} 
void setup() {

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
  pinMode(CA3, OUTPUT);
  pinMode(CA4, OUTPUT);
  pinMode(BotonIncremento,INPUT);//los botones los declaramos como entradas
  pinMode(BotonDecremento,INPUT);
  digitalWrite(BotonIncremento, HIGH); // activa Resistencia pull up
  digitalWrite(BotonDecremento, HIGH); // activa RPA 
  //Serial.begin(9600);

}
boolean inicio=false;
void loop() {

  EstadoBotonIncremento=digitalRead(BotonIncremento);//leemos el botón
  if((EstadoBotonIncremento !=EstadoBotonAnteriorIncremento) &&(antirebote(BotonIncremento))){//preguntamos si hay cambio respecto al estado anterior y vemos si esta presionado
    cuenta++;//aumentamos la cuenta
    if(cuenta>9999){//aquí establecí un parámetro para respetar a la cuenta por asi llamarlo.
      cuenta=0;//en este caso si es mayor que 9999 se vaya a cero (0).
    }
  }
  EstadoBotonAnteriorIncremento = EstadoBotonIncremento;//guardamos el estado del botón

  //Botón de Decremento.
  EstadoBotonDecremento=digitalRead(BotonDecremento);//leemos el estado del botón
  if((EstadoBotonDecremento != EstadoBotonAnteriorDecremento)&&(antirebote(BotonDecremento))){
    cuenta--;//disminuimos la cuenta
    if(cuenta<0){
      cuenta=9999;
    }
  }
  EstadoBotonAnteriorDecremento = EstadoBotonDecremento;


  if( inicio == false ){
    iniciar();
    inicio=true;
  }
  else {
    digit1=cuenta / 1000;    // formula para hallar digitos
    digit2=(cuenta  / 100) % 10 ;
    digit3=(cuenta / 10 ) % 10 ;
    digit4=cuenta % 10;
  }
  lightDigit1(numbers[digit1]);
  delayMicroseconds(time);
  lightDigit2(numbers[digit2]);
  delayMicroseconds(time);
  lightDigit3(numbers[digit3]);
  delayMicroseconds(time);
  lightDigit4(numbers[digit4]);
  delayMicroseconds(time);
}

void lightDigit1(byte number) {
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, HIGH);
  lightSegments(number);
}

void lightDigit2(byte number) {
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, LOW);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, HIGH);
  lightSegments(number);
}

void lightDigit3(byte number) {
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, LOW);
  digitalWrite(CA4, HIGH);
  lightSegments(number);
}

void lightDigit4(byte number) {
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, LOW);
  lightSegments(number);
}

void lightSegments(byte number) {
  for (int i = 0; i < 7; i++) {
    int bit = bitRead(number, i);
    digitalWrite(segs[i], bit);
  }
}


void display (int a, int b, int c, int d, int e, int f, int g)// Función del display
{

  digitalWrite (5,a);   
  digitalWrite (4,b);   
  digitalWrite (17,c);
  digitalWrite (18,d);
  digitalWrite (19,e);
  digitalWrite (3,f);
  digitalWrite (2,g);
}


void iniciar(){


  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, LOW);
  display(1,1,1,0,1,1,1);
  delay(120);
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, LOW);
  digitalWrite(CA4, HIGH);
  display(1,1,1,0,1,1,1);
  delay(120);
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, LOW);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, HIGH);
  display(1,1,1,0,1,1,1);
  delay(120);
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, HIGH);
  display(1,1,1,0,1,1,1);
  delay(120);
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, HIGH);
  display(1,1,1,1,0,1,1);
  delay(120);
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, HIGH);
  display(1,1,1,1,1,0,1);
  delay(120);
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, HIGH);
  display(0,1,1,1,1,1,1);
  delay(120);
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, LOW);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, HIGH);
  display(0,1,1,1,1,1,1);
  delay(120);
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, LOW);
  digitalWrite(CA4, HIGH);
  display(0,1,1,1,1,1,1);
  delay(120);
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
  digitalWrite(CA4, LOW);
  display(0,1,1,1,1,1,1);
  delay(120); 
}


