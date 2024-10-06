/*
 Author: Ignazio Leonardo Calogero Sperandeo
 Date: 25/08/2024
 Project Name: PPSv2
 Repo: https://github.com/jim-bug/PPS/tree/pps-v2
 
 by jim_bug // :)
*/


#include <WiFi.h>

#define LEN 4
#define START_PIN 16
#define END_PIN 19
#define CONNECT_TIME 10000
#define TIMEOUTTIME 5000
#define PORT 5544

const char* ssid = "";
const char* password = "";
WiFiServer server(5544);       // Server will work on 5544 port.
String header;

size_t currentTime = millis();
size_t previousTime = 0;
int socketPin[LEN];
int socketStatus[LEN];

void setup(){
    Serial.begin(115200);
    Serial.print("Attemption to connect to ");
    Serial.print(ssid);
    WiFi.begin(ssid, password);

    size_t start_time = millis();
    size_t dot_time = millis();
    while ((WiFi.status() != WL_CONNECTED) && (start_time + CONNECT_TIME) > millis()) {
        if (dot_time + 250 < millis()) {
            Serial.print(".");
            dot_time = millis();
        }
    }
    if(WiFi.status() != WL_CONNECTED){
        Serial.print("Connection failed, please try again!");
        while(1);
    }
    Serial.println();
    Serial.print("ESP32 is connected with: ");
    Serial.println(ssid);
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("ESP32 PORT: ");
    Serial.println(PORT);


    for(int i = START_PIN; i <= END_PIN; i++){
        pinMode(i, OUTPUT);
        socketStatus[i-START_PIN] = 1;
        digitalWrite(i, HIGH);
    }

    server.begin();
}
void loop(){
    WiFiClient client = server.available();

    if(client){
        currentTime = millis();
        previousTime = currentTime;
        Serial.println("New client is connected");
        String currentLine = "";

        while(client.connected() && currentTime - previousTime <= TIMEOUTTIME){     // se la connessione è chiusa, senza ricezione di dati
            currentTime = millis();
            if(client.available()){
                char c = client.read();
                Serial.write(c);
                header += c;
                if(c == '\n'){
                    if(currentLine.length() == 0){
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();


                        for(int i = START_PIN; i <= END_PIN;i++){
                            if(header.indexOf("GET /socket/"+ String(i-START_PIN)) >= 0){
                                Serial.println("Socket " + String(i-START_PIN) + " has changed state!");
                                socketStatus[i-START_PIN] = !socketStatus[i-START_PIN];
                                digitalWrite(i, socketStatus[i-START_PIN]);
                            }
                        }

                        client.println("<!DOCTYPE html>");
                        client.println("<html>");
                        client.println("<head>");
                        client.println("<meta charset=\"UTF-8\">");
                        client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                        client.println("<title>PPS-v2</title>");
                        client.println("<h1 align=\"center\">Particular Power Strip v2</h1>");
                        client.println("<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css\">");
                        client.println("");
                        client.println("<style>");
                        client.println(".presa-container {");
                        client.println("display: flex;");
                        client.println("justify-content: space-around;");
                        client.println("align-items: center;");
                        client.println("width: 100%;");
                        client.println("min-height: 50vh;");
                        client.println("}");
                        client.println("");
                        client.println(".presa {");
                        client.println("width: 100px;");
                        client.println("height: 200px;");
                        client.println("border: none;");
                        client.println("background-color: transparent;");
                        client.println("cursor: pointer;");
                        client.println("padding: 0;");
                        client.println("}");
                        client.println("");
                        client.println(".presa svg {");
                        client.println("width: 100%;");
                        client.println("height: 100%;");
                        client.println("}");
                        client.println(".copyright-section {");
                        client.println("background-color: #000;");
                        client.println("color: #fff;");
                        client.println("text-align: center;");
                        client.println("padding: 20px;");
                        client.println("}");
                        client.println("footer {");
                        client.println("background-color: #333;");
                        client.println("color: #fff;");
                        client.println("padding: 20px;");
                        client.println("text-align: center;");
                        client.println("position: relative;");
                        client.println("bottom: 0;");
                        client.println("width: 100%;");
                        client.println("min-height: 11vh;");
                        client.println("}");
                        client.println(".footer-content {");
                        client.println("display: flex;");
                        client.println("flex-direction: column;");
                        client.println("align-items: center;");
                        client.println("}");
                        client.println(".footer-content a {");
                        client.println("color: #1e90ff;");
                        client.println("text-decoration: none;");
                        client.println("margin: 0 5px;");
                        client.println("}");
                        client.println(".footer-content a:hover {");
                        client.println("text-decoration: underline;");
                        client.println("}");
                        client.println(".footer-content .github-icon {");
                        client.println("font-size: 2em;");
                        client.println("color: #fff;");
                        client.println("}");
                        client.println(".footer-content .license-info {");
                        client.println("margin-top: 10px;");
                        client.println("font-size: 0.9em;");
                        client.println("}");
                        client.println(".footer-content .license-info a {");
                        client.println("color: #1e90ff;");
                        client.println("}");
                        client.println(".container {");
                        client.println("display: grid;");
                        client.println("grid-template-columns: repeat(4, 1fr);");
                        client.println("gap: 50px; /* Spazio tra le celle */");
                        client.println("width: 80%; /* Larghezza della riga */");
                        client.println("max-width: 1200px;");
                        client.println("margin: 100px auto;");
                        client.println("}");
                        client.println(".cell {");
                        client.println("background-color: #000000;");
                        client.println("color: white;");
                        client.println("display: flex;");
                        client.println("justify-content: center;");
                        client.println("align-items: center;");
                        client.println("font-size: 1.2em;");
                        client.println("border-radius: 8px;");
                        client.println("box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);");
                        client.println("height: 50px; /* Altezza delle celle */");
                        client.println("}");
                        client.println("</style>");
                        client.println("</head>");
                        client.println("<body>");
                        client.println("<div class=\"presa-container\">");
                        client.println("<button class=\"presa\">");
                        client.println("</button>");
                        client.println("<button class=\"presa\">");
                        client.println("</button>");
                        client.println("<button class=\"presa\">");
                        client.println("</button>");
                        client.println("<button class=\"presa\">");
                        client.println("</button>");
                        client.println("</div>");
                        client.println("<div class=\"container\">");

                        for(int i = 0; i < LEN;i++){
                            if(socketStatus[i] == 1){
                                client.println("<div class=\"cell\"><p>OFF</p></div>");
                            }
                            else{
                                client.println("<div class=\"cell\"><p>ON</p></div>");
                            }
                        }

                        client.println("</div>");
                        client.println("<footer>");
                        client.println("<div class=\"footer-content\">");
                        client.println("<a href=\"https://github.com/jim-bug\" target=\"_blank\" rel=\"noopener noreferrer\">");
                        client.println("<i class=\"fab fa-github github-icon\"></i>");
                        client.println("</a>");
                        client.println("<div class=\"license-info\">");
                        client.println("<p>Distribuito sotto la <strong>Licenza GPL-v3</strong>. Per dettagli, consulta:<a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">LICENSE</a></p>");
                        client.println("</div>");
                        client.println("</div>");
                        client.println("</footer>");
                        client.println("</body>");
                        client.println("<script>");
                        client.println("const prese = document.querySelectorAll('.presa');");
                        client.println("prese.forEach((presa, index) => {");
                        client.println("const svg = document.createElementNS(\"http://www.w3.org/2000/svg\", \"svg\");");
                        client.println("svg.setAttribute('width', '100');");
                        client.println("svg.setAttribute('height', '200');");
                        client.println("svg.setAttribute('viewBox', '0 0 100 200');");
                        client.println("svg.setAttribute('xmlns', 'http://www.w3.org/2000/svg');");
                        client.println("");
                        client.println("// Add the SVG content from your provided code here");
                        client.println("svg.innerHTML = `");
                        client.println("<rect x=\"10\" y=\"10\" width=\"80\" height=\"180\" rx=\"10\" ry=\"10\" fill=\"#f0f0f0\" stroke=\"#000\" stroke-width=\"2\"/>");
                        client.println("");
                        client.println("<path d=\"M40,50 a10,15 0 1,0 20,0 a10,15 0 1,0 -20,0\" fill=\"#000\"/>");
                        client.println("");
                        client.println("<circle cx=\"50\" cy=\"100\" r=\"10\" fill=\"#000\" />");
                        client.println("");
                        client.println("<path d=\"M40,150 a10,15 0 1,0 20,0 a10,15 0 1,0 -20,0\" fill=\"#000\"/>");
                        client.println("`;");
                        client.println("");
                        client.println("presa.appendChild(svg);");
                        client.println("");
                        client.println("presa.addEventListener('click', () => {");
                        client.println("window.location.href = `/socket/${index}`;");
                        client.println("});");
                        client.println("});");
                        client.println("</script>");
                        client.println("");
                        client.println("</html>");
                        client.println();       // end of http response.

                        break;
                    } 
                    else{
                        currentLine = "";
                    }
                } 
                else if(c != '\r'){
                    currentLine += c;
                }
            }

        }
        header = "";
        client.stop();
        Serial.println("Client disconnected");
        Serial.println();
    }
}

// :)
