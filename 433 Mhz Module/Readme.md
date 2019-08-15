# 433 Mhz Modules
[these]: /url "https://www.amazon.com/UCEC-XY-MK-5V-Transmitter-Receiver-Raspberry/dp/B017AYH5G0/ref=sr_1_1_sspa?crid=3MDRJEGJM7CT7&keywords=433mhz+transmitter+and+receiver&qid=1562610321&s=gateway&sprefix=433+mhz+%2Caps%2C155&sr=8-1-spons&psc=1"
[Manchester Encoding library]: /url "https://github.com/mchr3k/arduino-libs-manchester"
[BME280 I2C library]: /url "https://www.14core.com/wiring-the-bme280-environmental-sensor-using-i2cspi-interface-with-microcontroller/"
[TinySnore Library]: /url "https://github.com/connornishijima/TinySnore"
We're using [these] cheap Tx/Rx modules from Amazon for our tests. After testing the modules within the sweet potato crates, this readme will be updated with how they performed.

The code here utilizes the [Manchester Encoding library], the [BME280 I2C library], and the [TinySnore library].

The Manchester Encoding library is not licensed. As such, I have encluded it here through Github's terms regarding the forking/cloning of unlicensed code. Furthermore, the code no longer needs to be used in this non-commercial research project and it is included solely for the purposes of thorough prototype documentation as opposed to distribution.

The BME280 library code is licensed under the Creative Commons Attribution Non-Commercial 3.0 License (http://creativecommons.org/licenses/by-nc-sa/3.0/).

The TinySnore library is licensed under the GPL. I have encluded the GPL in the LICENSE file in this folder.
