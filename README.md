# DelayFunctions Library for Arduino and ESP

The **DelayFunctions** library is a versatile tool for managing multiple software timers in Arduino and ESP projects. It provides a clean, non-blocking, and efficient way to handle timed events, making it ideal for tasks like LED blinking, button debouncing, or periodic updates.

The library is designed to handle the overflow of `millis()`. However, this has not been tested, but in practice, it should work.

---

## Key Features

- **Dynamic Timer Allocation**  
  Handle a user-defined number of timers with memory dynamically allocated for efficient resource usage.

- **Flexible Timer Updates**  
  Update timer intervals at runtime without restarting or losing track of the timer.

- **Non-blocking Design**  
  Uses the `millis()` function for asynchronous timing, ensuring smooth program execution without delays.

- **Simple Interface**  
  Easy-to-use functions for adding, updating, and managing timers within your main program loop.

This library helps streamline complex timing operations and keeps your code organized and efficient.

---

## Installation

Available now from the official Arduino Library Manager.

![image](https://github.com/user-attachments/assets/fb6774c0-e1aa-4530-9a12-9cde5967aadf)


OR

1. Download or clone the repository.
2. Place the library in your Arduino `libraries` folder.
3. Restart the Arduino IDE to access the library.

---

## API Reference

### 1. `DelayFunctions(int maxTimers)`
- **Description:** Creates a `DelayFunctions` object capable of managing up to `maxTimers`.
- **Example:**  
  ```cpp
  DelayFunctions delayObj(3); // Maximum of 3 timers
    ```

### 2. `void NewDelayFunction(unsigned long interval, void (*callback)())`
- **Description:** Adds a new timer with a specified `interval` (in milliseconds) and a `callback` function to execute when the timer elapses.
- **Example:**
  ```cpp
  delayObj.NewDelayFunction(1000, myCallback); // Executes myCallback every 1000ms

### 3. `void updateTime(void (*callback)(), unsigned long interval)`
- **Description:** Updates the interval of an existing timer associated with the given `callback`.
- **Example:**
  ```cpp
  delayObj.updateTime(myCallback, 500); // Changes interval to 500ms

### 4. `void loop()`
- **Description:** Call this method in the main `loop()` function to keep the timers running and execute callbacks when needed.
- **Example:**
  ```cpp
  void loop() {
    delayObj.loop();
  }

## Example Usage

Here's a simple example to toggle an LED every second:

cpp
```
#include <DelayFunctions.h>

#define ledPin 2  // Use LED_BUILTIN for Arduino, pin 2 for ESP boards

// Create a DelayFunctions object with capacity for 1 timer
DelayFunctions delayObj(1);

// Callback function for the timer
void toggleLED() {
  digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
}

void setup() {
  pinMode(ledPin, OUTPUT);
  delayObj.NewDelayFunction(1000, toggleLED); // Create a timer to toggle LED every 1000ms
}

void loop() {
  delayObj.loop(); // Keep timers running
}
```

## How It Works

1. **Setup Timers:** Create an instance of `DelayFunctions` and define your timers with specific intervals and callback functions.
2. **Run the Loop:** Call the `loop()` method in your `loop()` function to process the timers and trigger callbacks as needed.
3. **Extend Functionality:** Dynamically update intervals or add new timers during runtime.


## Applications

- Button debouncing
- LED control (blinking, patterns)
- Periodic sensor readings
- Timed animations
- General event scheduling in Arduino/ESP projects

## Contributing

Contributions, suggestions, and bug reports are welcome! Please create an issue or submit a pull request.


## License

This library is open-source and licensed under the MIT License. See the LICENSE file for details.
