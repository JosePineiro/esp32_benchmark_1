#include <Arduino.h>
#include <esp_timer.h>


// ========================================
// MOCK DEFINITIONS
// ========================================

// extensions & MIME-Types
static constexpr const char *T__avif = ".avif";                                   // AVIF: Highly compressed images. Compatible with all modern browsers.
static constexpr const char *T__csv = ".csv";                                     // CSV: Data logging and configuration
static constexpr const char *T__css = ".css";                                     // CSS: Styling for web interfaces
static constexpr const char *T__gif = ".gif";                                     // GIF: Simple animations. Legacy support
static constexpr const char *T__gz = ".gz";                                       // GZ: compressed files
static constexpr const char *T__htm = ".htm";                                     // HTM: Web interface files
static constexpr const char *T__html = ".html";                                   // HTML: Web interface files
static constexpr const char *T__ico = ".ico";                                     // ICO: Favicons, system icons. Legacy support
static constexpr const char *T__jpg = ".jpg";                                     // JPEG/JPG: Photos. Legacy support
static constexpr const char *T__js = ".js";                                       // JavaScript: Interactive functionality
static constexpr const char *T__json = ".json";                                   // JSON: Data exchange format
static constexpr const char *T__mp4 = ".mp4";                                     // MP4: Proprietary format. Worse compression than WEBM.
static constexpr const char *T__opus = ".opus";                                   // OPUS: High compression audio format
static constexpr const char *T__pdf = ".pdf";                                     // PDF: Universal document format
static constexpr const char *T__png = ".png";                                     // PNG: Icons, logos, transparency. Legacy support
static constexpr const char *T__svg = ".svg";                                     // SVG: Vector graphics, icons (scalable, tiny file sizes)
static constexpr const char *T__ttf = ".ttf";                                     // TTF: Font file. Legacy support
static constexpr const char *T__txt = ".txt";                                     // TXT: Plain text files
static constexpr const char *T__webm = ".webm";                                   // WebM: Video. Open source, optimized for web. Compatible with all modern browsers.
static constexpr const char *T__webp = ".webp";                                   // WebP: Highly compressed images. Compatible with all modern browsers.
static constexpr const char *T__woff = ".woff";                                   // WOFF: Font file. Legacy support
static constexpr const char *T__woff2 = ".woff2";                                 // WOFF2: Better compression. Compatible with all modern browsers.
static constexpr const char *T__xml = ".xml";                                     // XML: Configuration and data files
static constexpr const char *T_application_javascript = "application/javascript"; // Obsolete type for JavaScript
static constexpr const char *T_application_json = "application/json";
static constexpr const char *T_application_msgpack = "application/msgpack";
static constexpr const char *T_application_octet_stream = "application/octet-stream";
static constexpr const char *T_application_pdf = "application/pdf";
static constexpr const char *T_app_xform_urlencoded = "application/x-www-form-urlencoded";
static constexpr const char *T_audio_opus = "audio/opus";
static constexpr const char *T_font_ttf = "font/ttf";
static constexpr const char *T_font_woff = "font/woff";
static constexpr const char *T_font_woff2 = "font/woff2";
static constexpr const char *T_image_avif = "image/avif";
static constexpr const char *T_image_gif = "image/gif";
static constexpr const char *T_image_jpeg = "image/jpeg";
static constexpr const char *T_image_png = "image/png";
static constexpr const char *T_image_svg_xml = "image/svg+xml";
static constexpr const char *T_image_webp = "image/webp";
static constexpr const char *T_image_x_icon = "image/x-icon";
static constexpr const char *T_text_css = "text/css";
static constexpr const char *T_text_csv = "text/csv";
static constexpr const char *T_text_event_stream = "text/event-stream";
static constexpr const char *T_text_html = "text/html";
static constexpr const char *T_text_javascript = "text/javascript";
static constexpr const char *T_text_plain = "text/plain";
static constexpr const char *T_text_xml = "text/xml";
static constexpr const char *T_video_mp4 = "video/mp4";
static constexpr const char *T_video_webm = "video/webm";

// Global variable to simulate contentType pointer
const char *_contentType = nullptr;

// ========================================
// FUNCTIONS TO BENCHMARK
// ========================================

/**
 * @brief Original version
 */
void _setContentTypeFromPath_v1(const String &path)
{
  const char *cpath = path.c_str();
  const char *dot = strrchr(cpath, '.');

  if (!dot)
  {
    _contentType = T_application_octet_stream;
    return;
  }
  if (strcmp(dot, T__html) == 0 || strcmp(dot, T__htm) == 0)
  {
    _contentType = T_text_html;
  }
  else if (strcmp(dot, T__css) == 0)
  {
    _contentType = T_text_css;
  }
  else if (strcmp(dot, T__js) == 0)
  {
    _contentType = T_application_javascript;
  }
  else if (strcmp(dot, T__json) == 0)
  {
    _contentType = T_application_json;
  }
  else if (strcmp(dot, T__png) == 0)
  {
    _contentType = T_image_png;
  }
  else if (strcmp(dot, T__ico) == 0)
  {
    _contentType = T_image_x_icon;
  }
  else if (strcmp(dot, T__svg) == 0)
  {
    _contentType = T_image_svg_xml;
  }
  else if (strcmp(dot, T__jpg) == 0)
  {
    _contentType = T_image_jpeg;
  }
  else if (strcmp(dot, T__webp) == 0)
  {
    _contentType = T_image_webp;
  }
  else if (strcmp(dot, T__avif) == 0)
  {
    _contentType = T_image_avif;
  }
  else if (strcmp(dot, T__gif) == 0)
  {
    _contentType = T_image_gif;
  }
  else if (strcmp(dot, T__woff2) == 0)
  {
    _contentType = T_font_woff2;
  }
  else if (strcmp(dot, T__woff) == 0)
  {
    _contentType = T_font_woff;
  }
  else if (strcmp(dot, T__ttf) == 0)
  {
    _contentType = T_font_ttf;
  }
  else if (strcmp(dot, T__xml) == 0)
  {
    _contentType = T_text_xml;
  }
  else if (strcmp(dot, T__pdf) == 0)
  {
    _contentType = T_application_pdf;
  }
  else if (strcmp(dot, T__mp4) == 0)
  {
    _contentType = T_video_mp4;
  }
  else if (strcmp(dot, T__opus) == 0)
  {
    _contentType = T_audio_opus;
  }
  else if (strcmp(dot, T__webm) == 0)
  {
    _contentType = T_video_webm;
  }
  else if (strcmp(dot, T__txt) == 0)
  {
    _contentType = T_text_plain;
  }
  else
  {
    _contentType = T_application_octet_stream;
  }
}

/**
 * @brief Optimized version using switch
 */
void _setContentTypeFromPath_v2(const String &path) {
  // Extract extension to const char *
  const char *cpath = path.c_str();
  const char *dot = strrchr(cpath, '.');

  if (!dot) {
    _contentType = T_application_octet_stream;
    return;
  }

  switch (dot[1]) {
  case 'a':
    if (strcmp(dot, T__avif) == 0)
      _contentType = T_image_avif;
    break;
  case 'c':
    if (strcmp(dot, T__css) == 0)
      _contentType = T_text_css;
    break;
  case 'g':
    if (strcmp(dot, T__gif) == 0)
      _contentType = T_image_gif;
    break;
  case 'h':
    if (strcmp(dot, T__html) == 0 || strcmp(dot, T__htm) == 0)
      _contentType = T_text_html;
    break;
  case 'i':
    if (strcmp(dot, T__ico) == 0)
      _contentType = T_image_x_icon;
    break;
  case 'j':
    // Order by likelihood: JS is more common. JSON in less common.
    if (strcmp(dot, T__js) == 0)
      _contentType = T_application_javascript;
    else if (strcmp(dot, T__jpg) == 0)
      _contentType = T_image_jpeg;
    else if (strcmp(dot, T__json) == 0)
      _contentType = T_application_json;
    break;
  case 'm':
    if (strcmp(dot, T__mp4) == 0)
      _contentType = T_video_mp4;
    break;
  case 'o':
    if (strcmp(dot, T__opus) == 0)
      _contentType = T_audio_opus;
    break;
  case 'p':
    // PNG is more common in web contexts, so check it first
    if (strcmp(dot, T__png) == 0)
      _contentType = T_image_png;
    else if (strcmp(dot, T__pdf) == 0)
      _contentType = T_application_pdf;
    break;
  case 's':
    if (strcmp(dot, T__svg) == 0)
      _contentType = T_image_svg_xml;
    break;
  case 't':
    if (strcmp(dot, T__ttf) == 0)
      _contentType = T_font_ttf;
    else if (strcmp(dot, T__txt) == 0)
      _contentType = T_text_plain;
    break;
  case 'w':
    // Order by likelihood in web serving contexts
    if (strcmp(dot, T__webp) == 0)
      _contentType = T_image_webp;
    else if (strcmp(dot, T__webm) == 0)
      _contentType = T_video_webm;
    else if (strcmp(dot, T__woff2) == 0)
      _contentType = T_font_woff2;
    else if (strcmp(dot, T__woff) == 0)
      _contentType = T_font_woff;
    break;
  case 'x':
    if (strcmp(dot, T__xml) == 0)
      _contentType = T_text_xml;
    break;
  default:
    _contentType = T_application_octet_stream;
    return;
  }

  // If we reach here and contentType wasn't set, use default
  if (_contentType == nullptr)
  {
    _contentType = T_application_octet_stream;
  }
}

#define EXT_EQ(dot, ext) (dot[1] == ext[1] && strcmp(dot, ext) == 0)
/**
 * @brief Optimized version using table
 */
void _setContentTypeFromPath_v3(const String &path) {
  const char *dot = strrchr(path.c_str(), '.');
  if (!dot)
    _contentType = T_application_octet_stream;
  else if (EXT_EQ(dot, T__html) || EXT_EQ(dot, T__htm))
    _contentType = T_text_html;
  else if (EXT_EQ(dot, T__css))
    _contentType = T_text_css;
  else if (EXT_EQ(dot, T__js))
    _contentType = T_application_javascript;
  else if (EXT_EQ(dot, T__avif))
    _contentType = T_image_avif;
  else if (EXT_EQ(dot, T__webp))
    _contentType = T_image_webp;
  else if (EXT_EQ(dot, T__svg))
    _contentType = T_image_svg_xml;
  else if (EXT_EQ(dot, T__json))
    _contentType = T_application_json;
  else if (EXT_EQ(dot, T__woff2))
    _contentType = T_font_woff2;
  else if (EXT_EQ(dot, T__png))
    _contentType = T_image_png;
  else if (EXT_EQ(dot, T__jpg))
    _contentType = T_image_jpeg;
  else if (EXT_EQ(dot, T__gif))
    _contentType = T_image_gif;
  else if (EXT_EQ(dot, T__ico))
    _contentType = T_image_x_icon;
  else if (EXT_EQ(dot, T__woff))
    _contentType = T_font_woff;
  else if (EXT_EQ(dot, T__ttf))
    _contentType = T_font_ttf;
  else if (EXT_EQ(dot, T__xml))
    _contentType = T_text_xml;
  else if (EXT_EQ(dot, T__pdf))
    _contentType = T_application_pdf;
  else if (EXT_EQ(dot, T__webm))
    _contentType = T_video_webm;
  else if (EXT_EQ(dot, T__mp4))
    _contentType = T_video_mp4;
  else if (EXT_EQ(dot, T__opus))
    _contentType = T_audio_opus;
  else if (EXT_EQ(dot, T__txt))
    _contentType = T_text_plain;
  else
    _contentType = T_application_octet_stream;
}


// ========================================
// BENCHMARK CONFIGURATION
// ========================================

#define BENCHMARK_ITERATIONS 100000 // Number of iterations per test
#define BENCHMARK_ROUNDS 10         // Number of test rounds for averaging
#define TEST_DATA_SIZE 25           // Number of different test patterns

// Test data patterns - realistic file paths
static const char *testPaths[TEST_DATA_SIZE] = {
    "/index.html",         // Main page (1)
    "/dashboard.html",     // Additional UI page (2)
    "/settings.html",      // Another HTML view (3)
    "/about.html",         // Info page (4)
    "/config.htm",         // Embedded config page (5)
    "/style.css",          // Main stylesheet (1)
    "/theme.css",          // Alternate theme (2)
    "/layout.css",         // Layout-specific CSS (3)
    "/main.js",            // Main logic (1)
    "/ajax.js",            // AJAX handler (2)
    "/charts.js",          // UI interaction (3)
    "/data.json",          // Device data (1)
    "/config.json",        // User config (2)
    "/status.json",        // System status (3)
    "/icon.png",           // Small UI icon (1)
    "/logo.png",           // Logo or branding (2)
    "/favicon.ico",        // Browser icon
    "/graphics/alert.svg", // SVG icon
    "/fonts/roboto.woff2", // Web font
    "/fonts/icons.ttf",    // Font for icon set
    "/unknownfile.xyz",
    "/very/long/path/to/file.html",
    "/no/extension",
    "/void/extension.",
    "/two/extension.min.js"
  };

// ========================================
// BENCHMARK UTILITIES
// ========================================

/**
 * @brief Get high precision timestamp in microseconds
 */
static inline uint64_t getMicros()
{
  return esp_timer_get_time();
}

/**
 * @brief Verify that all functions produce identical results
 */
bool verifyFunctionEquivalence()
{
  Serial.println("=== VERIFYING FUNCTION EQUIVALENCE ===");

  for (int i = 0; i < TEST_DATA_SIZE; i++)
  {
    String testPath = String(testPaths[i]);

    // Test version 1
    _setContentTypeFromPath_v1(testPath);
    const char *result1 = _contentType;

    // Test version 2
    _setContentTypeFromPath_v2(testPath);
    const char *result2 = _contentType;

    // Test version 3
    _setContentTypeFromPath_v3(testPath);
    const char *result3 = _contentType;

    // Compare results
    if (strcmp(result1, result2) != 0 || strcmp(result1, result3) != 0)
    {
      Serial.printf("MISMATCH at test %d: %s\n", i, testPaths[i]);
      Serial.printf("Version 1: %s\n", result1);
      Serial.printf("Version 2: %s\n", result2);
      Serial.printf("Version 3: %s\n", result3);
      return false;
    }

    Serial.printf("Test %d OK: %s -> %s\n", i, testPaths[i], result1);
  }

  Serial.println("All functions produce identical results!\n");
  return true;
}

/**
 * @brief Benchmark a specific function
 */
uint64_t benchmarkFunction(void (*func)(const String &), const char *functionName)
{
  uint64_t totalTime = 0;

  Serial.printf("Benchmarking %s...\n", functionName);

  for (int round = 0; round < BENCHMARK_ROUNDS; round++)
  {
    uint64_t startTime = getMicros();

    // Perform benchmark iterations
    for (int iter = 0; iter < BENCHMARK_ITERATIONS; iter++)
    {
      // Use different test data to prevent compiler optimizations
      String testPath = String(testPaths[iter % TEST_DATA_SIZE]);

      func(testPath);

      // Prevent compiler from optimizing away the function call
      asm volatile("" ::"m"(_contentType) : "memory");
    }

    uint64_t endTime = getMicros();
    uint64_t roundTime = endTime - startTime;
    totalTime += roundTime;

    Serial.printf("  Round %d: %llu μs (%0.5f μs per call)\n",
                  round + 1, roundTime, (double)roundTime / BENCHMARK_ITERATIONS);
  }

  uint64_t avgTime = totalTime / BENCHMARK_ROUNDS;
  double avgPerCall = (double)avgTime / BENCHMARK_ITERATIONS;

  Serial.printf("  Average: %llu μs (%0.5f μs per call)\n\n", avgTime, avgPerCall);

  return avgTime;
}

/**
 * @brief Calculate performance improvement percentage
 */
void calculateImprovement(uint64_t time1, uint64_t time2, uint64_t time3)
{
  Serial.println("=== PERFORMANCE COMPARISON ===");
  Serial.printf("Version 1: %0.4f μs per call\n", (double)time1 / BENCHMARK_ITERATIONS);
  Serial.printf("Version 2: %0.4f μs per call\n", (double)time2 / BENCHMARK_ITERATIONS);
  Serial.printf("Version 3: %0.4f μs per call\n", (double)time3 / BENCHMARK_ITERATIONS);

  double improvement2 = ((double)(time1 - time2) / time1) * 100.0;
  double improvement3 = ((double)(time1 - time3) / time1) * 100.0;
  double speedup2 = (double)time1 / time2;
  double speedup3 = (double)time1 / time3;

  Serial.printf("\nVersion 2 vs Version 1: %0.2f%% improvement, %0.2fx speedup\n",
                improvement2, speedup2);
  Serial.printf("Version 3 vs Version 1: %0.2f%% improvement, %0.2fx speedup\n",
                improvement3, speedup3);

  // Find the fastest
  uint64_t fastest = min(time1, min(time2, time3));
  if (fastest == time1)
  {
    Serial.println("✓ Version 1 is FASTEST");
  }
  else if (fastest == time2)
  {
    Serial.println("✓ Version 2 is FASTEST");
  }
  else
  {
    Serial.println("✓ Version 3 is FASTEST");
  }
  Serial.println();
}

/**
 * @brief Memory usage test
 */
void testMemoryUsage()
{
  Serial.println("=== MEMORY USAGE TEST ===");

  UBaseType_t stackBefore = uxTaskGetStackHighWaterMark(NULL);

  // Test all versions
  String testPath = "test.html";
  for (int i = 0; i < 1000; i++)
  {
    _setContentTypeFromPath_v1(testPath);
    _setContentTypeFromPath_v2(testPath);
    _setContentTypeFromPath_v3(testPath);
  }

  UBaseType_t stackAfter = uxTaskGetStackHighWaterMark(NULL);

  Serial.printf("Stack usage change: %d bytes\n", (stackBefore - stackAfter) * 4);
  Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
  Serial.println();
}

// ========================================
// MAIN PROGRAM
// ========================================

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }

  delay(2000); // Give time to open serial monitor

  Serial.println("=======================================");
  Serial.println("ESP32 Content Type Performance Benchmark");
  Serial.println("=======================================");
  Serial.printf("CPU Frequency: %d MHz\n", getCpuFrequencyMhz());
  Serial.printf("Flash Speed: %d MHz\n", ESP.getFlashChipSpeed() / 1000000);
  Serial.printf("Benchmark iterations: %d\n", BENCHMARK_ITERATIONS);
  Serial.printf("Benchmark rounds: %d\n", BENCHMARK_ROUNDS);
  Serial.println();

  // Step 1: Verify functions produce identical results
  if (!verifyFunctionEquivalence())
  {
    Serial.println("❌ FUNCTIONS DO NOT MATCH! Stopping benchmark.");
    return;
  }

  // Step 2: Memory usage test
  testMemoryUsage();

  // Step 3: Performance benchmark
  Serial.println("=== PERFORMANCE BENCHMARK ===");
  delay(3000);

  uint64_t time1 = benchmarkFunction(_setContentTypeFromPath_v1, "Version 1");
  uint64_t time2 = benchmarkFunction(_setContentTypeFromPath_v2, "Version 2");
  uint64_t time3 = benchmarkFunction(_setContentTypeFromPath_v3, "Version 3");

  // Step 4: Calculate and display results
  calculateImprovement(time1, time2, time3);

  // Step 5: Additional system info
  Serial.println("=== SYSTEM INFORMATION ===");
  Serial.printf("ESP32 Chip: %s\n", ESP.getChipModel());
  Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
  Serial.printf("Flash Size: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("PSRAM Size: %d MB\n", ESP.getPsramSize() / (1024 * 1024));
  Serial.printf("Free Heap: %d KB\n", ESP.getFreeHeap() / 1024);
  Serial.printf("Cpu Frequency: %d Mhz\n", getCpuFrequencyMhz());
  Serial.println("\n✅ Benchmark completed!");
}

void loop()
{
  // Optional: Run continuous mini-benchmark
  static unsigned long lastBenchmark = 0;

  if (millis() - lastBenchmark > 30000)
  { // Every 30 seconds
    lastBenchmark = millis();

    Serial.println("\n--- Quick Benchmark ---");

    String testPath = "example.css";

    // Quick test - 10000 iterations
    uint64_t start1 = getMicros();
    for (int i = 0; i < 10000; i++)
    {
      _setContentTypeFromPath_v1(testPath);
    }
    uint64_t time1 = getMicros() - start1;

    uint64_t start2 = getMicros();
    for (int i = 0; i < 10000; i++)
    {
      _setContentTypeFromPath_v2(testPath);
    }
    uint64_t time2 = getMicros() - start2;

    uint64_t start3 = getMicros();
    for (int i = 0; i < 10000; i++)
    {
      _setContentTypeFromPath_v3(testPath);
    }
    uint64_t time3 = getMicros() - start3;

    Serial.printf("V1: %0.5f μs/call, V2: %0.5f μs/call, V3: %0.5f μs/call\n",
                  (float)time1 / 10000, (float)time2 / 10000, (float)time3 / 10000);
    Serial.printf("V2 speedup: %0.2fx, V3 speedup: %0.2fx\n",
                  (float)time1 / time2, (float)time1 / time3);
  }

  delay(1000);
}