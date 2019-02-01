#include "LEDMatrix.h"

#define WIDTH   17
#define HEIGHT  7

LEDMatrix matrix(A2, A2, A2, A2, A2, A2, A1, A0);     // LEDMatrix(a, b, c, d, oe, r1, stb, clk);
uint8_t displaybuf[WIDTH *HEIGHT / 8];          // Display Buffer

void setup() {
    matrix.begin(displaybuf, WIDTH, HEIGHT);
}

void loop() {
    static uint32_t lastCountTime = 0;
    static uint8_t count = 0;

    matrix.scan();

    if ((millis() - lastCountTime) > 3000) {
        lastCountTime = millis();
        matrix.drawRect(count + 4, count, 28 - count, 16 - count, 1 - (count & 1));
        count = (count + 1) & 0x0F;
    }
}
