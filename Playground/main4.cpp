#include <cstdint>

#include <array>
#include <iostream>
#include <vector>
#include <setjmp.h>

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

template <typename T>
T read(void const* ptr) {
	std::aligned_storage_t<sizeof(T), alignof(T)> storage;
	std::memcpy(&storage, ptr, sizeof(T));
	return reinterpret_cast<T const&>(storage);
}

template <typename T>
void store(void* dest, T const& t) {
	std::memcpy(dest, &t, sizeof(T));
}


struct Type {
	enum EnumType: u8 {
		Void, Bool, Int, Float, String
	};
	
	static constexpr auto sizeTable = []{
		return std::array{
			0, 1, 8, 8, 24
		};
	}();
	
	Type(): type(Void), size(0) {}
	explicit Type(EnumType type): type(type), size(sizeTable[u64(type)]) {}
	
	EnumType type;
	u8 size;
};

struct Expression {
	using NodeFnPtr = void(*)(Expression& self, void* out, void const* in);
	i8 numArgs = 0;
	Type type;
	
	union {
		Expression* children[3];
		void* dataPtr;
	};
	
	NodeFnPtr function = nullptr;
	
	void eval(void* out);
};

void Expression::eval(void* out) {
	u8* argBuffer = (u8*)alloca(8 * numArgs);
	for (int i = 0; i < numArgs; ++i) {
		children[i]->eval(argBuffer + 8 * i);
	}
	function(*this, out, argBuffer);
}

struct Variable {
	static constexpr std::size_t localBufferSize = 8;
	
	explicit Variable(Type type): type(type), bufferPtr(type.size <= localBufferSize ? &localBuffer : std::malloc(type.size)) {}
//	~Variable() { if (type.size > localBufferSize) { std::free(bufferPtr); } }
	
	Type type;
	void* bufferPtr;
	char localBuffer[localBufferSize];
};

struct Statement {
	virtual void execute() = 0;
};

struct VariableDeclaration: Statement {
	VariableDeclaration(Variable v, Expression initExpr) :var(v), initExpr(initExpr) {}
	
	void execute() override {
		initExpr.eval(var.bufferPtr);
	}
	
	Variable var;
	Expression initExpr;
};

Expression variableReference(Variable const& var) {
	Expression result;
	result.type = var.type;
	result.dataPtr = var.bufferPtr;
	result.function = [](Expression& self, void* out, void const* in) {
		std::memcpy(out, self.dataPtr, self.type.size);
	};
	return result;
}

struct ExpressionStatement: Statement {
	void execute() override {
		void* buffer = alloca(expr.type.size);
		expr.eval(buffer);
		(void)buffer;
	}
	Expression expr;
};

struct StatementBlock: Statement {
	void execute() override {
		for (auto s: statements) {
			s->execute();
		}
	}
	
	void add(Statement* s) { statements.push_back(s); }
	
	std::vector<Statement*> statements;
};

struct ControlFlowStatement: Statement {};


struct JumpBuffer {
	bool set() {
		return !setjmp(buffer);
	}
	[[noreturn]] void jump() { longjmp(buffer, 1); }
	
	jmp_buf buffer;
};

struct Function;

struct ReturnStatement: ControlFlowStatement {
	ReturnStatement(Function& function, Expression expr, void* valueDest);
	
	[[noreturn]] void execute() override;
	
	Expression expr;
	Function* function;
};

struct IfStatement: ControlFlowStatement {
	void execute() override {
		bool cond;
		condition.eval(&cond);
		if (cond) {
			ifBlock.execute();
		}
		else {
			thenBlock.execute();
		}
	}
	Expression condition;
	StatementBlock ifBlock, thenBlock;
};

struct Function {
	void invoke(void* out);
	
	Type returnType;
	void* out;
	std::vector<Variable> arguments;
	StatementBlock statements;
	JumpBuffer jumpBuffer;
};

void Function::invoke(void* out) {
	this->out = out;
	if (jumpBuffer.set()) {
		statements.execute();
	}
}

ReturnStatement::ReturnStatement(Function& function, Expression expr, void* valueDest):
	expr(expr),
	function(&function)
{}

void ReturnStatement::execute() {
	expr.eval(function->out);
	function->jumpBuffer.jump();
}

int main() {
//
//	Expression* arg1 = new Expression{
//		.numArgs = 0,
//		.type = Type{ Type::Int },
//		.children = {},
//		.function = [](void* out, void const*) {
//			store(out, i64(7));
//		}
//	};
//
//	Expression* arg2 = new Expression{
//		.numArgs = 0,
//		.type = Type{ Type::Int },
//		.children = {},
//		.function = [](void* out, void const*) {
//			store(out, i64(3));
//		}
//	};

	Expression mulExpr = {
		.numArgs = 2,
		.type = Type{ Type::Int },
		.children = {  },
		.function = [](Expression& self, void* out, void const* in) {
			auto const args = read<std::array<i64, 2>>(in);
			store(out, args[0] * args[1]);
		}
	};
	
	Function myFunction;
	myFunction.arguments = { Variable(Type(Type::Int)), Variable(Type(Type::Int)) };
	myFunction.returnType = Type(Type::Int);

	
	
	auto* varDecl = new VariableDeclaration(Variable(Type(Type::Int)), mulExpr);
	myFunction.statements.add(varDecl);
	varDecl->initExpr.children[0] = new Expression(variableReference(myFunction.arguments[0]));
	varDecl->initExpr.children[1] = new Expression(variableReference(myFunction.arguments[1]));
	myFunction.statements.add(new ReturnStatement(myFunction, variableReference(varDecl->var), nullptr));
	
	u64 x;
	x = 5;
	std::memcpy(myFunction.arguments[0].bufferPtr, &x, 8);
	x = 7;
	std::memcpy(myFunction.arguments[1].bufferPtr, &x, 8);
	myFunction.invoke(&x);
	
	std::cout << x << std::endl;
	
}
