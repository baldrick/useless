#define DEBUGGING_ON
#ifdef DEBUGGING_ON
  #define DEBUG(...)      Serial.println(__VA_ARGS__)
#else
  #define DEBUG(...)
#endif

//#define TRACING_ON
#ifdef TRACING_ON
  #define TRACE(...)      Serial.println(__VA_ARGS__)
#else
  #define TRACE(...)
#endif
