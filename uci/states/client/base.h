#pragma once

#include "../base.h"

namespace uci
{
	namespace states
	{
		namespace client
		{
			class Base : uci::states::Base
			{
			public:
				virtual void init() = 0;

				virtual Base::States update() = 0;

				virtual void terminate() = 0;

			private:
			};
		} // namespace client
	} // namespace states
} // namespace uci