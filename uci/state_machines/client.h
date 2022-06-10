#pragma once

#include "state_machine_base.h"

#include <iostream>
#include <string>

namespace uci
{
	namespace state_machines
	{
		class ClientStateMachine 
		{
		public:

			void init(const std::string& engine_exe);

			//StateBase::States update();

		private:
		};
	} // namespace state_machines
} // namespace uci