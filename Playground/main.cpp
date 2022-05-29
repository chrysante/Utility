#include <iostream>

#include <optional>
#include <typeindex>

struct X{};
struct Y{};

struct Object {
	
};

#if 0
#define PURE { assert(false && "Don't call me"); }
#else
#define PURE = 0
#endif

struct Renderer {
	Renderer() = default;
	Renderer(Renderer const&) = delete;
	virtual ~Renderer() = default;
	virtual void begin() PURE;
	virtual void submit(Object const&) PURE;
	virtual void draw() PURE;
};

struct ForwardRenderer: Renderer {
	void begin() override {
		
	}
	void submit(Object const&) override {
		
	}
	void draw() override {
		
	}
};

struct ObjectDebugData {
	bool selected = false;
};

struct DebugRenderer: Renderer {
	explicit DebugRenderer(Renderer& renderer):
		mRenderer(&renderer) { assert(mRenderer != this); }
	void begin() override {
		mRenderer->begin();
	}
	void submit(Object const& obj) override {
		submit(obj, ObjectDebugData{});
	}
	void submit(Object const& obj, ObjectDebugData const& debugData) {
		mRenderer->submit(obj);
		submitDebugData(debugData);
	}
	void draw() override {
		static int i = 0;
		if (i++ == 100) throw std::runtime_error("");
		mRenderer->draw();
		drawDebug();
	}
	
private:
	void submitDebugData(ObjectDebugData const&) {}
	void drawDebug() {}
	
private:
	Renderer* mRenderer = nullptr;
};

int main() {

	std::unique_ptr<Renderer> mRenderer = std::make_unique<ForwardRenderer>();
	auto& renderer = *mRenderer;

	DebugRenderer debugRenderer(renderer);

	debugRenderer.begin();
	debugRenderer.submit(Object{}, ObjectDebugData{});
	
	debugRenderer.draw();
	
	
//	std::aligned_storage<sizeof(DebugRenderer), alignof(DebugRenderer)> storage;
//	Renderer& renderer = *reinterpret_cast<DebugRenderer*>(&storage);
//	::new ((void*)&storage) DebugRenderer(renderer);
//
//	renderer.draw();
}
