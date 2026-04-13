 * Author: mani123
 * For: Hack Club Highway to Undercity
 */

#include "esp_camera.h"
#include <WiFi.h>
#include <ESP32Servo.h>
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// =============================================
// WIFI CONFIG - CHANGE THESE
// =============================================
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// =============================================
// PIN DEFINITIONS
// =============================================
#define SOUND_PIN 4       // KY-038 D0
#define BUZZER_PIN 12     // Passive buzzer
#define SERVO_PIN 13      // SG90 signal

// LED Matrix (MAX7219)
#define LED_DIN 23
#define LED_CLK 18
#define LED_CS 5

// =============================================
// CAMERA PINS (AI-THINKER ESP32-CAM)
// =============================================
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

// =============================================
// BEHAVIOR SETTINGS
// =============================================
#define AWAKE_DURATION 60000     // Sleep after 60s of inactivity
#define MOTION_INTERVAL 500      // Check motion every 500ms
#define CLAP_TIMEOUT 1500        // 1.5s window to count claps
#define MOTION_THRESHOLD 30      // Motion sensitivity (lower = more sensitive)

// =============================================
// GLOBAL OBJECTS
// =============================================
Servo armServo;
WiFiServer server(80);
MD_Parola ledFace = MD_Parola(MD_MAX72XX::FC16_HW, LED_CS, 1);

// =============================================
// STATE VARIABLES
// =============================================
bool isAwake = false;
bool motionEnabled = true;
unsigned long wakeTime = 0;
unsigned long lastMotionCheck = 0;

// Clap detection state
int clapCount = 0;
unsigned long firstClapTime = 0;
unsigned long lastClapDetect = 0;

// =============================================
// HTML PAGE FOR WEB INTERFACE
// =============================================
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>JARVIS Jr.</title>
  <style>
    body { font-family: Arial, sans-serif; background: #1a1a2e; color: #eee; text-align: center; padding: 20px; }
    h1 { color: #00ff88; margin-bottom: 10px; }
    .subtitle { color: #888; margin-bottom: 30px; }
    .status { padding: 10px; margin: 10px; border-radius: 8px; background: #16213e; }
    .buttons { display: grid; grid-template-columns: 1fr 1fr; gap: 10px; max-width: 400px; margin: 20px auto; }
    button { padding: 20px; font-size: 18px; border: none; border-radius: 10px; cursor: pointer; transition: 0.2s; }
    .wave { background: #00ff88; color: #000; }
    .point { background: #ff6b6b; color: #000; }
    .photo { background: #4ecdc4; color: #000; }
    .sleep { background: #555; color: #fff; }
    button:active { transform: scale(0.95); }
    .cam-container { margin: 20px auto; max-width: 640px; }
    img { width: 100%; border-radius: 10px; border: 3px solid #00ff88; }
    .motion-toggle { margin: 20px; }
    .switch { position: relative; display: inline-block; width: 60px; height: 34px; }
    .switch input { opacity: 0; width: 0; height: 0; }
    .slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background: #555; border-radius: 34px; transition: 0.3s; }
    .slider:before { position: absolute; content: ""; height: 26px; width: 26px; left: 4px; bottom: 4px; background: #fff; border-radius: 50%; transition: 0.3s; }
    input:checked + .slider { background: #00ff88; }
    input:checked + .slider:before { transform: translateX(26px); }
    .footer { margin-top: 30px; color: #555; font-size: 12px; }
  </style>
</head>
<body>
  <h1>JARVIS Jr.</h1>
  <div class="subtitle">ESP32-CAM Desk Companion</div>
  
  <div class="status" id="status">
    <span id="state">Status: Loading...</span>
  </div>
  
  <div class="buttons">
    <button class="wave" onclick="fetch('/wave')">Wave</button>
    <button class="point" onclick="fetch('/point')">Point</button>
    <button class="photo" onclick="fetch('/photo')">Photo</button>
    <button class="sleep" onclick="fetch('/sleep')">Sleep</button>
  </div>
  
  <div class="motion-toggle">
    <span>Motion Detection:</span>
    <label class="switch">
      <input type="checkbox" id="motionToggle" checked onchange="toggleMotion()">
      <span class="slider"></span>
    </label>
  </div>
  
  <div class="cam-container">
    <img id="cam" src="" onerror="this.src='/cam?t='+Date.now()">
  </div>
  
  <div class="footer">
    Built for Hack Club Highway | <a href="/status" style="color:#00ff88">API Status</a>
  </div>
  
  <script>
    function toggleMotion() {
      var on = document.getElementById('motionToggle').checked;
      fetch(on ? '/motion/on' : '/motion/off');
    }
    
    function updateStatus() {
      fetch('/status').then(r => r.json()).then(data => {
        document.getElementById('state').textContent = 
          'Status: ' + (data.awake ? 'AWAKE' : 'SLEEPING') + 
          ' | Motion: ' + (data.motion ? 'ON' : 'OFF');
      }).catch(() => {});
    }
    
    setInterval(() => {
      var cam = document.getElementById('cam');
      cam.src = '/cam?t=' + Date.now();
      updateStatus();
    }, 1000);
    
    updateStatus();
  </script>
</body>
</html>
)rawliteral";

// =============================================
// SETUP
// =============================================
void setup() {
  Serial.begin(115200);
  Serial.println("\n\n========================================");
  Serial.println("       JARVIS Jr. Booting Up...");
  Serial.println("========================================\n");
  
  // Initialize pins
  pinMode(SOUND_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
  
  // Initialize servo
  armServo.attach(SERVO_PIN);
  armServo.write(90);
  Serial.println("[OK] Servo initialized (centered at 90)");
  
  // Initialize LED matrix
  ledFace.begin();
  ledFace.setIntensity(8);
  ledFace.displayClear();
  ledFace.displayScroll("HI", PA_LEFT, PA_SCROLL_LEFT, 80);
  Serial.println("[OK] LED matrix initialized");
  
  // Initialize camera
  initCamera();
  
  // Connect to WiFi
  Serial.print("[..] Connecting to WiFi");
  WiFi.begin(ssid, password);
  int wifiTries = 0;
  while (WiFi.status() != WL_CONNECTED && wifiTries < 30) {
    delay(500);
    Serial.print(".");
    wifiTries++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[OK] WiFi connected!");
    Serial.print("      IP Address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    Serial.println("[OK] Web server started");
  } else {
    Serial.println("\n[ERR] WiFi connection failed!");
    Serial.println("      Check SSID/password and restart");
  }
  
  // Startup sequence
  Serial.println("\n----------------------------------------");
  beep(2);
  Serial.println("JARVIS Jr. Ready!");
  Serial.println("----------------------------------------");
  Serial.println("Features:");
  Serial.println("  - Motion detection: ON");
  Serial.println("  - Face detection: ON");
  Serial.println("  - Clap patterns: 2=wave, 3=point, 4=photo");
  Serial.println("  - Phone control: http://<IP>");
  Serial.println("========================================\n");
}

// =============================================
// CAMERA INITIALIZATION
// =============================================
void initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 12;
  config.fb_count = 2;
  
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("[ERR] Camera init failed: 0x%x\n", err);
    return;
  }
  Serial.println("[OK] Camera initialized (SVGA, JPEG)");
  
  // Enable face detection
  sensor_t *s = esp_camera_sensor_get();
  if (s != NULL) {
    s->set_face_detect(s, true);
    Serial.println("[OK] Face detection enabled");
  }
}

// =============================================
// MAIN LOOP
// =============================================
void loop() {
  // Update LED animation
  if (ledFace.displayAnimate()) {
    ledFace.displayReset();
  }
  
  // Check for claps
  checkClap();
  
  // Check for motion when asleep
  if (motionEnabled && !isAwake) {
    checkMotion();
  }
  
  // Check awake timeout
  if (isAwake && millis() - wakeTime > AWAKE_DURATION) {
    goToSleep();
  }
  
  // Handle web requests
  handleWebClient();
}

// =============================================
// CLAP DETECTION
// =============================================
void checkClap() {
  int sound = digitalRead(SOUND_PIN);
  
  if (sound == HIGH) {
    unsigned long now = millis();
    
    // Debounce - ignore if too close to last detection
    if (now - lastClapDetect < 100) return;
    lastClapDetect = now;
    
    if (clapCount == 0) {
      clapCount = 1;
      firstClapTime = now;
      Serial.println("[CLAP] 1 detected");
      beep(1);
    } else if (now - firstClapTime < CLAP_TIMEOUT) {
      clapCount++;
      Serial.printf("[CLAP] %d detected\n", clapCount);
      
      if (clapCount == 4) {
        Serial.println("[ACT] 4 claps -> Taking photo!");
        takePhoto();
        clapCount = 0;
      } else if (clapCount == 3) {
        Serial.println("[ACT] 3 claps -> Pointing!");
        pointAtYou();
        clapCount = 0;
      } else if (clapCount == 2) {
        Serial.println("[ACT] 2 claps -> Waving!");
        waveArm();
        clapCount = 0;
      }
    }
    
    delay(50);
  }
  
  // Timeout - reset clap counter
  if (clapCount > 0 && millis() - firstClapTime > CLAP_TIMEOUT) {
    Serial.println("[CLAP] Timeout, resetting");
    clapCount = 0;
  }
}

// =============================================
// MOTION DETECTION
// =============================================
void checkMotion() {
  if (millis() - lastMotionCheck < MOTION_INTERVAL) return;
  lastMotionCheck = millis();
  
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) return;
  
  // Simple motion detection: count "interesting" pixels
  int motionScore = 0;
  for (size_t i = 0; i < fb->len; i += 50) {
    uint8_t pixel = fb->buf[i];
    if (pixel > 200 || pixel < 50) {
      motionScore++;
    }
  }
  
  esp_camera_fb_return(fb);
  
  if (motionScore > MOTION_THRESHOLD) {
    Serial.printf("[MOTION] Detected! Score: %d\n", motionScore);
    wakeUp();
  }
}

// =============================================
// WAKE / SLEEP
// =============================================
void wakeUp() {
  isAwake = true;
  wakeTime = millis();
  showFace("happy");
  beep(2);
  Serial.println("[STATE] Awake!");
}

void goToSleep() {
  isAwake = false;
  showFace("sleep");
  Serial.println("[STATE] Sleeping...");
}

// =============================================
// ARM MOVEMENTS
// =============================================
void waveArm() {
  isAwake = true;
  wakeTime = millis();
  showFace("happy");
  beep(2);
  
  for (int i = 0; i < 3; i++) {
    armServo.write(30);
    delay(200);
    armServo.write(150);
    delay(200);
  }
  armServo.write(90);
  Serial.println("[SERVO] Waved!");
}

void pointAtYou() {
  isAwake = true;
  wakeTime = millis();
  showFace("alert");
  beep(3);
  
  armServo.write(0);  // Point forward
  delay(1000);
  armServo.write(90);
  Serial.println("[SERVO] Pointed!");
}

// =============================================
// TAKE PHOTO
// =============================================
void takePhoto() {
  isAwake = true;
  wakeTime = millis();
  showFace("alert");
  beep(4);
  
  camera_fb_t* fb = esp_camera_fb_get();
  if (fb) {
    Serial.printf("[CAM] Photo captured! Size: %d bytes\n", fb->len);
    esp_camera_fb_return(fb);
    showFace("happy");
  } else {
    Serial.println("[CAM] Photo failed!");
  }
}

// =============================================
// BEEP
// =============================================
void beep(int count) {
  for (int i = 0; i < count; i++) {
    tone(BUZZER_PIN, 1000);
    delay(80);
    noTone(BUZZER_PIN);
    delay(80);
  }
}

// =============================================
// LED FACE EXPRESSIONS
// =============================================
void showFace(String expression) {
  ledFace.displayClear();
  
  if (expression == "happy") {
    ledFace.displayScroll(":)", PA_LEFT, PA_SCROLL_LEFT, 80);
  } else if (expression == "alert") {
    ledFace.displayScroll("O_O", PA_LEFT, PA_SCROLL_LEFT, 80);
  } else if (expression == "sleep") {
    ledFace.displayScroll("Zzz", PA_LEFT, PA_SCROLL_LEFT, 150);
  }
}

// =============================================
// WEB SERVER
// =============================================
void handleWebClient() {
  WiFiClient client = server.available();
  if (!client) return;
  
  // Read request with timeout
  String request = "";
  unsigned long timeout = millis();
  while (client.available() == 0 && millis() - timeout < 1000) {
    delay(10);
  }
  if (client.available()) {
    request = client.readStringUntil('\r');
    client.flush();
  }
  
  // Route: Home page
  if (request.indexOf("GET / ") >= 0 || request.indexOf("GET /") == 0 && request.indexOf(".") < 0) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.print(index_html);
    return;
  }
  
  // Route: Wave
  if (request.indexOf("GET /wave") >= 0) {
    waveArm();
    sendOK(client, "waving");
    return;
  }
  
  // Route: Point
  if (request.indexOf("GET /point") >= 0) {
    pointAtYou();
    sendOK(client, "pointing");
    return;
  }
  
  // Route: Photo
  if (request.indexOf("GET /photo") >= 0) {
    takePhoto();
    sendOK(client, "photo taken");
    return;
  }
  
  // Route: Sleep
  if (request.indexOf("GET /sleep") >= 0) {
    goToSleep();
    sendOK(client, "sleeping");
    return;
  }
  
  // Route: Wake
  if (request.indexOf("GET /wake") >= 0) {
    wakeUp();
    sendOK(client, "awake");
    return;
  }
  
  // Route: Motion ON
  if (request.indexOf("GET /motion/on") >= 0) {
    motionEnabled = true;
    sendOK(client, "motion on");
    return;
  }
  
  // Route: Motion OFF
  if (request.indexOf("GET /motion/off") >= 0) {
    motionEnabled = false;
    sendOK(client, "motion off");
    return;
  }
  
  // Route: Status (JSON)
  if (request.indexOf("GET /status") >= 0) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();
    client.print("{\"awake\":");
    client.print(isAwake ? "true" : "false");
    client.print(",\"motion\":");
    client.print(motionEnabled ? "true" : "false");
    client.print(",\"claps\":");
    client.print(clapCount);
    client.println("}");
    return;
  }
  
  // Route: Camera snapshot
  if (request.indexOf("GET /cam") >= 0) {
    camera_fb_t* fb = esp_camera_fb_get();
    if (fb) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: image/jpeg");
      client.println("Connection: close");
      client.println();
      client.write(fb->buf, fb->len);
      esp_camera_fb_return(fb);
    } else {
      client.println("HTTP/1.1 500 Error");
      client.println("Connection: close");
      client.println();
    }
    return;
  }
  
  // Default: 404
  client.println("HTTP/1.1 404 Not Found");
  client.println("Connection: close");
  client.println();
}

void sendOK(WiFiClient client, String action) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  client.print("{\"action\":\"");
  client.print(action);
  client.println("\"}");
}
