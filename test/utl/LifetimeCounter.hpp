#pragma once

namespace utl_test {
	
	struct __LifetimeCounterBase {
		bool _doCount = true;
		bool operator==(__LifetimeCounterBase const&) const = default;
	};

	 class LifetimeCounter: __LifetimeCounterBase {
	 public:
		 LifetimeCounter() {
			 _inc();
		 }
		 
		 explicit LifetimeCounter(bool doCount): __LifetimeCounterBase{ doCount } {
			 _inc();
		 }
		 
		 LifetimeCounter(LifetimeCounter const& rhs) {
			 _inc();
		 }
		 
		 LifetimeCounter(LifetimeCounter&&) noexcept {
			 _inc();
		 }
		 
		 ~LifetimeCounter() {
			 _dec();
		 }
		 
		 LifetimeCounter& operator=(LifetimeCounter const&) {
			 return *this;
		 }
		 
		 LifetimeCounter& operator=(LifetimeCounter&&) noexcept {
			 return *this;
		 }
		 
		 bool operator==(LifetimeCounter const&) const = default;
		 
		 static int liveObjects() { return _liveObjects; }
		 static void reset() { _liveObjects = 0; }
		 
	 private:
		 void _inc() const {
			 if (_doCount) {
				 ++_liveObjects;
			 }
		 }
		 void _dec() const {
			 if (_doCount) {
				 --_liveObjects;
			 }
		 }
		 static int _liveObjects;
	 };
	
}
