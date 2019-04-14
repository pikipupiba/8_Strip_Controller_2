
/** show() for ESP32
Call this function instead of FastLED.show(). It signals core 0 to issue a show,
then waits for a notification that it is done.
*/
void FastLEDshowESP32();

/** show Task
This function runs on core 0 and just waits for requests to call FastLED.show()
*/
void FastLEDshowTask(void *pvParameters);

void createTasks();