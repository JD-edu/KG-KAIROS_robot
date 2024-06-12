#ifndef NDelayFunc_h_
#define NDelayFunc_h_

class NDelayFunc {
  unsigned long t_prev;
  const unsigned long t_delay;
  void (* func)();

public:
  NDelayFunc(
	const unsigned long t_delay,
	void (* func)());
	
  void run();
};

#endif