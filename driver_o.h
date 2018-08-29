class driver_o : public object {
  
 public:

  size_t type() const { return runtime::type::driver_o; }

  bool equals(var const & o) const { return (this == o.get()); }

#if !defined(FERRET_DISABLE_STD_OUT)
  void stream_console() const {
    runtime::print("driver");
  }
#endif

  explicit driver_o() {
  }
};
