#include "test.hpp"


#include <utl/__debug.hpp>

void glbind(void*) {}

namespace engine {

	enum class RenderAPI {
		opengl, directx, metal, vulkan
	};
	
	RenderAPI globalRenderAPI() { return RenderAPI::metal; }
	
	/// MARK: Implementation Interface
	class Texture::Impl {
	public:
		virtual void* native() = 0;
		virtual void bind() = 0;
		virtual ~Impl() = default;
	};
	
	/// MARK: Implementation Metal
	class MetalTexture: public Texture::Impl {
	public:
		MetalTexture(void* device) {
			_native = nullptr;
		}
		
		void* native() final {
			return  _native;
		}
		
		void bind() final {
			
		}
		
	private:
		void* _native;
	};
	
	/// MARK: Wrapper
	Texture::Texture(): _impl(utl::no_init) {
		switch (globalRenderAPI()) {
			case RenderAPI::metal:
				_impl.construct<MetalTexture>(nullptr);
			default:
				__utl_debugbreak("Invalid Render API");
		}
	}
	
	Texture::~Texture() = default;
	
	void Texture::bind() {
		_impl->bind();
	}
	
	void* Texture::native() {
		return _impl->native();
	}

}
