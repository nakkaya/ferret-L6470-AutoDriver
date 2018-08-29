class driver_o : public object {
  AutoDriver board;
 public:

  size_t type() const { return runtime::type::driver_o; }

  bool equals(var const & o) const { return (this == o.get()); }

#if !defined(FERRET_DISABLE_STD_OUT)
  void stream_console() const {
    runtime::print("driver");
  }
#endif

  explicit driver_o(number_t position, number_t CSPin, number_t resetPin) :
    board(position, CSPin, resetPin){
    pinMode(resetPin, OUTPUT);
    pinMode(CSPin, OUTPUT);
    digitalWrite(CSPin, HIGH);
    digitalWrite(resetPin, LOW);
    digitalWrite(resetPin, HIGH);
    // Before doing anything else, we need to
    //  tell the objects which SPI port to use.
    //  Some devices may have more than one.
    board.SPIPortConnect(&SPI);

    // BUSY pin low during operations;
    // second paramter ignored.
    board.configSyncPin(BUSY_PIN, 0);
    board.configStepMode(STEP_FS);             // 0 microsteps per step
    board.setMaxSpeed(10000);                  // 10000 steps/s max
    board.setFullSpeed(10000);                 // microstep below 10000 steps/s
    board.setAcc(10000);                       // accelerate at 10000 steps/s/s
    board.setDec(10000);
    board.setSlewRate(SR_530V_us);             // Upping the edge speed increases torque.
    board.setOCThreshold(OC_750mA);            // OC threshold 750mA
    board.setPWMFreq(PWM_DIV_2, PWM_MUL_2);    // 31.25kHz PWM freq
    board.setOCShutdown(OC_SD_DISABLE);        // don't shutdown on OC
    board.setVoltageComp(VS_COMP_DISABLE);     // don't compensate for motor V
    board.setSwitchMode(SW_USER);              // Switch is not hard stop
    board.setOscMode(INT_16MHZ_OSCOUT_16MHZ);  // for board, we want 16MHz
    // We'll tinker with these later, if needed.
    board.setAccKVAL(128);
    board.setDecKVAL(128);
    board.setRunKVAL(128);
    // This controls the holding current; keep it low.
    board.setHoldKVAL(32); 
  }

  void use_external_clock(){
    board.setOscMode(EXT_16MHZ_OSCOUT_INVERT);
  }

  void run(number_t speed){
    if (speed >= 0)
      board.run(FWD, speed);
    else
      board.run(REV, speed);
  }
  
  void soft_stop(){
    board.softStop();
  }

  void hard_stop(){
    board.hardStop();
  }
  
  var busy_check(){
    return obj<boolean>(board.busyCheck());
  }
};
