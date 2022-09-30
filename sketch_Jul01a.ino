#include <ESP8266WiFi.h>
#include <DHT.h>
#define PIN_DHT 2

const char* ssid = "noname";
const char* password = "noname";


WiFiServer server(80); //NODE MCU를 서버로 사용하겠다 // 포트번호는 80
WiFiClient client;
DHT DHTsensor(PIN_DHT, DHT11);


void setup() { // put your setup code here, to run once:
  DHTsensor.begin();
  Serial.begin(115200);
  delay(100);
  pinMode(14, OUTPUT); //쿨링
  pinMode(12, OUTPUT); //내부 LED
  pinMode(13, OUTPUT); //스탠드
  pinMode(15, OUTPUT); //컴퓨터 파워
  pinMode(4, INPUT_PULLUP); //파워 버튼
  Serial.println();
  Serial.print("CONNECTING TO ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); // 와이파이 이름과 비밀번호를 통해 WIFI연결을 시작하겠다
  // WL_CONNECTED라는 값을 돌려준다
  while (WiFi.status() != WL_CONNECTED) { // 네트워크의 연결 상태, 8개의 리턴값 / STATUS와 WL_CONNECTED 값이 같은지를 통해 제대로 연결이 되있는지를 확인할 수 있다
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi connected!");
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //서버 IP주소를 알려준다. 브라우저의 주소란에 치면 NODE MCU가 서버로 있는 것으로 접근할 수 있다.
  Serial.println("/");
  Serial.println("");
}
int green = LOW;
int red = LOW;
int blue = LOW;
int pw = LOW;
int t = 0;
void loop() { // put your main code here, to run repeatedly:
  //WiFiClient client = server.available();
  client = server.available();
  //Serial.println(digitalRead(4));
  if (digitalRead(4)== LOW){
    digitalWrite(15, HIGH);
    delay(200);
    digitalWrite(15, LOW);
    delay(200);
  }
  if (!client) {
    return;
  }
  Serial.println("new client");
  //  client.setTimeout(5000);
  // String request = client.readStringUntil('\r');
  //  Serial.println("request: ");
  //  Serial.println(request);
  String request = client.readStringUntil('\r'); // \r 명령어, 즉 줄 바꿈 명령어가 나오기 전까지 계속 데이터를 읽어라
  Serial.println(request);
  while (client.available()) {
    client.read();
  }
  //  while (!client.available()) {
  //    delay(1);
  //  } //서버와 연결된 클라이언트가 있으면 다음으로 넘어가라

  //client.flush(); //버퍼에 남은것을 없애라

  float humidity = DHTsensor.readHumidity();
  float temp = DHTsensor.readTemperature();
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.print(" Temperature : ");
  Serial.print(temp);
  Serial.println(" ºC");

  if (request.indexOf("/green=ON") != -1) {
    digitalWrite(12, HIGH);
    green = HIGH;
  } // 읽어들인 문자에 /LED=ON 이 있는지 없는지 확인하라, (즉 /LED=ON 이 -1 인 상태)
  //그리고 digitalWrite에 적용되는 핀에 맞추어서 값을 HIGH로 가져라 ==> 불을 켜라
  if (request.indexOf("/green=OFF") != -1) {
    digitalWrite(12, LOW);
    green = LOW;
  } // // 읽어들인 문자에 /LED=OFF 이 있는지 없는지 확인하라, (즉 /LED=OFF 이 -1 인 상태)

  if (request.indexOf("/red=ON") != -1) {
    digitalWrite(14, HIGH);
    red = HIGH;
  } // 읽어들인 문자에 /LED=ON 이 있는지 없는지 확인하라, (즉 /LED=ON 이 -1 인 상태)
  //그리고 digitalWrite에 적용되는 핀에 맞추어서 값을 HIGH로 가져라 ==> 불을 켜라
  if (request.indexOf("/red=OFF") != -1) {
    digitalWrite(14, LOW);
    red = LOW;
  } // // 읽어들인 문자에 /LED=OFF 이 있는지 없는지 확인하라, (즉 /LED=OFF 이 -1 인 상태)

  if (request.indexOf("/blue=ON") != -1) {
    digitalWrite(13, HIGH);
    blue = HIGH;
  } // 읽어들인 문자에 /LED=ON 이 있는지 없는지 확인하라, (즉 /LED=ON 이 -1 인 상태)
  //그리고 digitalWrite에 적용되는 핀에 맞추어서 값을 HIGH로 가져라 ==> 불을 켜라
  if (request.indexOf("/blue=OFF") != -1) {
    digitalWrite(13, LOW);
    blue = LOW;
  } // // 읽어들인 문자에 /LED=OFF 이 있는지 없는지 확인하라, (즉 /LED=OFF 이 -1 인 상태)
  if (request.indexOf("/pw=ON") != -1) {
    digitalWrite(15, HIGH);
    pw = HIGH;
  } // 읽어들인 문자에 /LED=ON 이 있는지 없는지 확인하라, (즉 /LED=ON 이 -1 인 상태)
  //그리고 digitalWrite에 적용되는 핀에 맞추어서 값을 HIGH로 가져라 ==> 불을 켜라
  if (request.indexOf("/pw=OFF") != -1) {
    digitalWrite(15, LOW);
    pw = LOW;
  } // // 읽어들인 문자에 /LED=OFF 이 있는지 없는지 확인하라, (즉 /LED=OFF 이 -1 인 상태)






  //읽어들인 문자에 /LED=ON 이 있는지 없는지 확인하라, (즉 /LED=ON 이 -1 인 상태)
  //그리고 digitalWrite에 적용되는 핀에 맞추어서 값을 HIGH로 가져라 ==> 불을 켜라
  //  if (request.indexOf("/pw=OFF") != -1) {
  //    digitalWrite(15, LOW);
  //    pw = LOW;
  //  } // // 읽어들인 문자에 /LED=OFF 이 있는지 없는지 확인하라, (즉 /LED=OFF 이 -1 인 상태)

  //그리고 digitalWrite에 적용되는 핀에 맞추어서 값을 LOW로 가져라 ==> 불을 꺼라
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type : text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("<head>");
  client.print("<meta charset=\"UTF-8\" http-equiv=\"refresh\" content=\"1\">");
  client.print("<title>All in One Smart Desktop System</title>");
  client.print("</head>");
  client.print("<body>");
  client.print("<h2>All in One Smart Desktop System</h2>");
  client.print("<br>");
  client.print("Desktop's Temperature : ");
  client.print(temp);
  client.print(" °C");
  client.print("<br>");
  client.print("Desktop's Humidity : ");
  client.print(humidity);
  client.print(" %");
  client.print("</body>");
  client.println("<br><br>");

  client.println(" Computer power System ");
  if (pw == HIGH) client.println("On");
  else if (pw == LOW) client.print("Off");

  client.println("<br><br>");
  client.println("<a href = \"/pw=ON\"\"><button>ON</button></a>");
  client.println("<a href = \"/pw=OFF\"\"><button>OFF</button></a>");

  // client.println("<a href=\"/BLINK=on\"\"><button>BLINK</button></a>");

  client.println("<br><br>");
  client.println("Stand Light Power ");

  if (green == HIGH) client.println("On");
  else if (green == LOW) client.print("Off");

  client.println("<br><br>");
  client.println("<a href = \"/green=ON\"\"><button>ON</button></a>");
  client.println("<a href = \"/green=OFF\"\"><button>OFF</button></a>");

  client.println("<br><br>");
  client.println("Cooling System ");

  if (red == HIGH) client.println("On");
  else if (red == LOW) client.print("Off");

  client.println("<br><br>");
  client.println("<a href = \"/red=ON\"\"><button>ON</button></a>");
  client.println("<a href = \"/red=OFF\"\"><button>OFF</button></a>");

  client.println("<br><br>");
  client.println(" Computer Iight System ");

  if (blue == HIGH) client.println("On");
  else if (blue == LOW) client.print("Off");

  client.println("<br><br>");
  client.println("<a href = \"/blue=ON\"\"><button>ON</button></a>");
  client.println("<a href = \"/blue=OFF\"\"><button>OFF</button></a>");

  client.println("</html>"); //HTML로 서버에 버튼을 생성하고 사이트를 만들어라 delay(1);

  Serial.println(client.connect("http://newsky2.kma.go.kr/service/SecndSrtpdFrcstInfoService2/ForecastSpaceData?serviceKey=VlJoz90r6QOqEXPQIwP0jdLqCtgkQbgXo%2Fy0L%2B4x6z6VjH5LPx3RPYAH4RAJmaqSWCh7BM7s5KCSDPR5s%2F27Lg%3D%3D&base_date=20190704&base_time=0500&nx=60&n=127&numOfRows=10&pageNo=1&_type=xml", 8));
  Serial.println("Client disconnected !! ");
  Serial.println();
}
