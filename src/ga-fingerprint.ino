#include <SoftwareSerial.h>
#include "fingerprint_defs.h"

#define FP_RX_PIN 2   // Arduino pin connected to module TX
#define FP_TX_PIN 3   // Arduino pin connected to module RX
#define FP_BAUD   9600

const bool DEBUG_OUT = true;

SoftwareSerial fpSerial(FP_RX_PIN, FP_TX_PIN);

#define FP_SERIAL fpSerial

void setup() {
    Serial.begin(115200);
    FP_SERIAL.begin(FP_BAUD);

    delay(500);
    Serial.println("Fingerprint module test");

    // 1. Open connection
    if (fp_send_command(FP_CMD_OPEN, 0, 0, 0, 0)) {
        Serial.println("Open: OK");
    } else {
        Serial.println("Open: FAILED");
    }

    // 2. Light LED
    if (fp_send_command(FP_CMD_LED_CONTROL, FP_LED_ON, 0, 0, 0)) {
        Serial.println("LED On: OK");
    } else {
        Serial.println("LED On: FAILED");
    }

    // 3. Delay 1000 ms
    delay(1000);

    // 4. Turn off LED
    if (fp_send_command(FP_CMD_LED_CONTROL, FP_LED_OFF, 0, 0, 0)) {
        Serial.println("LED Off: OK");
    } else {
        Serial.println("LED Off: FAILED");
    }

    // 5. Close connection
    if (fp_send_command(FP_CMD_CLOSE, 0, 0, 0, 0)) {
        Serial.println("Close: OK");
    } else {
        Serial.println("Close: FAILED");
    }

    Serial.println("Done");
}

void loop() {
}

/**
 * Send command to fingerprint module and wait for response
 * Returns true if ACK_SUCCESS received
 */
bool fp_send_command(uint8_t cmd, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4) {
    uint8_t packet[FP_PACKET_SIZE];
    uint8_t checksum;

    // Build command packet
    checksum = cmd ^ p1 ^ p2 ^ p3 ^ p4;

    packet[0] = FP_PACKET_START_CODE;
    packet[1] = cmd;
    packet[2] = p1;
    packet[3] = p2;
    packet[4] = p3;
    packet[5] = p4;
    packet[6] = checksum;
    packet[7] = FP_PACKET_END_CODE;

    // Send packet
    FP_SERIAL.write(packet, FP_PACKET_SIZE);

    if (DEBUG_OUT) {
        Serial.println();
        Serial.print("Sending command ");
        Serial.print(fp_cmd_to_string(cmd));
        Serial.println(":");
        fp_print_packet(packet);
    }

    // Wait for response
    return fp_receive_response(cmd);
}

/**
 * Receive and validate response packet
 */
bool fp_receive_response(uint8_t expected_cmd) {
    uint8_t response[FP_PACKET_SIZE];
    unsigned long timeout = millis() + 2000;
    uint8_t idx = 0;

    // Read response packet
    while (millis() < timeout && idx < FP_PACKET_SIZE) {
        if (FP_SERIAL.available()) {
            response[idx++] = FP_SERIAL.read();
        }
    }

    if (idx < FP_PACKET_SIZE) {
        if (DEBUG_OUT) {
            Serial.println("Response: Timeout");
            Serial.println();
        }
        return false;
    }

    // Validate packet structure
    if (response[0] != FP_PACKET_START_CODE || response[7] != FP_PACKET_END_CODE) {
        if (DEBUG_OUT) {
            Serial.println("Response: Invalid packet framing");
            Serial.println();
        }
        return false;
    }

    // Validate checksum
    uint8_t checksum = response[1] ^ response[2] ^ response[3] ^ response[4] ^ response[5];
    if (checksum != response[6]) {
        if (DEBUG_OUT) {
            Serial.println("Response: Checksum error");
            Serial.println();
        }
        return false;
    }

    // Check ACK code (Q3 at offset 4)
    uint8_t ack = response[FP_ACK_OFFSET_Q3];

    if (DEBUG_OUT) {
        Serial.print("Response ");
        Serial.print(fp_ack_to_string(ack));
        Serial.println(":");
        fp_print_packet(response);
        Serial.println();
    }

    return (ack == FP_ACK_SUCCESS);
}

/**
 * Print packet bytes in hex format
 */
void fp_print_packet(uint8_t* packet) {
    for (int i = 0; i < FP_PACKET_SIZE; i++) {
        if (packet[i] < 0x10) Serial.print("0");
        Serial.print(packet[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}
