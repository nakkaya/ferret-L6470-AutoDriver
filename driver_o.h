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

    board.SPIPortConnect(&SPI);
    board.configSyncPin(BUSY_PIN, 0);
    board.configStepMode(STEP_FS);
    board.setMinSpeed(0);
    board.setMaxSpeed(200);
    board.setFullSpeed(0x027);
    board.setAcc(0xFFF);
    board.setDec(0xFFF);
    board.setOCThreshold(OC_6000mA);
    board.setOscMode(INT_16MHZ_OSCOUT_16MHZ);
    board.setAccKVAL(254);
    board.setDecKVAL(254);
    board.setRunKVAL(254);
    board.setHoldKVAL(32);
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
