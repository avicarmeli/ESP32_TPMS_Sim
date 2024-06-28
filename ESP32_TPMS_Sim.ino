#include <ELECHOUSE_CC1101_SRC_DRV.h>

#define CC1101_FREQUENCY 433.92 // Frequency for TPMS
#define DEBUG 1 //to print debug data

void setup() {
  Serial.begin(115200);

#ifdef DEBUG
  Serial.println("Initializing CC1101...");
#endif

if (ELECHOUSE_cc1101.getCC1101()){      // Check the CC1101 Spi connection.

#ifdef DEBUG
    Serial.println("Connection OK");
#endif
    }else{
#ifdef DEBUG
    Serial.println("Connection Error");
#endif
    return;
    }
 
    ELECHOUSE_cc1101.Init();                // must be set to initialize the cc1101!
    ELECHOUSE_cc1101.setCCMode(1);          // set config for internal transmission mode.
    ELECHOUSE_cc1101.setModulation(0);      // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
    ELECHOUSE_cc1101.setMHZ(CC1101_FREQUENCY);        // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
    ELECHOUSE_cc1101.setDeviation(47.60);   // Set the Frequency deviation in kHz. Value from 1.58 to 380.85. Default is 47.60 kHz.
    ELECHOUSE_cc1101.setChannel(0);         // Set the Channelnumber from 0 to 255. Default is cahnnel 0.
    ELECHOUSE_cc1101.setChsp(199.95);       // The channel spacing is multiplied by the channel number CHAN and added to the base frequency in kHz. Value from 25.39 to 405.45. Default is 199.95 kHz.
    ELECHOUSE_cc1101.setRxBW(812.50);       // Set the Receive Bandwidth in kHz. Value from 58.03 to 812.50. Default is 812.50 kHz.
    ELECHOUSE_cc1101.setDRate(18.5);       // Set the Data Rate in kBaud. Value from 0.02 to 1621.83. Default is 99.97 kBaud!
    ELECHOUSE_cc1101.setPA(10);             // Set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12) Default is max!
    ELECHOUSE_cc1101.setSyncMode(0);        // Combined sync-word qualifier mode. 0 = No preamble/sync. 1 = 16 sync word bits detected. 2 = 16/16 sync word bits detected. 3 = 30/32 sync word bits detected. 4 = No preamble/sync, carrier-sense above threshold. 5 = 15/16 + carrier-sense above threshold. 6 = 16/16 + carrier-sense above threshold. 7 = 30/32 + carrier-sense above threshold.
    ELECHOUSE_cc1101.setSyncWord(211, 145); // Set sync word. Must be the same for the transmitter and receiver. (Syncword high, Syncword low)
    ELECHOUSE_cc1101.setAdrChk(0);          // Controls address check configuration of received packages. 0 = No address check. 1 = Address check, no broadcast. 2 = Address check and 0 (0x00) broadcast. 3 = Address check and 0 (0x00) and 255 (0xFF) broadcast.
    ELECHOUSE_cc1101.setAddr(0);            // Address used for packet filtration. Optional broadcast addresses are 0 (0x00) and 255 (0xFF).
    ELECHOUSE_cc1101.setWhiteData(0);       // Turn data whitening on / off. 0 = Whitening off. 1 = Whitening on.
    ELECHOUSE_cc1101.setPktFormat(0);       // Format of RX and TX data. 0 = Normal mode, use FIFOs for RX and TX. 1 = Synchronous serial mode, Data in on GDO0 and data out on either of the GDOx pins. 2 = Random TX mode; sends random data using PN9 generator. Used for test. Works as normal mode, setting 0 (00), in RX. 3 = Asynchronous serial mode, Data in on GDO0 and data out on either of the GDOx pins.
    ELECHOUSE_cc1101.setLengthConfig(1);    // 0 = Fixed packet length mode. 1 = Variable packet length mode. 2 = Infinite packet length mode. 3 = Reserved
    ELECHOUSE_cc1101.setPacketLength(0);    // Indicates the packet length when fixed packet length mode is enabled. If variable packet length mode is used, this value indicates the maximum packet length allowed.
    ELECHOUSE_cc1101.setCrc(0);             // 1 = CRC calculation in TX and CRC check in RX enabled. 0 = CRC disabled for TX and RX.
    ELECHOUSE_cc1101.setCRC_AF(0);          // Enable automatic flush of RX FIFO when CRC is not OK. This requires that only one packet is in the RXIFIFO and that packet length is limited to the RX FIFO size.
    ELECHOUSE_cc1101.setDcFilterOff(0);     // Disable digital DC blocking filter before demodulator. Only for data rates ≤ 250 kBaud The recommended IF frequency changes when the DC blocking is disabled. 1 = Disable (current optimized). 0 = Enable (better sensitivity).
    ELECHOUSE_cc1101.setManchester(0);      // Enables Manchester encoding/decoding. 0 = Disable. 1 = Enable.
    ELECHOUSE_cc1101.setFEC(0);             // Enable Forward Error Correction (FEC) with interleaving for packet payload (Only supported for fixed packet length mode. 0 = Disable. 1 = Enable.
    ELECHOUSE_cc1101.setPRE(0);             // Sets the minimum number of preamble bytes to be transmitted. Values: 0 : 2, 1 : 3, 2 : 4, 3 : 6, 4 : 8, 5 : 12, 6 : 16, 7 : 24
    ELECHOUSE_cc1101.setPQT(0);             // Preamble quality estimator threshold. The preamble quality estimator increases an internal counter by one each time a bit is received that is different from the previous bit, and decreases the counter by 8 each time a bit is received that is the same as the last bit. A threshold of 4∙PQT for this counter is used to gate sync word detection. When PQT=0 a sync word is always accepted.
    ELECHOUSE_cc1101.setAppendStatus(0);    // When enabled, two status bytes will be appended to the payload of the packet. The status bytes contain RSSI and LQI values, as well as CRC OK.

    Serial.println("Tx Mode");
#ifdef DEBUG
    Serial.println("CC1101 initialized.");
#endif
}

uint8_t crc8(const uint8_t *data, size_t len, uint8_t polynomial, uint8_t initial) {
  uint8_t crc = initial;
  while (len--) {
    crc ^= *data++;
    for (uint8_t i = 0; i < 8; i++) {
      if (crc & 0x80)
        crc = (crc << 1) ^ polynomial;
      else
        crc <<= 1;
    }
  }
  return crc;
}


void generateTPMSData(uint8_t *data, uint32_t id, float temperature, double pressure, uint8_t battery) {
  uint16_t press;
  
  press = (static_cast<uint16_t>((pressure * 4) / 3));

#ifdef DEBUG
  Serial.printf("Pressure=%f",(pressure*4/3));
  Serial.println();
  Serial.printf("Press=%d",press);
  Serial.println();
#endif

  data[0] = ((battery <<2) | (press >> 8 )) & 0xFF;
  data[1] = (press) & 0xFF;
  data[2] = static_cast<uint8_t>(temperature + 30); // Offset by 30
  data[5] = (id >> 16) & 0xFF;
  data[4] = (id >> 8) & 0xFF;
  data[3] = id & 0xFF;
  data[6] = 0x50;
  data[7] = 0xBD;
  data[8] = crc8(data, 8, 0x07, 0x00); // Calculate CRC8 checksum with polynomial 0x07 and initial value 0x00
}

void encodeManchester(uint8_t *encoded, const uint8_t *data, size_t len) {
  size_t bitIndex = 0;
  for (size_t i = 0; i < len; i++) {
    for (int bit = 7; bit >= 0; bit--) {
      if (data[i] & (1 << bit)) {
        // Bit is 1, Manchester encoding is 10
        encoded[bitIndex / 8] |= (1 << (7 - (bitIndex % 8)));
        bitIndex++;
        encoded[bitIndex / 8] &= ~(1 << (7 - (bitIndex % 8)));
      } else {
        // Bit is 0, Manchester encoding is 01
        encoded[bitIndex / 8] &= ~(1 << (7 - (bitIndex % 8)));
        bitIndex++;
        encoded[bitIndex / 8] |= (1 << (7 - (bitIndex % 8)));
      }
      bitIndex++;
    }
  }
}

void loop() {
  uint8_t tpmsData[11]; // Actual data
  uint8_t encodedData[22]; // Manchester encoded data (2x the size)
  // Set preamble: 0xAA, 0xAA, 0xAA, 0xA9 (inverted: 0x55, 0x55, 0x55, 0x56) Machester encoding will inflate it to the mentioned preable
  tpmsData[0] = 0x00;
  tpmsData[1] = 0x01;
  // Generate the TPMS data payload
  generateTPMSData(tpmsData + 2, 0x031464, 36, 221.25, 54); // Example values

  // Encode data using Manchester encoding
  memset(encodedData, 0, sizeof(encodedData));
  encodeManchester(encodedData, tpmsData, sizeof(tpmsData));

#ifdef DEBUG
 // Print data for debugging
  Serial.println("TPMS DATA:");
  for (int i = 0; i < sizeof(tpmsData); i++) {
    Serial.print(tpmsData[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Print data for debugging
  Serial.println("ENCODED TPMS DATA:");
  for (int i = 0; i < sizeof(encodedData); i++) {
    Serial.print(encodedData[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
#endif
  // Send TPMS data
  //ELECHOUSE_cc1101.Sidle();
  ELECHOUSE_cc1101.SendData(encodedData, sizeof(encodedData),100);

#ifdef DEBUG
  Serial.println("TPMS signal sent.");
#endif

 

  delay(2000); // Wait 2 seconds before sending the next signal
}
