(native-header "SPI.h"
               "SparkFunAutoDriver.h")

(defobject driver_o "ferret-L6470-AutoDriver/driver_o.h")

(defn driver [p c r]
  "__result = obj<driver_o>(number::to<number_t>(p),
                            number::to<number_t>(c),
                            number::to<number_t>(r));")

(defn reset [b]
  "b.cast<driver_o>()->reset();")

(defn external-clock [b]
  "b.cast<driver_o>()->external_clock();")

(defn invert-dir [b]
  "b.cast<driver_o>()->invert_dir();")

(defn run [b s]
  "b.cast<driver_o>()->run(number::to<number_t>(s));")

(defn move [b s]
  "b.cast<driver_o>()->move(number::to<number_t>(s));")

(defn soft-stop [b]
  "b.cast<driver_o>()->soft_stop();")

(defn hard-stop [b]
  "b.cast<driver_o>()->hard_stop();")

(defn busy? [b]
  "__result = b.cast<driver_o>()->busy_check();")

(defn reset-pos [b]
  "b.cast<driver_o>()->reset_pos();")

(defn pos [b]
  "__result = b.cast<driver_o>()->pos();")

(defn speed [b s]
  "b.cast<driver_o>()->speed(number::to<real_t>(s));")
