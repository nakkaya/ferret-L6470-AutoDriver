(native-header "SPI.h"
               "SparkFunAutoDriver.h")

(defobject driver_o "ferret-L6470-AutoDriver/driver_o.h")

(defn driver [pos cs reset]
  "__result = obj<driver_o>(number::to<number_t>(pos),
                            number::to<number_t>(cs),
                            number::to<number_t>(reset));")

(defn use-external-clock [b]
  "b.cast<driver_o>()->use_external_clock();")

(defn run [b s]
  "b.cast<driver_o>()->run(number::to<number_t>(s));")

(defn soft-stop [b]
  "b.cast<driver_o>()->soft_stop();")

(defn busy? [b]
  "__result = b.cast<driver_o>()->busy_check();")
