#include <utl/vector.hpp>
#include <utl/functional.hpp>

#include <mtl/mtl.hpp>
#include <iostream>

#include <any>
#include <memory>
#include <unordered_map>

struct Expression {
	virtual ~Expression() = default;
	
	virtual std::any evaluate() const = 0;
};


class Variable: public Expression {
public:
	Variable(std::any value): _value(std::move(value)) {}
	
	std::any evaluate() const override { return _value; }

private:
	std::any _value;
};


template <std::size_t, typename>
class __OperationImpl;

template <std::size_t Arity, std::size_t... I>
class __OperationImpl<Arity, std::index_sequence<I...>>: public Expression {
public:
	template <typename T, std::size_t>
	using __PassType = T;
	__OperationImpl(__PassType<std::unique_ptr<Expression>, I>... operands): __operands(std::move(operands)...) {}
	
	std::any evaluate() const override { return __operation(std::get<I>(__operands)->evaluate()...); }
	
private:
	std::tuple<__PassType<std::unique_ptr<Expression>, I>...> __operands;
	std::function<std::any(__PassType<std::any, I> const&...)> __operation;
};


template <std::size_t Arity>
class Operation: public __OperationImpl<Arity, std::make_index_sequence<Arity>> {
public:
	using __Base = __OperationImpl<Arity, std::make_index_sequence<Arity>>;
	using __Base::__Base;
	
	using __Base::evaluate;
};


struct Token {
	enum class Type {
		name, openingBrace, closingBrace, openingParan, closingParan, operatorPlus
	};
	Type type;
	
};

std::unordered_map

std::vector<Token> parse(char const* text) {
	while (text != )
}



char const* MyScript = R"(
int x = 1 + 2;
)";

int main() {

	
	
}

