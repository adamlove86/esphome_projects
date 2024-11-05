# Bathroom Node v2 Xiao

Automates bathroom functions, including motion detection, temperature, humidity, and environmental monitoring using ESPHome.

## Overview

The Bathroom Node v2 Xiao is an ESPHome-based project that monitors motion, temperature, humidity, and additional environmental parameters in the bathroom. It integrates seamlessly with Home Assistant, providing real-time data and enabling automations tailored to bathroom use.

## Features

- **Motion Detection**: Utilizes a 24GHz mmWave XIAO Radar (LD2410) to detect motion and presence in the bathroom, even through barriers. This radar provides distinct detections for moving and still targets, making it highly accurate for occupancy sensing.
- **Temperature and Humidity Monitoring**: Employs a DHT22 (AM2302) sensor for tracking temperature and humidity levels, with safeguards to reject out-of-range values to ensure accurate readings.
- **Home Assistant Integration**: Easily integrates with Home Assistant, enabling responsive automations based on real-time sensor data.
- **Local Web Server**: Hosts a local web interface for live monitoring and diagnostics, accessible over the network.
- **Over-The-Air (OTA) Updates**: Supports OTA updates for convenient firmware upgrades without physical access to the device.
- **Flashing LED Indicator**: The onboard LED flashes on detecting motion, signaling active presence detection to the user.
- **Verbose Logging**: Enhanced logging for sensor data, including LD2410 motion detection readouts, helps in monitoring and troubleshooting.

## Configuration Details

- **24GHz mmWave XIAO Radar (LD2410)**: Configured to provide detailed motion data (distance, energy levels, and specific zone thresholds) and includes an engineering mode for advanced calibration.
- **DHT22 Temperature & Humidity Sensor**: Connected via GPIO22, with a sliding window moving average filter for stable output, and configured to reject extreme temperature and humidity values that fall outside typical bathroom conditions.
- **LED Notification**: An onboard LED flashes in response to detected motion, helping visually confirm sensor activity and bathroom occupancy status.

This project offers a reliable and compact solution for monitoring bathroom conditions, with enhanced functionality and integration for a responsive, smart bathroom environment.

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
