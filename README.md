# ESPHome TCR component

This repo contains a simple component definition for the [Tiny Code Reader from Useful Sensors](https://github.com/usefulsensors/tiny_code_reader_docs/blob/main/README.md) to be used with [ESPHome](https://esphome.io/).

## Setup

- Connect 3.3 V and GND pins on the TCR to appropriate pins on the ESP device.
- Connect SDA and SCL pins on the TCR to any availalbe GPIOs on the ESP. Use the corresponding pinout schema for your ESP device.

## Configuration

### Add external component

To add this repository as an external component add the following to your yaml configuration.

```yaml

external_components:
  - source: github://timum-viw/esphome-tcr@main
    components: [ tcr ]

```

### Setup I2C Bus

The Tiny Code Reader uses the I2C Interface which means you have to add a [i2c](https://esphome.io/components/i2c.html) bus to your configuration.

```yaml
i2c:
  sda: GPIO04
  scl: GPIO05
  # use scan to check for the tcr device. If everything is connected properly, it should be found on address 0x0c.
  scan: true
```

If no device is found while scanning make sure the selected GPIOs are correctly connected. You might have to switch SDA and SCL lines.
According to the specs of the TCR frequencies up to 400 kHz are supported, although going above 50 kHz resulted in increasing numbers of errors for me.
See the [docs for the i2c bus component](https://esphome.io/components/i2c.html) for more configuration options.

### Add component

To add the TCR to your to your configuration, add the following lines:

```yaml
text_sensor:
  - platform: tcr
    name: "qr code"
```

The TCR component is implemented as a [text_sensor](https://esphome.io/components/text_sensor/) platform, which means it will output any qr code reads as a text string (UTF-8 encoded). You can add any option like filters from the [text_sensor](https://esphome.io/components/text_sensor/) component.

## Example

You can find a basic [example](/tcr.yaml) configuration that will write the qr code text to the logger. So if you're connected to your ESP device through serial you will find the reads in the terminal.

## Known Issues

For some reason I was only able to read up to 128 bytes from the TCR. The full output should be 256 bytes but for me this will result in timeout issues. Updating the ```timeout``` option of the i2c bus did not fix this issue.

The component polls every 500ms. So there is a chance with unfortunate timeing to miss a read if the code is only presented very shortly.

The TCR is not perfect. Sometimes reads will have messed up bytes in them. Make sure to validate any reads before further processing.

## Supported Devices

This component should work with any device that can run esphome.
I've successfully used it with:

- ESP8266 
    - nodemcuv2
    - d1_wroom_02

- ESP32 
    - esp32dev