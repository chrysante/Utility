#pragma once

#include <utl/pimpl.hpp>

namespace engine {
	
	class Texture {
	public:
		Texture();
		Texture(Texture const&) = delete;
		~Texture();
		
		void bind();
		void* native();
		
	public:
		class Impl;
		
	private:
		utl::local_pimpl<Impl, 16, 8> _impl;
	};
	
}
