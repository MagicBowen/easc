// #include <iostream>

// template <class T, T V>
// struct integral_constant {
//     static constexpr const T value = V;
//     typedef T value_type;
//     typedef integral_constant type;
//     inline constexpr operator value_type() const noexcept { return value; }
// };

// template <bool V>
// using BoolType = integral_constant<bool, V>;

// using FalseType = BoolType<false>;
// using TrueType  = BoolType<true>;

// template<typename T>
// struct IsBoolType : FalseType {
//     static constexpr bool value = false;
// };

// template<bool V>
// struct IsBoolType<BoolType<V>> : TrueType {
//     static constexpr bool value = true;
//     static constexpr bool boolValue = V;
// };

// // Conditional 元结构
// template <bool cond, typename Then, typename Else>
// struct Conditional;

// template <typename Then, typename Else>
// struct Conditional<true, Then, Else> {
//     using type = Then;
// };

// template <typename Then, typename Else>
// struct Conditional<false, Then, Else> {
//     using type = Else;
// };

// template<typename T>
// constexpr T&& forward(std::remove_reference_t<T>& param) noexcept {
//     return static_cast<T&&>(param);
// }

// template<typename T>
// constexpr T&& forward(std::remove_reference_t<T>&& param) noexcept {
//     static_assert(!std::is_lvalue_reference<T>::value, "Invalid forward of an rvalue as an lvalue");
//     return static_cast<T&&>(param);
// }

// /////////////////////////////////////////////////////////////////////////////////////
// // TypeList 定义
// template <typename... Ts>
// struct TypeList {};

// /////////////////////////////////////////////////////////////////////////////////////
// // IsEmpty 元结构
// template <typename List>
// struct TypeList_IsEmpty;

// template <>
// struct TypeList_IsEmpty<TypeList<>> {
//     static constexpr bool value = true;
// };

// template <typename... Ts>
// struct TypeList_IsEmpty<TypeList<Ts...>> {
//     static constexpr bool value = false;
// };

// /////////////////////////////////////////////////////////////////////////////////////
// // Size 元结构
// template <typename List>
// struct TypeList_Size;

// template <typename... Ts>
// struct TypeList_Size<TypeList<Ts...>> {
//     static constexpr size_t value = sizeof...(Ts);
// };

// /////////////////////////////////////////////////////////////////////////////////////
// // Get 元结构
// template <typename TypeList, std::size_t N>
// struct TypeList_Get;

// template <typename T, typename... Ts, std::size_t N>
// struct TypeList_Get<TypeList<T, Ts...>, N> {
//     using type = typename TypeList_Get<TypeList<Ts...>, N - 1>::type;
// };

// template <typename T, typename... Ts>
// struct TypeList_Get<TypeList<T, Ts...>, 0> {
//     using type = T;
// };

// template <std::size_t N>
// struct TypeList_Get<TypeList<>, N> {
//     static_assert(N < 0, "Index out of bounds in TypeList_Get");
// };

// /////////////////////////////////////////////////////////////////////////////////////
// // ByteOffset 元结构
// template <typename TypeList, std::size_t N>
// struct TypeList_ByteOffset;

// template <std::size_t N>
// struct TypeList_ByteOffset<TypeList<>, N> {
//     static_assert(N < 0, "Index out of range for empty TypeList.");
//     static constexpr std::size_t value = 0;
// };

// template <typename Head, typename... Tail>
// struct TypeList_ByteOffset<TypeList<Head, Tail...>, 0> {
//     static constexpr std::size_t value = 0;
// };

// template <typename Head, typename... Tail, std::size_t N>
// struct TypeList_ByteOffset<TypeList<Head, Tail...>, N> {
//     static_assert(N < sizeof...(Tail) + 1, "Index out of range for TypeList.");
//     static constexpr std::size_t value = sizeof(Head) + TypeList_ByteOffset<TypeList<Tail...>, N - 1>::value;
// };

// /////////////////////////////////////////////////////////////////////////////////////
// // Prepend 元结构
// template <typename T, typename List>
// struct TypeList_Prepend;

// template <typename T, typename... Ts>
// struct TypeList_Prepend<T, TypeList<Ts...>> {
//     using type = TypeList<T, Ts...>;
// };

// /////////////////////////////////////////////////////////////////////////////////////
// // Filter 元结构
// template <typename List, template <typename> class Pred>
// struct TypeList_Filter;

// template <template <typename> class Pred>
// struct TypeList_Filter<TypeList<>, Pred> {
//     using type = TypeList<>;
// };

// template <typename Head, typename... Tail, template <typename> class Pred>
// struct TypeList_Filter<TypeList<Head, Tail...>, Pred> {
// private:
//     using TailFiltered = typename TypeList_Filter<TypeList<Tail...>, Pred>::type;

// public:
//     using type = typename Conditional<
//         Pred<Head>::value,
//         typename TypeList_Prepend<Head, TailFiltered>::type,
//         TailFiltered
//     >::type;
// };

// /////////////////////////////////////////////////////////////////////////////////////
// // Map 元结构
// template <typename List, template <typename> class Mapper>
// struct TypeList_Map;

// template <template <typename> class Mapper>
// struct TypeList_Map<TypeList<>, Mapper> {
//     using type = TypeList<>;
// };

// template <typename Head, typename... Tail, template <typename> class Mapper>
// struct TypeList_Map<TypeList<Head, Tail...>, Mapper> {
// private:
//     using MappedHead = typename Mapper<Head>::type;
//     using MappedTail = typename TypeList_Map<TypeList<Tail...>, Mapper>::type;

// public:
//     using type = typename TypeList_Prepend<MappedHead, MappedTail>::type;
// };

// template <std::size_t... Is>
// struct IndexSequence {};

// template <std::size_t N, std::size_t... Is>
// struct MakeIndexSequenceImpl : MakeIndexSequenceImpl<N - 1, N - 1, Is...> {};

// template <std::size_t... Is>
// struct MakeIndexSequenceImpl<0, Is...> {
//     using type = IndexSequence<Is...>;
// };

// template <std::size_t N>
// using MakeIndexSequence = typename MakeIndexSequenceImpl<N>::type;

// /////////////////////////////////////////////////////////////////////////////////////
// template <typename... Ts>
// struct Tuple {};

// template <typename T, typename... Ts>
// struct Tuple<T, Ts...> {
//     T head;
//     Tuple<Ts...> tail;
    
//     Tuple() : head(), tail() {}
//     Tuple(T&& h, Ts&&... ts) : head(forward<T>(h)), tail(forward<Ts>(ts)...) {}
// };

// template <>
// struct Tuple<> {};

// /////////////////////////////////////////////////////////////////////////////////////
// template <typename... Ts>
// Tuple<Ts&&...> ForwardAsTuple(Ts&&... ts) {
//     return Tuple<Ts&&...>(std::forward<Ts>(ts)...);
// }

// /////////////////////////////////////////////////////////////////////////////////////
// template <typename List>
// struct TupleFromTypeList;

// template <typename... Ts>
// struct TupleFromTypeList<TypeList<Ts...>> {
//     using type = Tuple<Ts...>;
// };

// /////////////////////////////////////////////////////////////////////////////////////
// template <typename TupleType>
// struct TupleSize;

// template <typename... Ts>
// struct TupleSize<Tuple<Ts...>> {
//     static constexpr size_t value = sizeof...(Ts);
// };

// /////////////////////////////////////////////////////////////////////////////////////
// // 获取 Tuple 中第 N 个元素的类型
// template <std::size_t N, typename TupleType>
// struct TupleElemType;

// template <typename T, typename... Ts>
// struct TupleElemType<0, Tuple<T, Ts...>> {
//     using type = T;
// };

// template <std::size_t N, typename T, typename... Ts>
// struct TupleElemType<N, Tuple<T, Ts...>> {
//     static_assert(N -1 < sizeof...(Ts), "N overflow!");
//     using type = typename TupleElemType<N - 1, Tuple<Ts...>>::type;
// };

// /////////////////////////////////////////////////////////////////////////////////////
// // 获取特定索引的 Tuple 元素的引用
// template <std::size_t N, typename TupleType>
// typename TupleElemType<N, TupleType>::type& TupleElemGet(TupleType& tuple) {
//     if constexpr (N == 0) {
//         return tuple.head;
//     } else {
//         return TupleElemGet<N - 1>(tuple.tail);
//     }
// }

// using Addr = unsigned char*;

// template<typename T>
// struct Tensor {
//     T* data;
//     std::size_t size;
// };

// template <typename T>
// struct TypeToTensor {
//     using type = Tensor<T>;
// };

// template <typename List>
// struct TensorTuple {
// private:
//     using Tensors = typename TypeList_Map<List, TypeToTensor>::type;
// public:
//     using type = typename TupleFromTypeList<Tensors>::type;
// };

// /////////////////////////////////////////////////////////////////////////////
// enum class ParamType {
//     INPUT,
//     OUTPUT,
//     TEMP,
// };

// template<ParamType PT, typename ... Ts>
// struct ParamTypes{
//     using types = TypeList<Ts...>;
//     static constexpr ParamType usage = PT;
// };

// template<typename ... Ts>
// using Input = ParamTypes<ParamType::INPUT, Ts...>;

// template<typename ... Ts>
// using Output = ParamTypes<ParamType::OUTPUT, Ts...>;

// template<typename ... Ts>
// using Temp = ParamTypes<ParamType::TEMP, Ts...>;

// ///////////////////////////////////////////////////////////////////////////////
// template <typename OP, typename INPUT_TYPES, typename OUTPUT_TYPES, typename TEMP_TYPES = Temp<>>
// class ElemWise {

//     static_assert(INPUT_TYPES::usage  == ParamType::INPUT, "INPUT_TYPES should be INPUT");
//     static_assert(OUTPUT_TYPES::usage == ParamType::OUTPUT, "OUTPUT_TYPES should be OUTPUT");
//     static_assert(TEMP_TYPES::usage   == ParamType::TEMP, "TEMP_TYPES should be TEMP");

//     using INPUTS  = typename INPUT_TYPES::types;
//     using OUTPUTS = typename OUTPUT_TYPES::types;
//     using TEMPS   = typename TEMP_TYPES::types;

//     static constexpr std::size_t INPUT_COUNT  = TypeList_Size<INPUTS>::value;
//     static constexpr std::size_t OUTPUT_COUNT = TypeList_Size<OUTPUTS>::value;
//     static constexpr std::size_t TEMP_COUNT   = TypeList_Size<TEMPS>::value;
//     static constexpr std::size_t ADDR_COUNT   = INPUT_COUNT + OUTPUT_COUNT;

// public:
//     template <typename... Args>
//     void Run(Args&&... args) {
        
//         static_assert(sizeof...(Args) > ADDR_COUNT, "args size is wrong!");

//         auto argsTuple = ForwardAsTuple(std::forward<Args>(args)...);

//         unsigned int count = TupleElemGet<ADDR_COUNT>(argsTuple);

//         FillAddrs(argsTuple, MakeIndexSequence<ADDR_COUNT>{});

//         FillOffsets<INPUTS>(inOffsets_);
//         FillOffsets<OUTPUTS>(outOffsets_);
//         FillOffsets<TEMPS>(tempOffsets_);

//         typename TensorTuple<INPUTS>::type inTensors;
//         typename TensorTuple<OUTPUTS>::type outTensors;
//         typename TensorTuple<TEMPS>::type tempTensors;
    
//         InitInputTensors(inTensors, count, MakeIndexSequence<INPUT_COUNT>{});
//         InitOutputTensors(outTensors, count, MakeIndexSequence<OUTPUT_COUNT>{});
//         InitTempTensors(tempTensors, count, MakeIndexSequence<TEMP_COUNT>{});

//         Compute(inTensors, outTensors, tempTensors, argsTuple,
//                 MakeIndexSequence<INPUT_COUNT>{}, 
//                 MakeIndexSequence<OUTPUT_COUNT>{}, 
//                 MakeIndexSequence<TEMP_COUNT>{}, 
//                 MakeIndexSequence<sizeof...(Args) - ADDR_COUNT - 1>{},
//                 count);
//     }

// private:
//     template <typename TUPLE, std::size_t... Is>
//     void InitInputTensors(TUPLE& tuple, std::size_t cnt, IndexSequence<Is...>) {
//         // 初始化每个 Tensor
//         int dummy[] = { 0, (InitInputTensor(TupleElemGet<Is>(tuple), cnt, Is), 0)... };
//         (void)dummy; // 避免未使用变量警告
//     }

//     template <typename TUPLE, std::size_t... Is>
//     void InitOutputTensors(TUPLE& tuple, std::size_t cnt, IndexSequence<Is...>) {
//         int dummy[] = { 0, (InitOutputTensor(TupleElemGet<Is>(tuple), cnt, Is), 0)... };
//         (void)dummy;
//     }

//     template <typename TUPLE, std::size_t... Is>
//     void InitTempTensors(TUPLE& tuple, std::size_t cnt, IndexSequence<Is...>) {
//         int dummy[] = { 0, (InitTempTensor(TupleElemGet<Is>(tuple), cnt, Is), 0)... };
//         (void)dummy;
//     }

//     template <typename T>
//     Tensor<T>& InitInputTensor(Tensor<T>& tensor, std::size_t cnt, std::size_t index) {
//         tensor.data = reinterpret_cast<T*>(inAddrs_[index] + inOffsets_[index] * cnt);
//         tensor.size = sizeof(T) * cnt;
//         return tensor;
//     }

//     template <typename T>
//     Tensor<T>& InitOutputTensor(Tensor<T>& tensor, std::size_t cnt, std::size_t index) {
//         tensor.data = reinterpret_cast<T*>(outAddrs_[index] + outOffsets_[index] * cnt);
//         tensor.size = sizeof(T) * cnt;
//         return tensor;
//     }

//     template <typename T>
//     Tensor<T>& InitTempTensor(Tensor<T>& tensor, std::size_t cnt, std::size_t index) {
//         tensor.size = sizeof(T) * cnt;
//         return tensor;
//     }

//     template<typename IN_TUPLE, typename OUT_TUPLE, typename TMP_TUPLE, typename ArgsType, 
//             std::size_t... I1, std::size_t... I2,  std::size_t... I3, std::size_t... I4>
//     void Compute(IN_TUPLE& inTensors, OUT_TUPLE& outTensors, TMP_TUPLE& tempTensors, ArgsType&& args,
//                  IndexSequence<I1...>, IndexSequence<I2...>, IndexSequence<I3...>, IndexSequence<I4...>, 
//                  std::size_t cnt) {
//         op_(TupleElemGet<I1>(inTensors)..., 
//             TupleElemGet<I2>(outTensors)..., 
//             TupleElemGet<I3>(tempTensors)..., 
//             cnt, 
//             TupleElemGet<ADDR_COUNT + 1 + I4>(std::forward<ArgsType>(args))...);
//     }

// private:
//     template <typename TupleType, std::size_t... Is>
//     void FillAddrs(TupleType& tuple, IndexSequence<Is...>) {
//         Addr argsArr[ADDR_COUNT] = { TupleElemGet<Is>(tuple)... };
//         for (std::size_t i = 0; i < INPUT_COUNT; ++i) {
//             inAddrs_[i] = argsArr[i];
//         }
//         for (std::size_t i = 0; i < OUTPUT_COUNT; ++i) {
//             outAddrs_[i] = argsArr[INPUT_COUNT + i];
//         }
//     }

//     // 填充 offset 到数组
//     template <typename List, std::size_t... Is>
//     constexpr void FillOffsetsImpl(std::size_t* offsets, IndexSequence<Is...>) {
//         ((offsets[Is] = TypeList_ByteOffset<List, Is>::value), ...);
//     }

//     template <typename List>
//     constexpr void FillOffsets(std::size_t* offsets) {
//         constexpr std::size_t count = TypeList_Size<List>::value;
//         FillOffsetsImpl<List>(offsets, MakeIndexSequence<count>{}); 
//     }

// private:
//     OP op_;

//     Addr inAddrs_[INPUT_COUNT];
//     Addr outAddrs_[OUTPUT_COUNT];

//     std::size_t inOffsets_[INPUT_COUNT];
//     std::size_t outOffsets_[OUTPUT_COUNT];
//     std::size_t tempOffsets_[TEMP_COUNT];
// };

// ///////////////////////////////////////////////////////////////////////////////
// struct KernelAdd {
//     template <typename T>
//     void operator()(Tensor<T> x, Tensor<T> y, Tensor<T> z, std::size_t cnt, bool cond) {
//         if (cond) {
//           for (int i = 0; i < 10; i++) {
//             z.data[i] = x.data[i] + y.data[i];
//           }
//         }
//     }
// };

// /////////////////////////////////////////////////////////////////////////////////////
// extern bool conditon;

// int main() {
//     unsigned char x[10];
//     unsigned char y[10];
//     unsigned char z[10];
//     unsigned char d[10];

//     ElemWise<KernelAdd, Input<int, int>, Output<int>> AddKernel;
//     AddKernel.Run(x, y, z, 10, conditon);

//     return 0;
// }

int main() {
    return 0;
}
