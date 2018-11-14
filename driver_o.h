class driver_o : public object {
  AutoDriver board;
  bool _invert_dir = false;
  bool _disable = false;
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

  void reset(){
    board.resetDev();
  }
  
  void external_clock(){
    board.setOscMode(EXT_16MHZ_OSCOUT_INVERT);
  }

  void invert_dir(){ _invert_dir = !_invert_dir; }

  void disable(){ _disable = true; }
  
  void run(number_t speed){
    if (_disable)
      return;

    if (_invert_dir)
      speed = speed * -1;
    
    if (speed >= 0)
      board.run(FWD, speed);
    else
      board.run(REV, runtime::abs(speed));
  }

  void move(number_t steps){
    if (_disable)
      return;

    if (_invert_dir)
      steps = steps * -1;

    if (steps >= 0)
      board.move(FWD, steps);
    else
      board.move(REV, runtime::abs(steps));
  }
  
  void soft_stop(){
    if (_disable)
      return;
    board.softStop();
  }

  void hard_stop(){
    if (_disable)
      return;
    board.hardStop();
  }
  
  var busy_check(){
    return obj<boolean>(board.busyCheck());
  }

  void reset_pos(){
    board.resetPos();
  }

  var pos(){
    auto pos = board.getPos();
    if (_invert_dir)
      pos = pos * -1;
    
    return obj<number>(pos);
  }

  void speed(real_t steps_per_sec){
    board.setMinSpeed(0);
    board.setMaxSpeed(steps_per_sec);
    board.setFullSpeed(0x027);
    board.setAcc(0xFFF);
    board.setDec(0xFFF);
  }
};
