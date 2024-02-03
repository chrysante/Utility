#ifndef UTL_DYNCAST_HPP_
#define UTL_DYNCAST_HPP_

#include <cassert>
#include <cstddef>
#include <type_traits>
#include <typeinfo> // For std::bad_cast
#include <utility>

/// Declares a mapping of \p type to its identifier \p ID
#define UTL_DYNCAST_IMPL_MAP(Type, ID)                                         \
    template <>                                                                \
    [[maybe_unused]] inline constexpr decltype(ID) utl::dc::TypeToID<Type> =   \
        ID;                                                                    \
    template <>                                                                \
    struct utl::dc::IDToTypeImpl<ID> {                                         \
        using type = Type;                                                     \
    };

/// Declares a mapping of \p type to its parent type \p Parent
#define UTL_DYNCAST_IMPL_PARENT(Type, Parent)                                  \
    template <>                                                                \
    struct utl::dc::TypeToParentImpl<Type> {                                   \
        using type = Parent;                                                   \
    };

/// Declares a mapping of \p type to its corporeality \p CorporealityKind
#define UTL_DYNCAST_IMPL_ABSTRACT(Type, CorporealityKind)                      \
    template <>                                                                \
    [[maybe_unused]] inline constexpr utl::dc::Corporeality                    \
        utl::dc::TypeToCorporeality<Type> =                                    \
            utl::dc::Corporeality::CorporealityKind;

/// User facing macro that declares all mappings defined above
#define UTL_DYNCAST_DEFINE(Type, ID, ParentType, Corporeality)                 \
    UTL_DYNCAST_IMPL_MAP(Type, ID)                                             \
    UTL_DYNCAST_IMPL_PARENT(Type, ParentType)                                  \
    UTL_DYNCAST_IMPL_ABSTRACT(Type, Corporeality)

namespace utl {

namespace dc {

using std::size_t;

/// MARK: - TMP debug utilities

#define UTL_DC_CONCAT(a, b)      UTL_DC_CONCAT_IMPL(a, b)
#define UTL_DC_CONCAT_IMPL(a, b) a##b

#define UTL_DC_CTPrintType(...)                                                \
    ::utl::dc::CTTP<__VA_ARGS__> UTL_DC_CONCAT(ctPrintVar, __LINE__);

#define UTL_DC_CTPrintVal(...)                                                 \
    ::utl::dc::CTVP<__VA_ARGS__> UTL_DC_CONCAT(ctPrintVar, __LINE__);

template <typename...>
struct CTTP;

template <auto...>
struct CTVP;

/// MARK: - General utilities

[[noreturn]] inline void unreachable() {
#if defined(__GNUC__)
    __builtin_unreachable();
#elif defined(_MSC_VER)
    __assume(false);
#else
    assert(false);
#endif
}

#if defined(__GNUC__)
#define UTL_DC_ALWAYS_INLINE __attribute__((always_inline))
#define UTL_DC_NODEBUG_IMPL  __attribute__((nodebug))
#elif defined(_MSC_VER)
#define UTL_DC_ALWAYS_INLINE __forceinline
#define UTL_DC_NODEBUG_IMPL
#else
#define UTL_DC_ALWAYS_INLINE
#define UTL_DC_NODEBUG_IMPL
#endif

/// We define `UTL_DC_NODEBUG` only conditionally so we can disable it in our
/// test and debug code
#if defined(UTL_DC_ENABLE_DEBUGGING)
#define UTL_DC_NODEBUG
#else
#define UTL_DC_NODEBUG UTL_DC_NODEBUG_IMPL
#endif

/// Small and simple array implementation to avoid `<array>` dependency
template <typename T, size_t Size>
struct Array {
    constexpr T& operator[](size_t index) { return elems[index]; }
    constexpr T const& operator[](size_t index) const { return elems[index]; }

    T elems[Size];
};

template <
    typename First, typename... Rest,
    typename = std::enable_if_t<(std::is_same_v<First, Rest> && ...), void>>
Array(First, Rest...) -> Array<First, sizeof...(Rest) + 1>;

/// Compile time `Min` and `Max` implementations to avoid `<algorithm>`
/// dependency
template <size_t...>
inline constexpr auto Min = nullptr;

template <size_t N, size_t M>
inline constexpr size_t Min<N, M> = N < M ? N : M;

template <size_t N, size_t... M>
inline constexpr size_t Min<N, M...> = Min<N, Min<M...>>;

template <size_t...>
inline constexpr auto Max = nullptr;

template <size_t N, size_t M>
inline constexpr size_t Max<N, M> = N > M ? N : M;

template <size_t N, size_t... M>
inline constexpr size_t Max<N, M...> = Max<N, Max<M...>>;

/// https://stackoverflow.com/a/31173086/21285803
template <typename T, typename U>
struct copy_cv_reference {
private:
    using R = std::remove_reference_t<T>;
    using U1 =
        std::conditional_t<std::is_const<R>::value, std::add_const_t<U>, U>;
    using U2 = std::conditional_t<std::is_volatile<R>::value,
                                  std::add_volatile_t<U1>, U1>;
    using U3 = std::conditional_t<std::is_lvalue_reference<T>::value,
                                  std::add_lvalue_reference_t<U2>, U2>;
    using U4 = std::conditional_t<std::is_rvalue_reference<T>::value,
                                  std::add_rvalue_reference_t<U3>, U3>;

public:
    using type = U4;
};

template <typename T, typename U>
using copy_cv_reference_t = typename copy_cv_reference<T, U>::type;

template <typename T>
struct remove_ref_ptr_cv {
    using type = T;
};
template <typename T>
struct remove_ref_ptr_cv<T const>: remove_ref_ptr_cv<T> {};
template <typename T>
struct remove_ref_ptr_cv<T*>: remove_ref_ptr_cv<T> {};
template <typename T>
struct remove_ref_ptr_cv<T&>: remove_ref_ptr_cv<T> {};
template <typename T>
struct remove_ref_ptr_cv<T&&>: remove_ref_ptr_cv<T> {};

template <typename T>
using remove_ref_ptr_cv_t = typename remove_ref_ptr_cv<T>::type;

/// Enum class to denote invalid type IDs
/// This is used internally to indicate the root of an inheritance hierarchy but
/// should not be visible to users.
enum class InvalidTypeID {};

/// Used to identify the base case in `isaImpl()`
template <auto Fallback>
constexpr decltype(Fallback) ValueOr(auto value) {
    return value;
}

/// Base case
template <auto Fallback>
constexpr decltype(Fallback) ValueOr(InvalidTypeID) {
    return Fallback;
}

/// Variadic type list useful for template meta programming
template <typename... T>
struct TypeList {
    TypeList() = default;
    constexpr TypeList(T...)
    requires(sizeof...(T) > 0)
    {}
};

template <typename T, typename...>
struct FirstImpl {
    using type = T;
};

/// Evaluates to the first type in the parameter pack \p T...
template <typename... T>
using First = typename FirstImpl<T...>::type;

template <typename>
struct IndexSequenceToArrayImpl;

template <size_t... I>
struct IndexSequenceToArrayImpl<std::index_sequence<I...>> {
    static constexpr Array<size_t, sizeof...(I)> value = { I... };
};

/// Converts the `std::index_sequence` \p IdxSeq to an
/// `Array<size_t, IdxSeq::size()>`
template <typename IdxSeq>
constexpr Array IndexSequenceToArray = IndexSequenceToArrayImpl<IdxSeq>::value;

/// MARK: - General RTTI implementation

/// Different kinds of _corporeality_. Corporeality is meant to denote the
/// 'class' of abstractness and concreteness.
enum class Corporeality { Abstract, Concrete };

template <typename IDType>
struct DetermineCount;

template <typename IDType>
requires requires { IDType::COUNT; }
struct DetermineCount<IDType> {
    static constexpr size_t value = (size_t)IDType::COUNT;
};

template <typename IDType>
requires(!requires { IDType::COUNT; }) && requires { IDType::LAST; }
struct DetermineCount<IDType> {
    static constexpr size_t value = (size_t)IDType::LAST + 1;
};

/// Common traits of an ID type
template <typename IDType>
struct IDTraits {
    static constexpr size_t count = DetermineCount<IDType>::value;

    static constexpr IDType first = IDType{ 0 };
    static constexpr IDType last = IDType(count);
};

/// MARK: - Maps

/// Maps \p T from the type domain to the identifier domain
template <typename T>
constexpr InvalidTypeID TypeToID{};

template <auto>
struct IDToTypeImpl {
    using type = void;
};

/// Maps \p ID from the identifier domain to the type domain
template <auto ID>
using IDToType = typename IDToTypeImpl<ID>::type;

template <typename>
struct TypeToParentImpl;

/// Maps \p T types to its parent type
template <typename T>
using TypeToParent = typename TypeToParentImpl<T>::type;

/// Maps \p ID to the ID of its parent type
template <typename IDType>
constexpr IDType IDToParent(IDType ID) {
    constexpr Array ParentArray = []<size_t... I>(std::index_sequence<I...>) {
        return Array{ ValueOr<IDTraits<IDType>::last>(
            TypeToID<TypeToParent<IDToType<IDType{ I }>>>)... };
    }(std::make_index_sequence<IDTraits<IDType>::count>{});
    return ParentArray[(size_t)ID];
}

/// Maps \p T to the ID type of its class hierarchy
template <typename T>
using TypeToIDType = decltype(TypeToID<std::decay_t<T>>);

/// Maps \p T to the number of types in its class hierarchy
template <typename T>
constexpr size_t TypeToBound = IDTraits<TypeToIDType<T>>::count;

template <typename... T>
constexpr Array TypesToBounds = { TypeToBound<T>... };

/// Maps \p T to its corporeality
template <typename T>
constexpr Corporeality TypeToCorporeality = Corporeality{ -1 };

/// Maps \p ID to its corporeality
template <auto ID>
constexpr Corporeality IDToCorporeality = TypeToCorporeality<IDToType<ID>>;

/// `true` if \p ID denotes a concrete type
template <auto ID>
constexpr bool IDIsConcrete = IDToCorporeality<ID> == Corporeality::Concrete;

/// `true` if \p ID denotes an abstract type
template <auto ID>
constexpr bool IDIsAbstract = IDToCorporeality<ID> == Corporeality::Abstract;

/// MARK: Concepts to constrain the public interfaces

template <typename T>
concept DynamicImpl =
    !std::is_same_v<remove_ref_ptr_cv_t<decltype(TypeToID<T>)>,
                    InvalidTypeID> &&
    std::is_class_v<T>;

/// Evaluates to `true` if \p T is registered with the RTTI facilities
/// disregarding any cv-ref qualifiers of \p T
template <typename T>
concept Dynamic = DynamicImpl<remove_ref_ptr_cv_t<T>>;

template <typename T, typename U>
concept SharesTypeHierarchyWithImpl =
    DynamicImpl<T> && DynamicImpl<U> &&
    std::same_as<TypeToIDType<T>, TypeToIDType<U>>;

/// Evaluates to `true` if \p T and \p U are registered with the RTTI facilities
/// disregarding any cv-ref qualifiers and are part of the same class hierarchy.
/// \Note This is implemented by checking if the ID types are the same
template <typename T, typename U>
concept SharesTypeHierarchyWith =
    SharesTypeHierarchyWithImpl<remove_ref_ptr_cv_t<T>, remove_ref_ptr_cv_t<U>>;

template <typename From, typename To>
concept CastableImpl = requires(From* from) { static_cast<To*>(from); };

/// Checks if it is possible to `static_cast` pointer to \p From to pointer to
/// \p To
template <typename From, typename To>
concept Castable =
    CastableImpl<remove_ref_ptr_cv_t<From>, remove_ref_ptr_cv_t<To>>;

/// MARK: - isa

/// \Returns `true` if \p TestID is a super class of \p ActualID
/// This function should ideally be `consteval` if we were writing C++23,
/// therefore the `ct` prefix
template <typename IDType>
static constexpr bool ctIsaImpl(IDType TestID, IDType ActualID) {
    /// Poor mans `consteval`
    assert(std::is_constant_evaluated());
    if constexpr (std::is_same_v<IDType, InvalidTypeID>) {
        UTL_DC_CTPrintVal(TestID);
        UTL_DC_CTPrintVal(ActualID);
    }
    if (ActualID == IDTraits<IDType>::last) {
        return false;
    }
    if (ActualID == TestID) {
        return true;
    }
    return ctIsaImpl(TestID, IDToParent(ActualID));
}

template <typename TestType>
static constexpr auto makeIsaDispatchArray() {
    using IDType = decltype(TypeToID<TestType>);
    return []<size_t... Actual>(std::index_sequence<Actual...>) {
        return Array{ ctIsaImpl(TypeToID<TestType>, IDType{ Actual })... };
    }(std::make_index_sequence<IDTraits<IDType>::count>{});
}

template <typename TestType>
static constexpr Array IsaDispatchArray = makeIsaDispatchArray<TestType>();

template <typename Test, typename Known>
constexpr bool isaImpl(Known* obj) {
    if (!obj) {
        return false;
    }
    return dc::IsaDispatchArray<Test>[(size_t)dyncast_get_type(*obj)];
}

template <typename Test, typename Known>
constexpr bool isaImpl(Known& obj) {
    return isaImpl<Test>(&obj);
}

template <typename Test>
requires dc::Dynamic<Test>
struct IsaFn {
    template <typename Known>
    requires std::is_class_v<Test> && SharesTypeHierarchyWith<Known, Test>
    UTL_DC_NODEBUG constexpr bool operator()(Known* obj) const {
        return isaImpl<Test>(obj);
    }

    template <typename Known>
    requires std::is_class_v<Test> && SharesTypeHierarchyWith<Known, Test>
    UTL_DC_NODEBUG constexpr bool operator()(Known& obj) const {
        return isaImpl<Test>(obj);
    }
};

/// MARK: - dyncast and cast

template <typename To, typename From>
constexpr To dyncastImpl(From* from) {
    if (isaImpl<std::remove_const_t<std::remove_pointer_t<To>>>(from)) {
        return static_cast<To>(from);
    }
    return nullptr;
}

template <typename To, typename From>
constexpr To dyncastImpl(From& from) {
    using ToNoRef = std::remove_reference_t<To>;
    if (auto* result = dyncastImpl<ToNoRef*>(&from)) {
        return *result;
    }
    throw std::bad_cast();
}

template <typename To>
requires dc::Dynamic<To>
struct DyncastFn {
    template <typename From>
    requires std::is_pointer_v<To> && SharesTypeHierarchyWith<From, To> &&
             Castable<From, To>
    UTL_DC_NODEBUG constexpr To operator()(From* from) const {
        return dyncastImpl<To>(from);
    }

    template <typename From>
    requires std::is_reference_v<To> && SharesTypeHierarchyWith<From, To> &&
             Castable<From, To>
    UTL_DC_NODEBUG constexpr To operator()(From& from) const {
        return dyncastImpl<To>(from);
    }
};

template <typename To, typename From>
constexpr To castImpl(From* from) {
    assert(!from || dyncastImpl<To>(from) && "cast failed.");
    return static_cast<To>(from);
}

template <typename To, typename From>
constexpr To castImpl(From& from) {
    using ToNoRef = std::remove_reference_t<To>;
    return *castImpl<ToNoRef*>(&from);
}

template <typename To>
requires dc::Dynamic<To>
struct UnsafeCastFn {
    template <typename From>
    requires std::is_pointer_v<To> && SharesTypeHierarchyWith<From, To> &&
             Castable<From, To>
    UTL_DC_NODEBUG constexpr To operator()(From* from) const {
        return castImpl<To>(from);
    }

    template <typename From>
    requires std::is_reference_v<To> && SharesTypeHierarchyWith<From, To> &&
             Castable<From, To>
    UTL_DC_NODEBUG constexpr To operator()(From& from) const {
        return castImpl<To>(from);
    }
};

} // namespace dc

template <typename Test>
inline constexpr dc::IsaFn<Test> isa{};

template <typename To>
inline constexpr dc::DyncastFn<To> dyncast{};

template <typename To>
inline constexpr dc::UnsafeCastFn<To> cast{};

template <typename To>
inline constexpr dc::UnsafeCastFn<To> unsafe_cast{};

/// MARK: - visit

namespace dc {

/// Tag type used by the overloads of `visit()` that don't take an explicit
/// return type parameter to instruct `visitImpl()` to deduce the return type
enum class DeduceReturnTypeTag {};

/// Converts the N-dimensional multi-index \p index to a single dimensional flat
/// index according to \p bounds
template <size_t N>
UTL_DC_ALWAYS_INLINE constexpr size_t flattenIndex(Array<size_t, N> index,
                                                   Array<size_t, N> bounds) {
    static_assert(N > 0);
    assert(index[0] < bounds[0]);
    size_t acc = index[0];
    for (size_t i = 1; i < N; ++i) {
        assert(index[i] < bounds[i]);
        acc *= bounds[i];
        acc += index[i];
    }
    return acc;
}

/// Converts the a single dimensional flat index \p flatIdex to an N-dimensional
/// multi-index according to \p bounds
template <size_t N>
constexpr Array<size_t, N> expandIndex(size_t flatIndex,
                                       Array<size_t, N> bounds) {
    assert(std::is_constant_evaluated());
    Array<size_t, N> index;
    for (size_t i = 0, j = N - 1; i < N; ++i, --j) {
        size_t m = 1;
        for (size_t k = N - 1; k > i; --k) {
            m *= bounds[k];
        }
        index[i] = flatIndex / m;
        flatIndex -= index[i] * m;
    }
    return index;
}

/// Implementation of `ComputeInvocableIndices`
template <auto ID, typename IDType, size_t Current, size_t Last,
          size_t... InvocableIndices>
struct InvocableIndicesImpl:
    std::conditional_t<
        /// `IsInvocable` =
        IDIsConcrete<(IDType)Current> /// `Current` must be concrete to even be
                                      /// considered invocable
            && ctIsaImpl(ID, (IDType)Current), /// and `Current` must be derived
                                               /// from `ID`
        InvocableIndicesImpl<ID, IDType, Current + 1, Last, InvocableIndices...,
                             Current>,
        InvocableIndicesImpl<ID, IDType, Current + 1, Last,
                             InvocableIndices...>> {};

/// Base case where `Current == Last`
template <auto ID, typename IDType, size_t Last, size_t... InvocableIndices>
struct InvocableIndicesImpl<ID, IDType, Last, Last, InvocableIndices...> {
    using Indices = std::index_sequence<InvocableIndices...>;
};

/// Computes which dispatch cases have to be generated for a given type `T`,
/// i.e. the list of all type IDs (represented as integers) that could be the
/// runtime type of `T`. This using declaration evaluates to a
/// `std::index_sequence` of the invocable indices
template <typename T>
using ComputeInvocableIndices = typename InvocableIndicesImpl<
    TypeToID<std::decay_t<T>>, TypeToIDType<T>,
    (size_t)IDTraits<TypeToIDType<T>>::first,
    (size_t)IDTraits<TypeToIDType<T>>::last>::Indices;

/// Implementation of `MakeStructuredIndex`
template <size_t FlatInvokeIndex, typename... InvocableIndices>
struct MakeStructuredIndexImpl {
    static constexpr Array ExIndex = expandIndex<sizeof...(
        InvocableIndices)>(FlatInvokeIndex, { InvocableIndices::size()... });

    template <size_t... I>
    static auto makeStructured(std::index_sequence<I...>) {
        return std::index_sequence<
            IndexSequenceToArray<InvocableIndices>[ExIndex[I]]...>{};
    }

    using type = decltype(makeStructured(
        std::make_index_sequence<sizeof...(InvocableIndices)>{}));
};

/// Converts the flat index `FlatInvokeIndex` in the space of _invocable_ types
/// to a structured multi-index in the space of all types. Here "space of
/// invocable types" means
/// `[0,...,NumInvocableTypes<T0>) x ... x  [0,...,NumInvocableTypes<TN>)`
/// where `NumInvocableTypes<T> = ComputeInvocableIndices<T>::size()`
/// This template evaluates to a `std::index_sequence` of the structured indices
template <size_t FlatInvokeIndex, typename... InvocableIndices>
using MakeStructuredIndex =
    typename MakeStructuredIndexImpl<FlatInvokeIndex,
                                     InvocableIndices...>::type;

template <typename R, typename F, typename T, typename StructuredIndex>
struct VisitorCase;

/// Evaluates to the type at index \p I in the class hierarchy of \p U with
/// the same cv-qualifications as \p U
template <typename U, size_t I>
using DerivedAt = copy_cv_reference_t<U&&, IDToType<(TypeToIDType<U>)I>>;

/// We use a macro here to not repeat ourselves and we don't wrap the
/// expression in a lambda to avoid one unnecessary runtime indirection
/// in debug builds
#define UTL_DC_INVOKE_EXPR() f(static_cast<DerivedAt<T, StructuredIndex>>(t)...)

/// Defines the invocation for one combination of runtime argument types. Users
/// of this class are only interested in the member typedef `type
template <typename R, typename F, typename... T, size_t... StructuredIndex>
struct VisitorCase<R, F, TypeList<T...>,
                   std::index_sequence<StructuredIndex...>> {
    UTL_DC_NODEBUG static constexpr R impl(F&& f, T&&... t) {
        using ExprType = decltype(UTL_DC_INVOKE_EXPR());
        if constexpr (std::is_same_v<R, void>) {
            UTL_DC_INVOKE_EXPR();
        }
        if constexpr (std::is_same_v<ExprType, void>) {
            UTL_DC_INVOKE_EXPR();
            /// Unreachable because we invoke UB by leaving a non-void
            /// function without a value.
            unreachable();
        }
        else {
            return UTL_DC_INVOKE_EXPR();
        }
    }
};

template <typename F, typename... T, size_t... StructuredIndex>
struct VisitorCase<DeduceReturnTypeTag, F, TypeList<T...>,
                   std::index_sequence<StructuredIndex...>> {
    UTL_DC_NODEBUG static constexpr decltype(auto) impl(F&& f, T&&... t) {
        return UTL_DC_INVOKE_EXPR();
    }
};

#undef UTL_DC_INVOKE_EXPR

template <typename R, typename F, typename T, typename InvocableIndices>
struct MakeVisitorCasesImpl;

template <typename R, typename F, typename... T,
          typename... InvocableIndices // <- Pack of index_sequences with the
                                       // same size as T that hold the invocable
                                       // indices for each T
          >
struct MakeVisitorCasesImpl<R, F, TypeList<T...>,
                            TypeList<InvocableIndices...>> {
    /// The total number of invocable cases. This is used to make an index
    /// sequence of this size, create structured indices for every flat index
    /// and create dispatch cases from that
    static constexpr size_t TotalInvocableCases =
        (InvocableIndices::size() * ...);

    template <size_t... FlatInvokeIndex>
    static auto makeCaseTypeList(std::index_sequence<FlatInvokeIndex...>) {
        return TypeList<VisitorCase<
            R, F, TypeList<T...>,
            MakeStructuredIndex<FlatInvokeIndex, InvocableIndices...>>...>{};
    }

    template <size_t... FlatInvokeIndex>
    static auto makeFlatCaseIndexList(std::index_sequence<FlatInvokeIndex...>) {
#if 0
        /// Debug code to print the computed values
        constexpr size_t TestInvokeIndex = 3;
        using StructuredIndex =
            MakeStructuredIndex<TestInvokeIndex, InvocableIndices...>;
        UTL_DC_CTPrintType(StructuredIndex);
        constexpr size_t FlatIndex =
            flattenIndex(IndexSequenceToArray<StructuredIndex>,
                         TypesToBounds<T...>);
        UTL_DC_CTPrintVal(FlatIndex);
        constexpr Array RestructuredIndex =
            expandIndex<sizeof...(T)>(FlatIndex, { TypeToBound<T>... });
        UTL_DC_CTPrintVal(RestructuredIndex);
#endif
        return std::index_sequence<
            flattenIndex(IndexSequenceToArray<MakeStructuredIndex<
                             FlatInvokeIndex, InvocableIndices...>>,
                         TypesToBounds<T...>)...>{};
    }

    using CaseTypeList = decltype(makeCaseTypeList(
        std::make_index_sequence<TotalInvocableCases>{}));

    using FlatCaseIndexList = decltype(makeFlatCaseIndexList(
        std::make_index_sequence<TotalInvocableCases>{}));
};

/// Provides two member typedefs
/// - `CaseTypeList` is a `TypeList` of lambda types for all possible invoke
///   cases that downcast to the runtime argument types. Instances of all types
///   can be converted to function pointers.
/// - `FlatCaseIndexList` is an `std::index_sequence` with the same size as
///   `CaseTypeList` that contains the corresponding flat indices in the space
///   of all possible type combinations.
template <typename R, typename F, typename... T>
struct MakeVisitorCases:
    MakeVisitorCasesImpl<R, F, TypeList<T...>,
                         TypeList<ComputeInvocableIndices<T>...>> {};

template <typename R, typename F, typename T, typename Cases>
struct DeduceReturnTypeImpl {
    using type = R;
};

template <typename F, typename... T, typename... Cases>
struct DeduceReturnTypeImpl<DeduceReturnTypeTag, F, TypeList<T...>,
                            TypeList<Cases...>>:
    std::common_reference<decltype(Cases::impl(std::declval<F&&>(),
                                               std::declval<T&&>()...))...> {};

/// Deduces the common return type of the `visit` expression by applying
/// `std::common_reference` over all possible return types.
template <typename R, typename F, typename T_TypeList, typename Cases_TypeList>
using DeduceReturnType =
    typename DeduceReturnTypeImpl<R, F, T_TypeList, Cases_TypeList>::type;

template <size_t... Indices>
requires(sizeof...(Indices) > 0)
inline constexpr size_t IndexRangeSize = Max<Indices...> - Min<Indices...> + 1;

template <typename ReturnType, typename CaseTypeList,
          typename FlatCaseIndexList>
struct InvokeVisitorCases;

/// This class instantiates an array of function pointers to all invocable
/// visitor cases and provides the `impl()` function to invoke a specific case.
///
/// We only generate function pointers in the smallest possible range of
/// invocable indices to avoid generating large chunks of unused zero bytes in
/// the executable. Therefore we have to subtract an offset (the smallest of the
/// `FlatCaseIndices`) from the runtime computed flat index before dispatching.
template <typename ReturnType, typename... Cases, size_t... FlatCaseIndices>
struct InvokeVisitorCases<ReturnType, TypeList<Cases...>,
                          std::index_sequence<FlatCaseIndices...>> {
    static constexpr size_t FirstFlatInvokeIndex = Min<FlatCaseIndices...>;

    static constexpr size_t NumFlatCaseIndices = sizeof...(FlatCaseIndices);

    /// The size of the function pointer array that is generated
    static constexpr size_t FlatInvokeIndexRangeSize =
        IndexRangeSize<FlatCaseIndices...>;

    /// Function pointer for one invoke case
    template <typename Case, typename F, typename... T>
    UTL_DC_NODEBUG static constexpr ReturnType casePtr(F&& f, T&&... t) {
        return Case::impl(static_cast<F&&>(f), static_cast<T&&>(t)...);
    }

    /// Runs a for loop to assign the case index function pointers to avoid a
    /// fold expression. Unlike a for loop fold expressions can run into issues
    /// with the expression nesting depth of the compiler.
    template <typename FuncPtrType>
    static constexpr void assignDispatchArray(
        Array<FuncPtrType, FlatInvokeIndexRangeSize>& DispatchArray,
        Array<size_t, NumFlatCaseIndices> const& indices,
        Array<FuncPtrType, NumFlatCaseIndices> const& casePtrs) {
        for (size_t i = 0; i < NumFlatCaseIndices; ++i) {
            DispatchArray[indices[i] - FirstFlatInvokeIndex] = casePtrs[i];
        }
    }

    /// Computes the array of function pointers
    template <typename FuncPtrType, typename F, typename... T>
    static constexpr auto makeDispatchArray() {
        Array<FuncPtrType, FlatInvokeIndexRangeSize> DispatchArray{};
        assignDispatchArray<FuncPtrType>(DispatchArray, { FlatCaseIndices... },
                                         { casePtr<Cases, F, T...>... });
        return DispatchArray;
    }

    /// The computed array of function pointers
    template <typename F, typename... T>
    static constexpr Array DispatchArray =
        makeDispatchArray<ReturnType (*)(F&&, T&&...), F, T...>();

    /// Subtracts the index offset from \p flatIndex and invokes the function
    /// pointer at that index
    template <typename F, typename... T>
    UTL_DC_NODEBUG static constexpr ReturnType impl(size_t flatIndex, F&& f,
                                                    T&&... t) {
        /// We use `.elems` directly here to avoid one function call in debug
        /// builds
        auto* dispatcher =
            DispatchArray<F, T...>.elems[flatIndex - FirstFlatInvokeIndex];
        /// ** Is the type hierarchy defined correctly? **
        /// If not `dispatcher` can be null
        assert(dispatcher);
        return dispatcher(static_cast<F&&>(f), static_cast<T&&>(t)...);
    }
};

template <typename R, typename F, typename... T>
UTL_DC_NODEBUG constexpr decltype(auto) visitImpl(F&& f, T&&... t) {
    using CaseTypeList = typename MakeVisitorCases<R, F, T...>::CaseTypeList;
    using FlatCaseIndexList =
        typename MakeVisitorCases<R, F, T...>::FlatCaseIndexList;
    using ReturnType = DeduceReturnType<R, F, TypeList<T...>, CaseTypeList>;

    Array index = { (size_t)dyncast_get_type(t)... };
    size_t flatIndex = flattenIndex(index, TypesToBounds<T...>);
    return InvokeVisitorCases<ReturnType, CaseTypeList,
                              FlatCaseIndexList>::impl(flatIndex,
                                                       static_cast<F&&>(f),
                                                       static_cast<T&&>(t)...);
}

} // namespace dc

template <typename R = dc::DeduceReturnTypeTag, typename F, dc::Dynamic T>
UTL_DC_NODEBUG constexpr decltype(auto) visit(T&& t, F&& fn) {
    return dc::visitImpl<R>((F&&)fn, (T&&)t);
}

template <typename R = dc::DeduceReturnTypeTag, typename F, dc::Dynamic T0,
          dc::Dynamic T1>
UTL_DC_NODEBUG constexpr decltype(auto) visit(T0&& t0, T1&& t1, F&& fn) {
    return dc::visitImpl<R>((F&&)fn, (T0&&)t0, (T1&&)t1);
}

template <typename R = dc::DeduceReturnTypeTag, typename F, dc::Dynamic T0,
          dc::Dynamic T1, dc::Dynamic T2>
UTL_DC_NODEBUG constexpr decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2,
                                              F&& fn) {
    return dc::visitImpl<R>((F&&)fn, (T0&&)t0, (T1&&)t1, (T2&&)t2);
}

template <typename R = dc::DeduceReturnTypeTag, typename F, dc::Dynamic T0,
          dc::Dynamic T1, dc::Dynamic T2, dc::Dynamic T3>
UTL_DC_NODEBUG constexpr decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2,
                                              T3&& t3, F&& fn) {
    return dc::visitImpl<R>((F&&)fn, (T0&&)t0, (T1&&)t1, (T2&&)t2, (T3&&)t3);
}

template <typename R = dc::DeduceReturnTypeTag, typename F, dc::Dynamic T0,
          dc::Dynamic T1, dc::Dynamic T2, dc::Dynamic T3, dc::Dynamic T4>
UTL_DC_NODEBUG constexpr decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2,
                                              T3&& t3, T4&& t4, F&& fn) {
    return dc::visitImpl<R>((F&&)fn, (T0&&)t0, (T1&&)t1, (T2&&)t2, (T3&&)t3,
                            (T4&&)t4);
}

template <typename R = dc::DeduceReturnTypeTag, typename F, dc::Dynamic T0,
          dc::Dynamic T1, dc::Dynamic T2, dc::Dynamic T3, dc::Dynamic T4,
          dc::Dynamic T5>
UTL_DC_NODEBUG constexpr decltype(auto)
visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5, F&& fn) {
    return dc::visitImpl<R>((F&&)fn, (T0&&)t0, (T1&&)t1, (T2&&)t2, (T3&&)t3,
                            (T4&&)t4, (T5&&)t5);
}

} // namespace utl

#if !defined(UTL_DC_ENABLE_DEBUGGING)

#undef UTL_DC_CONCAT
#undef UTL_DC_CONCAT_IMPL
#undef UTL_DC_CTPrintType
#undef UTL_DC_CTPrintVal

#endif // UTL_DC_ENABLE_DEBUGGING

#undef UTL_DC_ALWAYS_INLINE
#undef UTL_DC_NODEBUG
#undef UTL_DC_NODEBUG_IMPL

#endif // UTL_DYNCAST_HPP_
