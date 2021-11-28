/**
 * @brief Manage timing efficiently instead of using delays
 */
class Timer {
	private:
		long unsigned int t0 = 0;
		long unsigned int t1 = 0;
		double current_value = 0;
		bool current_value_init = false;
		bool enabled = true;

	public:
		Timer() {
			this->t0 = millis();
		}
		/**
		 * @brief Repeat a callback in a constat time intervals in milliseconds
		 * 
		 * @param interval 
		 * @param callback a call back to be repeated
		 */
		void setInterval (int interval, void(*callback)()) {
			if ( this->enabled && millis() >= this->t0 + interval ) {
				callback();
				this->t0 = millis();
			}
		}

		/**
		 * @brief Repeat a callback N times in a fixed time interval (frequency)
		 * 
		 * @param times 
		 * @param time 
		 * @param callback
		 */
		void repeatIn (int times, int time, void (*callback)()) {
			const int interval = time/times;
			this->setInterval (interval, callback);
		}

		/**
		 * @brief Like repeatIn but it maps a value while it's looping
		 * 
		 * @param res 		resolution
		 * @param time 
		 * @param start 	minimum value
		 * @param end 		maximum value
		 * @param callback 
		 * @param finishCallback 
		 */
		void reachIn (int res, int time, double start, double end, 
			void (*callback)(double), void (*finishCallback)() = [](){} ) 
		{
			const int interval = time/res;
			const double inc = (end-start)/res;
			if ( !this->current_value_init ) {
				this->t1 = millis();
				this->current_value_init = true;
				this->current_value = start;
			}
			const double val = this->current_value + inc;
			if ( this->enabled && millis() >= this->t1 + interval 
				&& ( (val <= end && inc > 0) || (val >= end && inc < 0) ) 
			) {
				callback(val);
				this->current_value = val;
				this->t1 = millis();
			} else if ( this->enabled 
				&& ( (val > end && inc > 0) || (val < end && inc < 0) ) 
			) {
				finishCallback();
			}
		}

		void block () { this->enabled = false; }
		void resume () { this->enabled = true; }
		void reset () {
			this->t0 = millis();
			this->t1 = millis();
			this->current_value = 0;
			this->current_value_init = false;
		}
};
