# Quick Setup Guide: Waveshare E-Paper Display with ESPHome and ESP32

## Prerequisites
- **Hardware:**
  - ESP32 Development Board (e.g., esp32dev)
  - Waveshare 7.50in-bv2-rb E-Paper Display
  - Connecting wires
  - Power supply
- **Software:**
  - ESPHome installed
  - Image editor (GIMP, Photoshop), or use the prompt below to put the image into chatgpt.

## Image Preparation
1. **Split Image into Layers:**
   - **Black Layer:** Contains only black parts, background transparent.
   - **Red Layer:** Contains only red parts, background transparent.
2. **Save as PNG:**
   - Ensure transparency is preserved.
   - Use `TRANSPARENT_BINARY` type for ESPHome.

**Firmware Quirk:** Due to a firmware quirk, black areas in your images should be rendered using `Color::WHITE` in the ESPHome configuration.

## ESPHome Configuration Overview
The configuration uses ESPHome to control the Waveshare E-Paper display connected to an ESP32 board. Below are some key parts of the configuration:

- **External Components:** The Waveshare e-paper display component is integrated from a GitHub repository.
- **Connectivity:** The ESP32 connects to WiFi, and a fallback AP mode is defined in case WiFi is unavailable.
- **Logging and OTA Updates:** Logs are configured for debugging, and Over-The-Air (OTA) updates are enabled for convenience.
- **SPI Configuration:** SPI interface pins for CLK and MOSI are defined.
- **Images and Colors:** Separate black and red layers are defined, and `CUSTOM_RED` is used to render the red color on the display.

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

### Image Prompt for ChatGPT
Create a posterized version of the uploaded image in three colors: black, red, and white, with the following specifications:

- Separate the image into two layers only:
  - **Black Layer:** Contains only black areas, with transparent background for all non-black regions.
  - **Red Layer:** Contains only red areas, with transparent background for all non-red regions.
- White areas should be transparent in both layers, so there is no separate white layer.
- Save each layer separately in PNG format with transparency. Return links to the two final PNGs: one for the Black Layer and one for the Red Layer.

## Conclusion
By splitting your image into separate transparent layers and using memory-efficient image types, you can effectively display multi-color images on a Waveshare E-Paper Display with ESPHome and ESP32. Remember to handle black areas using `Color::WHITE` due to the firmware quirk to ensure accurate rendering.
