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
    board.setMinSpeed(0);
    board.setMaxSpeed(200);                   // 200 steps/s max
    board.setFullSpeed(0x027);
    board.setAcc(0xFFF);
    board.setDec(0xFFF);
    board.setSlewRate(SR_530V_us);             // Upping the edge speed increases torque.
    board.setOCThreshold(OC_6000mA);            // OC threshold 750mA
    board.setPWMFreq(PWM_DIV_2, PWM_MUL_2);    // 31.25kHz PWM freq
    board.setOCShutdown(OC_SD_DISABLE);        // don't shutdown on OC
    board.setVoltageComp(VS_COMP_DISABLE);     // don't compensate for motor V
    board.setSwitchMode(SW_USER);              // Switch is not hard stop
    board.setOscMode(INT_16MHZ_OSCOUT_16MHZ);  // for board, we want 16MHz
    // We'll tinker with these later, if needed.
    board.setAccKVAL(255);
    board.setDecKVAL(255);
    board.setRunKVAL(255);
    // This controls the holding current; keep it low.
    board.setHoldKVAL(32);
    board.softStop();
  }

  void reset_dev(){
    board.resetDev();
  }
  
  void use_external_clock(){
    board.setOscMode(EXT_16MHZ_OSCOUT_INVERT);
  }

  void run(number_t speed){
    if (speed >= 0)
      board.run(FWD, speed);
    else
      board.run(REV, runtime::abs(speed));
  }

  void move(number_t steps){
    if (steps >= 0)
      board.move(FWD, steps);
    else
      board.move(REV, runtime::abs(steps));
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

  void reset_pos(){
    board.resetPos();
  }

  var get_pos(){
    return obj<number>(board.getPos());
  }

  void set_speed(real_t steps_per_sec){
    board.setMinSpeed(0);
    board.setMaxSpeed(steps_per_sec);
    board.setFullSpeed(0x027);
    board.setAcc(0xFFF);
    board.setDec(0xFFF);
  }
};
