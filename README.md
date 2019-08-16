# Sweet Potato Sensor

When stored and cured, sweet potatoes need to be kept at a certain temperature and humidity level to ensure that they don't go bad.
Traditionally, sweet potatoes have had their temperature and humidity monitored via sensors that reside outside of the crates in which the potatoes are stored in, but wouldn't it be great if you could monitor the temperature and humidity levels within the storage crates? This sounds simple enough, but there's a catch--raw sweet potatoes have lots of water in them, and high-frequency RF transmitters (like a Bluetooth module) won't transmit very far at all. Over the summer of 2019, I worked as temporary undergraduate researcher at NC State University to identify if transmitters operation at a frequency of 433 Mhz were viable as a means of monitoring the temperature and humidity of sweet potatoes being shipped across the world in shipping containers.

# Current Project Status
You can read all about my struggles, and the information I learned about each of the components I used, in [this](https://github.com/will7007/Sweet-Potato-Sensor/blob/master/Public%20Copy%20of%20Sweet%20Potato%20Temperature%20Tracking.pdf) PDF. I eventually got my amateur radio license in order to achieve 50+ feet of range with a 433 Mhz LoRa radio underneath ~2 feet of sweet potatoes in a metal refridgerator. Note that off-the-shelf Bluetooth temperature sensors were not able to penetrate even a few sweet potatoes at all.

Even though I have stopped work on the project to return to school, this project is still technically in progress, and I (or another student) may pick it up later to fine-tune the code and create a more final version of the sensor.

# Licensing
Each of the components I used had different libraries that worked best on the AtTiny85. Please see each of the component folders for more information.
