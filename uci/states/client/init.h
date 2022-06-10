#pragma once

#include "base.h"

namespace uci
{
	namespace states
	{
		namespace client
		{
			class Init : public Base
			{
			public:
				void init() override;

				uci::states::Base::States update() override;

				void terminate() override;

			private:
			};
		} // namespace client
	} // namespace states
} // namespace uci