# Quick Setup Guide: Waveshare E-Paper Display with ESPHome and ESP32

## Prerequisites
- **Hardware:**
  - ESP32 Development Board (e.g., esp32dev)
  - Waveshare 7.50in-bv2-rb E-Paper Display
  - Connecting wires
  - Power supply
- **Software:**
  - ESPHome installed
  - Image editor (GIMP, Photoshop)

## Hardware Connections
| E-Paper Pin | ESP32 GPIO Pin | Notes                                     |
|-------------|----------------|-------------------------------------------|
| CS          | GPIO15         | Strapping pin – use with care             |
| DC          | GPIO27         | Data/Command Control                      |
| Busy        | GPIO25         | Inverted signal                           |
| Reset       | GPIO26         | Reset Pin                                 |
| CLK         | GPIO13         | SPI Clock                                 |
| MOSI        | GPIO14         | SPI Master Out Slave In                   |
| VCC         | 3.3V           | Power                                      |
| GND         | GND            | Ground                                     |

**Note:** Avoid using strapping pins like GPIO15 for non-essential functions to prevent boot issues.

## Image Preparation
1. **Split Image into Layers:**
   - **Black Layer:** Contains only black parts, background transparent.
   - **Red Layer:** Contains only red parts, background transparent.
2. **Save as PNG:**
   - Ensure transparency is preserved.
   - Use `TRANSPARENT_BINARY` type for ESPHome.

**Firmware Quirk:** Due to a firmware quirk, black areas in your images should be rendered using `Color::WHITE` in the ESPHome configuration.

## ESPHome Configuration

esphome:
  name: epaper-display
  platform: ESP32
  board: esp32dev
  on_boot:
    priority: 200.0
    then:
      - script.execute: refresh_screen

external_components:
  - source:
      type: git
      url: https://github.com/twisterss/esphome-dev.git
      ref: waveshare-red-black
    components: [ waveshare_epaper ]

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  use_address: 192.168.1.117
  ap:
    ssid: "Epaper Display Fallback Hotspot"
    password: !secret wifi_password

captive_portal:

logger:
  level: DEBUG
  logs:
    waveshare_epaper: DEBUG

api:
  encryption:
    key: !secret epaper_display_key

ota:
  password: !secret ota_password

web_server:
  port: 80

spi:
  clk_pin: GPIO13
  mosi_pin: GPIO14

color:
  - id: CUSTOM_RED
    red: 100%
    green: 0%
    blue: 0%
    white: 0%

image:
  - file: "images/puppy_black_layer.png"
    id: puppy_black_layer
    type: TRANSPARENT_BINARY
  - file: "images/puppy_red_layer.png"
    id: puppy_red_layer
    type: TRANSPARENT_BINARY

display:
  - platform: waveshare_epaper
    id: epaper_display
    cs_pin: GPIO15
    dc_pin: GPIO27
    busy_pin:
      number: GPIO25
      inverted: true
    reset_pin: GPIO26
    model: 7.50in-bv2-rb
    reset_duration: 2ms
    update_interval: never
    rotation: 0
    lambda: |-
      it.fill(COLOR_OFF);
      // Note: Due to firmware quirk, Color::WHITE renders as black
      it.image(0, 0, id(puppy_black_layer), Color::WHITE);
      it.image(0, 0, id(puppy_red_layer), CUSTOM_RED);

script:
  - id: refresh_screen
    mode: restart
    then:
      - component.update: epaper_display

button:
  - platform: template
    name: "Force Display Update"
    on_press:
      - script.execute: refresh_screen

switch:
  - platform: template
    name: "Display Image"
    optimistic: true
    turn_on_action:
      - script.execute: refresh_screen
    turn_off_action:
      - script.execute: refresh_screen

## Upload Configuration
1. Connect ESP32 to PC via USB.
2. Open ESPHome Dashboard.
3. Select `epaper-display` device.
4. Click **Edit**, paste the YAML config.
5. Click **Install** → **Upload** via USB or OTA.

## Testing
- Upon successful upload, the display should show the combined black and red image.
- Use the "Force Display Update" button to refresh the screen.

## Troubleshooting
- **Memory Issues:** Use `TRANSPARENT_BINARY` to reduce memory usage. Simplify images if necessary.
- **Display Not Rendering Correctly:** Ensure images have transparent backgrounds and correct color isolation. Remember to use `Color::WHITE` for black areas.
- **GPIO Warnings:** If using strapping pins like GPIO15 causes issues, consider reassigning if possible.

## Tips
- **Optimize Images:** Keep image dimensions as needed to balance quality and memory usage.
- **Monitor Logs:** Use ESPHome logs for debugging display issues.
- **Community Support:** Engage with ESPHome forums for advanced troubleshooting.
- **Image Prompt for ChatGPT:**
  Create a posterized version of the uploaded image in three colors: black, red, and white, with the following specifications:

  Separate the image into two layers only:

  Black Layer: Contains only black areas, with transparent background for all non-black regions.
  Red Layer: Contains only red areas, with transparent background for all non-red regions.
  White areas should be transparent in both layers, so there is no separate white layer.

  Save each layer separately in PNG format with transparency. Return links to the two final PNGs: one for the Black Layer and one for the Red Layer.

## Conclusion
By splitting your image into separate transparent layers and using memory-efficient image types, you can effectively display multi-color images on a Waveshare E-Paper Display with ESPHome and ESP32. Remember to handle black areas using `Color::WHITE` due to the firmware quirk to ensure accurate rendering.
