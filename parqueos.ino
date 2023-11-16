#include <WiFi.h> //Librería para manejar el Wifi
#include <WiFiClient.h> //Librería para manejar Clientes
#include <WebServer.h> //Librería para manejar el servidor
#include <ESPmDNS.h> //Librería para asegurarse que la IP no cambie

#define RX_PIN 16  // Puedes cambiar estos pines según tu conexión
#define TX_PIN 17

byte pin[] = {15,2,4,5,18,19,21};  
//byte pin[] = {23,24,26,29,30,31,33};  

const byte count[10] = {  // this is data code for Seven segment 
  //GFEDCBA
  B00111111,  //0
  B00000110, // 1
  B01011011, // 2
  B01001111, //3
  B01100110, //4
  B01101101, //5
  B01111101, //6
  B00000111, //7
  B01111111, //8
  B01101111, //9
};

const char* ssid = "iPhone de Gabriel"; //Nombre de la red
const char* password = "GaryCipri7"; //Contraseña
char tiva1; //Variable para recibir del serial de la tiva 1
char tiva2; //Variable para recibir del serial de la tiva 2

WebServer server(80); //Definimos objeto para la librería Webserver en el puerto 80 ya con ese hace el request de http

//Variables booleanas para los parqueos
bool parqueo1 = false;
bool parqueo2 = false;
bool parqueo3 = false;
bool parqueo4 = false;
bool parqueo5 = false;
bool parqueo6 = false;
bool parqueo7 = false;
bool parqueo8 = false;

//Variables enteras para los totales de los parqueos
uint8_t s1;
uint8_t s2;
uint8_t s3;
uint8_t s4;
uint8_t s5;
uint8_t s6;
uint8_t s7;
uint8_t s8;
uint8_t park1;
uint8_t park2;
uint8_t disponibles;

//Función para que cuando se este en la pagina principal se ejecute la siguiente función
void handleRoot() {
  server.send(200, "text/html", HTML()); //Código de la página web
}

//Función que llama javascript para que cuando se este en la pagina principal se ejecute la siguiente función
void handleColor1(){
  if (parqueo1 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta vacío enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor2(){
  if (parqueo2 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor3(){
  if (parqueo3 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor4(){
  if (parqueo4 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor5(){
  if (parqueo5 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor6(){
  if (parqueo6 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor7(){
  if (parqueo7 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

void handleColor8(){
  if (parqueo8 == false) {
    server.send(200, "text/plain", "parking-spot vacant"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  } else {
    server.send(200, "text/plain", "parking-spot occupied"); //Si el parqueo esta ocupado enviar un texto a javascript con la clase de css en HTML para asignarle al id correspondiente
  }
}

//Funcion a llamar si el cliente escribe una direccion que no existe
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200); //Iniciar comunicación serial para ver en la terminal
  Serial1.begin(115200, SERIAL_8N1, 32, 33, false, 20000UL, 112); //Habilitar el UART1 y cambiar los pins
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN); // Inicializar UART2 con baudrate de 9600

  pinMode(pin[0], OUTPUT);  // every pin is output
  pinMode(pin[1], OUTPUT);
  pinMode(pin[2], OUTPUT);
  pinMode(pin[3], OUTPUT);
  pinMode(pin[4], OUTPUT);
  pinMode(pin[5], OUTPUT);
  pinMode(pin[6], OUTPUT);

  WiFi.mode(WIFI_STA); //Wifi como station mode para unirse a una red que ya existe
  WiFi.begin(ssid, password); //Iniciar la conexión 
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //Escribir la IP para acceder a la página

  //Iniciar multi DNS
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  //Definir las funciones a llamar cuando se haga el request de ciertas direcciones
  server.on("/", handleRoot);
  server.on("/l1", handleColor1);
  server.on("/l2", handleColor2);
  server.on("/l3", handleColor3);
  server.on("/l4", handleColor4);
  server.on("/l5", handleColor5);
  server.on("/l6", handleColor6);
  server.on("/l7", handleColor7);
  server.on("/l8", handleColor8);

  server.onNotFound(handleNotFound); //Cuando se pida una direccion inexistente llamar a la funcion indicada

  server.begin(); //Iniciar el servidor
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient(); //Mantener el servidor 
  check_tiva1(); //Llamar a función para revisar los parqueos de la tiva 1
  check_tiva2(); //Llamar a función para revisar los parqueos de la tiva 2
  check(); //Llamar para poder realizar suma de los parqueos
  park1 = s1 + s2 + s3 + s4; //Suma de parqueos en sotano 1
  park2 = s5 + s6 + s7 + s8; //Suma de parqueos en sotano 2
  disponibles = s1 + s2 + s3 + s4 + s5 + s6 + s7 +s8; //Suma de disponibles totales
  SevenSeg(count[8-disponibles]);
  //Serial.println(String(8-disponibles));
}

void SevenSeg(byte Bit) { //  sending data on each pin
  for(int i=0; i<8; i++)
  digitalWrite(pin[i],bitRead(Bit,i));
}

//Código HTML, CSS y Javascript para la página WEB
String HTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<meta charset=\"UTF-8\">\n";
  ptr +="<title>PARQUEOS</title>\n";
  ptr +="  <style>\n";
  ptr +="    /* CSS Styling */\n";
  ptr +="    body {\n";
  ptr +="      font-family: Arial, sans-serif;\n";
  ptr +="      background-color: #333;\n";
  ptr +="      color: #fff;\n";
  ptr +="      margin: 0;\n";
  ptr +="      padding: 20px;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    h1 {\n";
  ptr +="      text-align: center;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .parking-lot {\n";
  ptr +="      display: flex;\n";
  ptr +="      justify-content: center;\n";
  ptr +="      flex-wrap: wrap;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .parking-spot {\n";
  ptr +="      width: 100px;\n";
  ptr +="      height: 100px;\n";
  ptr +="      border-radius: 5px;\n";
  ptr +="      margin: 10px;\n";
  ptr +="      display: flex;\n";
  ptr +="      align-items: center;\n";
  ptr +="      justify-content: center;\n";
  ptr +="      font-size: 24px;\n";
  ptr +="      font-weight: bold;\n";
  ptr +="      cursor: pointer;\n";
  ptr +="      transition: background-color 0.3s ease;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .vacant {\n";
  ptr +="      background-color: #34c759;\n";
  ptr +="    }\n";
  ptr +="\n";
  ptr +="    .occupied {\n";
  ptr +="      background-color: #ff3b30;\n";
  ptr +="    }\n";
  ptr +="  </style>\n";
  ptr +="</head>\n";
  ptr +="<body onload=\"process()\">\n";
  ptr +="  <h1>PARQUEOS</h1>\n";
  ptr +="\n";
  ptr +="  <div class=\"parking-lot\">\n";
  ptr +="<div id=\"spot1\" class=\"parking-spot\">Parqueo 1</div>\n";
  ptr +="<div id=\"spot2\" class=\"parking-spot\">Parqueo 2</div>\n";
  ptr +="<div id=\"spot3\" class=\"parking-spot\">Parqueo 3</div>\n";
  ptr +="<div id=\"spot4\" class=\"parking-spot\">Parqueo 4</div>\n";
  ptr +="<div id=\"spot5\" class=\"parking-spot\">Parqueo 5</div>\n";
  ptr +="<div id=\"spot6\" class=\"parking-spot\">Parqueo 6</div>\n";
  ptr +="<div id=\"spot7\" class=\"parking-spot\">Parqueo 7</div>\n";
  ptr +="<div id=\"spot8\" class=\"parking-spot\">Parqueo 8</div>\n";
  ptr +="  </div>\n";
  ptr +="\n";
  ptr +="<script>\n";
  ptr +="function updateColor1() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot1').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l1', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor1, 500);}\n";

  ptr +="function updateColor2() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot2').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l2', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor2, 500);}\n";

  ptr +="function updateColor3() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot3').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l3', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor3, 500);}\n";

  ptr +="function updateColor4() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot4').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l4', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor4, 500);}\n";

  ptr +="function updateColor5() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot5').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l5', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor5, 500);}\n";

  ptr +="function updateColor6() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot6').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l6', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor6, 500);}\n";

  ptr +="function updateColor7() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot7').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l7', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor7, 500);}\n";

  ptr +="function updateColor8() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById('spot8').className = this.responseText;\n";
  ptr +="}\n";
  ptr +="};\n";
  ptr +="xhttp.open('GET', '/l8', true);\n";
  ptr +="xhttp.send();\n";
  ptr +="setTimeout(updateColor8, 500);}\n";

  ptr +="updateColor1();\n";
  ptr +="updateColor2();\n";
  ptr +="updateColor3();\n";
  ptr +="updateColor4();\n";
  ptr +="updateColor5();\n";
  ptr +="updateColor6();\n";
  ptr +="updateColor7();\n";
  ptr +="updateColor8();\n";
  ptr +="</script>\n";
  
  ptr +="</body>\n";
  ptr +="</html>";
  return ptr;
}

//Función para chequear la información de la Tiva1
void check_tiva1(){
  tiva1 = Serial2.read(); //Leer de UART2

  //Chequear para los parqueos
  if (tiva1 == '0'){
    parqueo1 = false;
    parqueo2 = false;
    parqueo3 = false;
    parqueo4 = false;
  }
  else if (tiva1 == 'A'){
    parqueo1 = true;
    parqueo2 = false;
    parqueo3 = false;
    parqueo4 = false;
  }
  else if (tiva1 == 'B'){
    parqueo1 = false;
    parqueo2 = true;
    parqueo3 = false;
    parqueo4 = false;
  }
  else if (tiva1 == 'C'){
    parqueo1 = true;
    parqueo2 = true;
    parqueo3 = false;
    parqueo4 = false;
  }
  else if (tiva1 == 'D'){
    parqueo1 = false;
    parqueo2 = false;
    parqueo3 = true;
    parqueo4 = false;
  }
  else if (tiva1 == 'E'){
    parqueo1 = true;
    parqueo2 = false;
    parqueo3 = true;
    parqueo4 = false;
  }
  else if (tiva1 == 'F'){
    parqueo1 = false;
    parqueo2 = true;
    parqueo3 = true;
    parqueo4 = false;
  }
  else if (tiva1 == 'G'){
    parqueo1 = true;
    parqueo2 = true;
    parqueo3 = true;
    parqueo4 = false;
  }
  else if (tiva1 == 'H'){
    parqueo1 = false;
    parqueo2 = false;
    parqueo3 = false;
    parqueo4 = true;
  }
  else if (tiva1 == 'I'){
    parqueo1 = true;
    parqueo2 = false;
    parqueo3 = false;
    parqueo4 = true;
  }
  else if (tiva1 == 'J'){
    parqueo1 = false;
    parqueo2 = true;
    parqueo3 = false;
    parqueo4 = true;
  }
  else if (tiva1 == 'K'){
    parqueo1 = true;
    parqueo2 = true;
    parqueo3 = false;
    parqueo4 = true;
  }
  else if (tiva1 == 'L'){
    parqueo1 = false;
    parqueo2 = false;
    parqueo3 = true;
    parqueo4 = true;
  }
  else if (tiva1 == 'M'){
    parqueo1 = true;
    parqueo2 = false;
    parqueo3 = true;
    parqueo4 = true;
  }
  else if (tiva1 == 'N'){
    parqueo1 = false;
    parqueo2 = true;
    parqueo3 = true;
    parqueo4 = true;
  }
  else if (tiva1 == 'O'){
    parqueo1 = true;
    parqueo2 = true;
    parqueo3 = true;
    parqueo4 = true;
  }
}

void check_tiva2(){
  tiva2 = Serial1.read(); //Leer del UART1

  //Chequear para los parqueos
  if (tiva2 == 0){
    parqueo5 = false;
    parqueo6 = false;
    parqueo7 = false;
    parqueo8 = false;
  }
  else if (tiva2 == 1){
    parqueo5 = true;
    parqueo6 = false;
    parqueo7 = false;
    parqueo8 = false;
  }
  else if (tiva2 == 2){
    parqueo5 = false;
    parqueo6 = true;
    parqueo7 = false;
    parqueo8 = false;
  }
  else if (tiva2 == 3){
    parqueo5 = true;
    parqueo6 = true;
    parqueo7 = false;
    parqueo8 = false;
  }
  else if (tiva2 == 4){
    parqueo5 = false;
    parqueo6 = false;
    parqueo7 = true;
    parqueo8 = false;
  }
  else if (tiva2 == 5){
    parqueo5 = true;
    parqueo6 = false;
    parqueo7 = true;
    parqueo8 = false;
  }
  else if (tiva2 == 6){
    parqueo5 = false;
    parqueo6 = true;
    parqueo7 = true;
    parqueo8 = false;
  }
  else if (tiva2 == 7){
    parqueo5 = true;
    parqueo6 = true;
    parqueo7 = true;
    parqueo8 = false;
  }
  else if (tiva2 == 8){
    parqueo5 = false;
    parqueo6 = false;
    parqueo7 = false;
    parqueo8 = true;
  }
  else if (tiva2 == 9){
    parqueo5 = true;
    parqueo6 = false;
    parqueo7 = false;
    parqueo8 = true;
  }
  else if (tiva2 == 10){
    parqueo5 = false;
    parqueo6 = true;
    parqueo7 = false;
    parqueo8 = true;
  }
  else if (tiva2 == 11){
    parqueo5 = true;
    parqueo6 = true;
    parqueo7 = false;
    parqueo8 = true;
  }
  else if (tiva2 == 12){
    parqueo5 = false;
    parqueo6 = false;
    parqueo7 = true;
    parqueo8 = true;
  }
  else if (tiva2 == 13){
    parqueo5 = true;
    parqueo6 = false;
    parqueo7 = true;
    parqueo8 = true;
  }
  else if (tiva2 == 14){
    parqueo5 = false;
    parqueo6 = true;
    parqueo7 = true;
    parqueo8 = true;
  }
  else if (tiva2 == 15){
    parqueo5 = true;
    parqueo6 = true;
    parqueo7 = true;
    parqueo8 = true;
  }
}

//Función para las sumas
void check(){
  //Revisar si están ocupados los parqueos
  if (parqueo1 == true){
    s1 = 1;
  }
  else{
    s1 = 0;
  }
  if (parqueo2 == true){
    s2 = 1;
  }
  else{
    s2 = 0;
  }
  if (parqueo3 == true){
    s3 = 1;
  }
  else{
    s3 = 0;
  }
  if (parqueo4 == true){
    s4 = 1;
  }
  else{
    s4 = 0;
  }
  if (parqueo5 == true){
    s5 = 1;
  }
  else{
    s5 = 0;
  }
  if (parqueo6 == true){
    s6 = 1;
  }
  else{
    s6 = 0;
  }
  if (parqueo7 == true){
    s7 = 1;
  }
  else{
    s7 = 0;
  }
  if (parqueo8 == true){
    s8 = 1;
  }
  else{
    s8 = 0;
  }
}
