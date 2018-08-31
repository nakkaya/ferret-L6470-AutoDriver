Ferret Bindings for SparkFun AutoDriver - Stepper Motor Driver
==========================================

![AutoDriver](https://cdn.sparkfun.com//assets/parts/1/1/2/8/8/13752-01a.jpg)  

[*AutoDriver (BOB-11611)*](https://www.sparkfun.com/products/11611)

The AutoDriver is a bipolar stepper driver based on the ST Micro L6470
chip. It allows a processor to control a single 3A bipolar stepper
motor across an 8-45V supply range.

    (require '[ferret.arduino :as gpio]
             '[ferret-L6470-AutoDriver.core :as driver])

    (gpio/spi-begin)

    (def motor (driver/driver 0 2 3))

    ;; 500 steps forward
    (driver/move motor 500)

See `core.clj` for supported functions. Due to they way Arduino IDE
works, you need to copy all `SparkFun*` files to a folder under your
Arduino libraries folder.

Documentation
--------------
* **[Library](https://github.com/sparkfun/SparkFun_AutoDriver_Arduino_Library)** - Arduino library for the AutoDriver.
* **[Hookup Guide](https://learn.sparkfun.com/tutorials/getting-started-with-the-autodriver---v13)** - Basic hookup guide for the Auto Driver.
* **[SparkFun Fritzing repo](https://github.com/sparkfun/Fritzing_Parts)** - Fritzing diagrams for SparkFun products.
* **[SparkFun 3D Model repo](https://github.com/sparkfun/3D_Models)** - 3D models of SparkFun products. 
* **[SparkFun Graphical Datasheets](https://github.com/sparkfun/Graphical_Datasheets)** -Graphical Datasheets for various SparkFun products.
