 /*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Electronica
 * Grado: Quinto
 * Sección: A
 * Curso: Taller de electronica digital y reparación de computadoras I
 * Nombre: Juan Manuel Sebastián Ixen Coy
 * Carnet: 2019519
 * Proyecto: Practica 1, parte 2
*/
#include <Ticker.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

#define Boton 3

volatile static bool Estado_Sensor;

void IRS_Boton();
void IRS_Temperatura();
void Actualizar();

Ticker IRS_Accion_Sensor    (IRS_Temperatura, 3000);
Ticker IRS_Accion_Boton(IRS_Boton, 6000);
OneWire ourWire(2);
DallasTemperature Sensor(&ourWire); 

void setup() 
{
  Serial.begin(9600);
  Sensor.begin();
  pinMode(Boton, INPUT);
  IRS_Accion_Sensor.start();
  IRS_Accion_Boton.start();
  Serial.println("Inicia el programa");
} 
void loop() 
{
 Actualizar();
}
void IRS_Boton(){
  Estado_Sensor = digitalRead(Boton);
  if(Estado_Sensor == HIGH)
{
  Serial.println("Boton Presionado");
}
  if(Estado_Sensor == LOW)
{
  Serial.println("Boton sin precionar");
}
}
void Actualizar()
{
 IRS_Accion_Sensor.update(); 
 IRS_Accion_Boton.update();
} 
void IRS_Temperatura()
{
  Sensor.requestTemperatures();
  int Temperatura_C = Sensor.getTempCByIndex(0);
  Serial.print("    ");  
  Serial.print("La temperatura es de:");  
  Serial.print(Temperatura_C);
  Serial.print("C");  
  Serial.println("     "); 
}
