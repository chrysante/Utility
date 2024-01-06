#ifndef UTL_DYNCAST_HPP_
#define UTL_DYNCAST_HPP_

#include <array>
#include <cassert>
#include <tuple>
#include <type_traits>
#include <typeinfo>

#include "__debug.hpp"

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

/// MARK: - TMP debug utilities

#define UTL_DC_CONCAT(a, b)      UTL_DC_CONCAT_IMPL(a, b)
#define UTL_DC_CONCAT_IMPL(a, b) a##b

#define CTPrintType(...) CTTP<__VA_ARGS__> UTL_DC_CONCAT(ctPrintVar, __LINE__);

#define CTPrintVal(...) CTVP<__VA_ARGS__> UTL_DC_CONCAT(ctPrintVar, __LINE__);

template <typename...>
struct CTTP;

template <auto...>
struct CTVP;

/// MARK: - General utilities

[[noreturn]] inline void unreachable() {
    assert(false);
}

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

/// Enum class to denote invalid type IDs
enum class Invalid {};

/// Used to identify the base case in `isaImpl()`
template <auto Fallback>
constexpr decltype(Fallback) ValueOr(auto value) {
    return value;
}

/// Base case
template <auto Fallback>
constexpr decltype(Fallback) ValueOr(Invalid) {
    return Fallback;
}

/// Variadic type list useful for template meta programming
template <typename... T>
struct TypeList {
    TypeList() = default;
    constexpr TypeList(T...) {}
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
    static constexpr std::array<size_t, sizeof...(I)> value = { I... };
};

/// Converts the `std::index_sequence` \p IdxSeq to an `std::array<size_t,
/// IdxSeq::size()>`
template <typename IdxSeq>
constexpr std::array IndexSequenceToArray =
    IndexSequenceToArrayImpl<IdxSeq>::value;

/// MARK: - General RTTI implementation

/// Different kinds of _corporeality_. Corporeality is meant to denote the
/// 'class' of abstractness and concreteness.
enum class Corporeality { Abstract, Concrete };

/// Common traits of an ID type
template <typename IDType>
struct IDTraits {
    static constexpr size_t count = (size_t)IDType::LAST + 1;
    static constexpr IDType first = IDType{ 0 };
    static constexpr IDType last = IDType(count);
};

/// MARK: - Maps

/// Maps \p T from the type domain to the identifier domain
template <typename T>
constexpr Invalid TypeToID{};

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
    constexpr std::array ParentArray =
        []<size_t... I>(std::index_sequence<I...>) {
        return std::array{ ValueOr<IDTraits<IDType>::last>(
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

/// MARK: - isa

/// \Returns `true` if \p TestID is a super class of \p ActualID
/// This function should ideally be `consteval` if we were writing C++23,
/// therefore the `ct` prefix
template <typename IDType>
static constexpr bool ctIsaImpl(IDType TestID, IDType ActualID) {
    if constexpr (std::is_same_v<IDType, Invalid>) {
        CTPrintVal(TestID);
        CTPrintVal(ActualID);
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
        return std::array{ ctIsaImpl(TypeToID<TestType>, IDType{ Actual })... };
    }(std::make_index_sequence<IDTraits<IDType>::count>{});
}

template <typename TestType>
static constexpr std::array IsaDispatchArray = makeIsaDispatchArray<TestType>();

template <typename Test, typename Known>
bool isaImpl(Known* obj) {
    if (!obj) {
        return false;
    }
    return dc::IsaDispatchArray<Test>[(size_t)dyncast_get_type(*obj)];
}

template <typename Test, typename Known>
bool isaImpl(Known& obj) {
    return isaImpl<Test>(&obj);
}

template <typename Test>
struct IsaFn {
    template <typename Known>
    requires std::is_class_v<Test>
    constexpr bool operator()(Known* obj) const {
        return isaImpl<Test>(obj);
    }

    template <typename Known>
    requires std::is_class_v<Test>
    constexpr bool operator()(Known& obj) const {
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
struct DyncastFn {
    template <typename From>
    requires std::is_pointer_v<To>
    constexpr To operator()(From* from) const {
        return dyncastImpl<To>(from);
    }

    template <typename From>
    requires std::is_reference_v<To>
    constexpr To operator()(From& from) const {
        return dyncastImpl<To>(from);
    }
};

template <typename To, typename From>
constexpr To castImpl(From* from) {
    __utl_assert(!from || dyncastImpl<To>(from) && "cast failed.");
    return static_cast<To>(from);
}

template <typename To, typename From>
constexpr To castImpl(From& from) {
    using ToNoRef = std::remove_reference_t<To>;
    return *castImpl<ToNoRef*>(&from);
}

template <typename To>
struct CastFn {
    template <typename From>
    requires std::is_pointer_v<To>
    constexpr To operator()(From* from) const {
        return castImpl<To>(from);
    }

    template <typename From>
    requires std::is_reference_v<To>
    constexpr To operator()(From& from) const {
        return castImpl<To>(from);
    }
};

} // namespace dc

template <typename Test>
inline constexpr dc::IsaFn<Test> isa{};

template <typename To>
inline constexpr dc::DyncastFn<To> dyncast{};

template <typename To>
inline constexpr dc::CastFn<To> cast{};

/// MARK: - visit

namespace dc {

/// Tag type used by the overloads of `visit()` that don't take an explicit
/// return type parameter to instruct `visitImpl()` to deduce the return type
enum class DeduceReturnType {};

/// Converts the N-dimensional multi-index \p index to a single dimensional flat
/// index according to \p bounds
template <size_t N>
constexpr size_t flattenIndex(std::array<size_t, N> index,
                              std::array<size_t, N> bounds) {
    static_assert(N > 0);
    __utl_assert(index[0] < bounds[0]);
    size_t acc = index[0];
    for (size_t i = 1; i < N; ++i) {
        __utl_assert(index[i] < bounds[i]);
        acc *= bounds[i];
        acc += index[i];
    }
    return acc;
}

/// Converts the a single dimensional flat index \p flatIdex to an N-dimensional
/// multi-index according to \p bounds
template <size_t N>
constexpr std::array<std::size_t, N> expandIndex(std::size_t flatIndex,
                                                 std::array<size_t, N> bounds) {
    std::array<std::size_t, N> index;
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

template <size_t FlatInvokeIndex, typename... InvocableIndices>
struct MakeStructuredIndexImpl {
    static constexpr std::array ExIndex = expandIndex<sizeof...(
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

/// Defines the invocation for one combination of runtime argument types. Users
/// of this class are only interested in the static member variable `impl`.
template <typename R, typename F, typename... T, size_t... StructuredIndex>
struct VisitorCase<R, F, TypeList<T...>,
                   std::index_sequence<StructuredIndex...>> {
private:
    ///
    template <typename U, size_t I>
    using DerivedAt = copy_cv_reference_t<U&&, IDToType<(TypeToIDType<U>)I>>;

public:
    static constexpr auto impl = [](F&& f, T&&... t) -> decltype(auto) {
        auto invoke = [&]() -> decltype(auto) {
            return f(static_cast<DerivedAt<T, StructuredIndex>>(t)...);
        };
        if constexpr (std::is_same_v<R, DeduceReturnType>) {
            return invoke();
        }
        else if constexpr (std::is_same_v<R, void>) {
            invoke();
        }
        else if constexpr (std::is_same_v<decltype(invoke()), void>) {
            return [&]() -> R {
                invoke();
                /// Unreachable because we invoke UB by returning from a
                /// non-void function without a value. This must be fixed in
                /// user code
                __utl_unreachable();
            }();
        }
        else {
            return [&]() -> R { return invoke(); }();
        }
    };
};

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
    /// and create dispatch cases from the that
    static constexpr size_t TotalInvocableCases =
        (InvocableIndices::size() * ...);

    template <size_t... FlatInvokeIndex>
    static auto makeCaseTypeList(std::index_sequence<FlatInvokeIndex...>) {
        return TypeList<
            decltype(VisitorCase<
                     R, F, TypeList<T...>,
                     MakeStructuredIndex<FlatInvokeIndex,
                                         InvocableIndices...>>::impl)...>{};
    }

    template <size_t... FlatInvokeIndex>
    static auto makeFlatCaseIndexList(std::index_sequence<FlatInvokeIndex...>) {
        /// Debug code to print the computed values
        if constexpr (false) {
            constexpr size_t TestInvokeIndex = 3;
            using StructuredIndex =
                MakeStructuredIndex<TestInvokeIndex, InvocableIndices...>;
            CTPrintType(StructuredIndex);
            constexpr size_t FlatIndex =
                flattenIndex(IndexSequenceToArray<StructuredIndex>,
                             { TypeToBound<T>... });
            CTPrintVal(FlatIndex);
            constexpr std::array RestructuredIndex =
                expandIndex<sizeof...(T)>(FlatIndex, { TypeToBound<T>... });
            CTPrintVal(RestructuredIndex);
        }
        return std::index_sequence<
            flattenIndex(IndexSequenceToArray<MakeStructuredIndex<
                             FlatInvokeIndex, InvocableIndices...>>,
                         { TypeToBound<T>... })...>{};
    }

    using CaseTypeList = decltype(makeCaseTypeList(
        std::make_index_sequence<TotalInvocableCases>{}));

    using FlatCaseIndexList = decltype(makeFlatCaseIndexList(
        std::make_index_sequence<TotalInvocableCases>{}));
};

template <typename R, typename F, typename... T>
struct MakeVisitorCases:
    MakeVisitorCasesImpl<R, F, TypeList<T...>,
                         TypeList<ComputeInvocableIndices<T>...>> {};

template <typename R, typename F, typename T, typename Cases>
struct DoDeduceReturnTypeImpl {
    using type = R;
};

template <typename F, typename... T, typename... Cases>
struct DoDeduceReturnTypeImpl<DeduceReturnType, F, TypeList<T...>,
                              TypeList<Cases...>> {
    template <typename Case>
    using ReturnType =
        decltype(Case{}(std::declval<F&&>(), std::declval<T&&>()...));
    using type = typename std::conditional_t<
        std::is_reference_v<First<ReturnType<Cases>...>>,
        std::common_reference<ReturnType<Cases>...>,
        std::common_type<ReturnType<Cases>...>>::type;
};

template <typename R, typename F, typename T_TypeList, typename Cases_TypeList>
using DoDeduceReturnType =
    typename DoDeduceReturnTypeImpl<R, F, T_TypeList, Cases_TypeList>::type;

template <typename ReturnType, typename CaseTypeList,
          typename FlatCaseIndexList>
struct InvokeVisitorCases;

template <typename ReturnType, typename... Cases, size_t... FlatCaseIndices>
struct InvokeVisitorCases<ReturnType, TypeList<Cases...>,
                          std::index_sequence<FlatCaseIndices...>> {
    template <typename FuncPtrType, size_t NumTotalCombinations, typename F,
              typename... T>
    static constexpr auto makeDispatchArray() {
        std::array<FuncPtrType, NumTotalCombinations> DispatchArray{};
        ((DispatchArray[FlatCaseIndices] = [](F&& f, T&&... t) -> ReturnType {
             return Cases{}(static_cast<F&&>(f), static_cast<T&&>(t)...);
         }),
         ...);
        return DispatchArray;
    }

    template <typename F, typename... T>
    static ReturnType impl(size_t flatIndex, F&& f, T&&... t) {
        using FuncPtrType = ReturnType (*)(F&&, T&&...);
        static constexpr size_t NumTotalCombinations = (TypeToBound<T> * ...);
        static constexpr auto DispatchArray =
            makeDispatchArray<FuncPtrType, NumTotalCombinations, F, T...>();
        FuncPtrType dispatcher = DispatchArray[flatIndex];
        /// ** Is the type hierarchy correctly defined? **
        /// If not `dispatcher` can be null
        return dispatcher(static_cast<F&&>(f), static_cast<T&&>(t)...);
    }
};

template <typename R, typename F, typename... T>
decltype(auto) visitImpl(F&& f, T&&... t) {
    using CaseTypeList = typename MakeVisitorCases<R, F, T...>::CaseTypeList;
    using FlatCaseIndexList =
        typename MakeVisitorCases<R, F, T...>::FlatCaseIndexList;
    using ReturnType = DoDeduceReturnType<R, F, TypeList<T...>, CaseTypeList>;
    static constexpr std::array Bounds = { TypeToBound<T>... };

    std::array index = { (size_t)dyncast_get_type(t)... };
    size_t flatIndex = flattenIndex(index, Bounds);
    return InvokeVisitorCases<ReturnType, CaseTypeList,
                              FlatCaseIndexList>::impl(flatIndex,
                                                       static_cast<F&&>(f),
                                                       static_cast<T&&>(t)...);
}

} // namespace dc

template <typename T, typename F>
decltype(auto) visit(T&& t, F&& fn) {
    return dc::visitImpl<dc::DeduceReturnType>(static_cast<F&&>(fn),
                                               static_cast<T&&>(t));
}

template <typename T0, typename T1, typename F>
decltype(auto) visit(T0&& t0, T1&& t1, F&& fn) {
    return dc::visitImpl<dc::DeduceReturnType>(static_cast<F&&>(fn),
                                               static_cast<T0&&>(t0),
                                               static_cast<T1&&>(t1));
}

template <typename T0, typename T1, typename T2, typename F>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, F&& fn) {
    return dc::visitImpl<dc::DeduceReturnType>(static_cast<F&&>(fn),
                                               static_cast<T0&&>(t0),
                                               static_cast<T1&&>(t1),
                                               static_cast<T2&&>(t2));
}

template <typename T0, typename T1, typename T2, typename T3, typename F>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, F&& fn) {
    return dc::visitImpl<dc::DeduceReturnType>(static_cast<F&&>(fn),
                                               static_cast<T0&&>(t0),
                                               static_cast<T1&&>(t1),
                                               static_cast<T2&&>(t2),
                                               static_cast<T3&&>(t3));
}

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename F>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, F&& fn) {
    return dc::visitImpl<dc::DeduceReturnType>(static_cast<F&&>(fn),
                                               static_cast<T0&&>(t0),
                                               static_cast<T1&&>(t1),
                                               static_cast<T2&&>(t2),
                                               static_cast<T3&&>(t3),
                                               static_cast<T4&&>(t4));
}

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename F>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5,
                     F&& fn) {
    return dc::visitImpl<dc::DeduceReturnType>(static_cast<F&&>(fn),
                                               static_cast<T0&&>(t0),
                                               static_cast<T1&&>(t1),
                                               static_cast<T2&&>(t2),
                                               static_cast<T3&&>(t3),
                                               static_cast<T4&&>(t4),
                                               static_cast<T5&&>(t5));
}

template <typename R, typename T, typename F>
decltype(auto) visit(T&& t, F&& fn) {
    return dc::visitImpl<R>(static_cast<F&&>(fn), static_cast<T&&>(t));
}

template <typename R, typename T0, typename T1, typename F>
decltype(auto) visit(T0&& t0, T1&& t1, F&& fn) {
    return dc::visitImpl<R>(static_cast<F&&>(fn), static_cast<T0&&>(t0),
                            static_cast<T1&&>(t1));
}

template <typename R, typename T0, typename T1, typename T2, typename F>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, F&& fn) {
    return dc::visitImpl<R>(static_cast<F&&>(fn), static_cast<T0&&>(t0),
                            static_cast<T1&&>(t1), static_cast<T2&&>(t2));
}

template <typename R, typename T0, typename T1, typename T2, typename T3,
          typename F>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, F&& fn) {
    return dc::visitImpl<R>(static_cast<F&&>(fn), static_cast<T0&&>(t0),
                            static_cast<T1&&>(t1), static_cast<T2&&>(t2),
                            static_cast<T3&&>(t3));
}

template <typename R, typename T0, typename T1, typename T2, typename T3,
          typename T4, typename F>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, F&& fn) {
    return dc::visitImpl<R>(static_cast<F&&>(fn), static_cast<T0&&>(t0),
                            static_cast<T1&&>(t1), static_cast<T2&&>(t2),
                            static_cast<T3&&>(t3), static_cast<T4&&>(t4));
}

template <typename R, typename T0, typename T1, typename T2, typename T3,
          typename T4, typename T5, typename F>
decltype(auto) visit(T0&& t0, T1&& t1, T2&& t2, T3&& t3, T4&& t4, T5&& t5,
                     F&& fn) {
    return dc::visitImpl<R>(static_cast<F&&>(fn), static_cast<T0&&>(t0),
                            static_cast<T1&&>(t1), static_cast<T2&&>(t2),
                            static_cast<T3&&>(t3), static_cast<T4&&>(t4),
                            static_cast<T5&&>(t5));
}

} // namespace utl

#endif // UTL_DYNCAST_HPP_
