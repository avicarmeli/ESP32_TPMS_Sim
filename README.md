# ESP32 Renault TPMS sensor RF simulator
## Description:
RF signal generator to simulate 433Mhz Renault TPMS sensor. The Simulator uses ESP32 companioned by CC1101 to transmit RF signal.


## Hardware:

### Components:
- ESP32 Dev kit such as [that.](https://www.aliexpress.com/item/1005001929935550.html?spm=a2g0o.order_list.order_list_main.70.2fcd1802a3JqO6)   -  4$
- CC1101 module such as [that.](https://www.aliexpress.com/item/1005006427924521.html?spm=a2g0o.productlist.main.3.4606552dDUIADI&algo_pvid=f668fbe3-3ef8-466c-aa06-0833614c0e76&algo_exp_id=f668fbe3-3ef8-466c-aa06-0833614c0e76-1&pdp_npi=4%40dis%21USD%218.08%212.66%21%21%2158.41%2119.20%21%40211b600b17183703870547694e856b%2112000037133340091%21sea%21IL%21127988983%21&curPageLogUid=XNWVIg16GNX4&utparam-url=scene%3Asearch%7Cquery_from%3A)  -  2.7$

- **Total                under 7$**

### Wiering:
See wiering [diagram](https://github.com/avicarmeli/ESP32_TPMS_Sim/blob/main/Connection%20Diagram.md).

## Code:
### installation:
#### Prerequests:
- Arduino IDE.
- ESP32 Board (I use DEV Kit).
- CC1101 Board (I use 8 pins TZT CC1101).
- Install in Arduio IDE the following libraries:
  - ELECHOUSE_CC1101_SRC_DRV
- locate the directory where Arduino IDE stores the projects (for windows usually in Arduino folder under DOCS).
- Download Zip file of the repo using the Green **Code** pull down on the upper right corner of this page.
- Unzip the foldeer into the Arduino projects folder you located.


#### Upload:
- Opened Arduino IDE.
- Open the ESP32_TPMS_Sim project.
- Hit the upload button on the upper left corner (right arrow icon).
- If there are any errors follow the messages (most likely it is missing library).
- Depend on the board you use you might need to manually put your board into upload mode (usually holding both push buttons then releasing the reset butteon and only after a second or so the other button).
- When upload is done you might need to reset the board again.
