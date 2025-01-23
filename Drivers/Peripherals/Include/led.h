#ifndef PERIPERALS_LED_H_
#define PERIPERALS_LED_H_

#define GPIO_PORT_A	0
#define LED_PIN		8
#define LED_MODE	1		// Output

void Led_Init(void);

// Function pointer to create an LED interface if multiple LEDs were to be used
typedef void (*ledFunc) (void);

typedef struct {
	const ledFunc On;
	const ledFunc Off;
} led;

extern led MyLED;

#endif /* PERIPERALS_LED_H_ */
