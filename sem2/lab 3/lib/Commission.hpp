#pragma once
#include <string>
#include <vector>

using vec = std::vector<std::string>;

namespace lib {
	class Commission {
	public:
		// ctor default
		Commission();
		// ctor param
		Commission(int time_to_check, const std::string& address, const vec ban_ingredient);
		// ctor copy
		Commission(const Commission& other);

		// dtor
		~Commission();

		//------------------------------------------------------------------------------------------------------------------------------------------------------

		void Legit_check(int expiration_days, const std::string& name);

	private:
		int time_to_check_;
		std::string address_;
		vec ban_ingredient_;
	};
}//namespase lib
