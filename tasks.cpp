#include "tasks.h"

// -- Task handles for use in the notifications
static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t userTaskHandle = 0;

/** show() for ESP32
Call this function instead of FastLED.show(). It signals core 0 to issue a show,
then waits for a notification that it is done.
*/
void FastLEDshowESP32()
{
	if (userTaskHandle == 0) {
		// -- Store the handle of the current task, so that the show task can
		//    notify it when it's done
		userTaskHandle = xTaskGetCurrentTaskHandle();

		// -- Trigger the show task
		xTaskNotifyGive(FastLEDshowTaskHandle);

		// -- Wait to be notified that it's done
		const TickType_t xMaxBlockTime = pdMS_TO_TICKS(200);
		ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
		userTaskHandle = 0;
	}
}

/** show Task
This function runs on core 0 and just waits for requests to call FastLED.show()
*/
void FastLEDshowTask(void *pvParameters)
{
	// -- Run forever...
	for (;;) {
		// -- Wait for the trigger
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		// -- Do the show (synchronously)
		FastLED.show();

		// -- Notify the calling task
		xTaskNotifyGive(userTaskHandle);
	}
}

void createTasks()
{

	// Print the core the main code is running on.
	// Make sure to change FASTLED_SHOW_CORE if it is the same as this one.
	int core = xPortGetCoreID();
	Serial.print("Main code running on core ");
	Serial.println(core);

	// -- Create the FastLED show task
	xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2048, NULL, 2, &FastLEDshowTaskHandle, FASTLED_SHOW_CORE);

}