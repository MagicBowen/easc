// #include <cstddef>
// #include "type_list.h"

// #define __aicore__
// #define __global__
// #define KERNEL_FUNC(...)

// using int32_t = int;
// using GM_ADDR = void*;

// namespace AscendC {
//     template <typename T>
//     struct LocalTensor {
//         int GetSize();
//     };
// };

// namespace EasyASC {
//     template<typename ...>
//     struct EleWiseOp {
//         template<typename ...Args>
//         void Run(Args&&... args) {
//         }
//     };

//     template<typename ...Ts>
//     using Input = asl::TypeList<Ts>;

//     template<typename ...Ts>
//     using Output = asl::TypeList<Ts>;

//     template<typename ...Ts>
//     using Temp = asl::TypeList<Ts>;
// }

// using namespace AscendC;
// using namespace EasyASC;

// struct SinhComputeFunc {
//     /*
//     函数说明： y = (e^x - e^(-x)) / 2
//     */
//     template<typename T, typename U>
//     __aicore__ inline void operator()(LocalTensor<T> x, LocalTensor<T> y, 
//                                       LocalTensor<U> tempBuffer1, 
//                                       LocalTensor<U> tempBuffer2) {
//         uint32_t tiledCnt = y.GetSize();
//         AscendC::Exp(tempBuffer1, x, tiledCnt);
//         AscendC::Muls(tempBuffer2, x, static_cast<T>(-1), tiledCnt);
//         AscendC::Exp(tempBuffer2, tempBuffer2, tiledCnt);
//         AscendC::Sub(y, tempBuffer1, tempBuffer2, tiledCnt);
//         AscendC::Muls(y, y, static_cast<T>(0.5), tiledCnt);
//     }
// };

// extern "C" __global__ __aicore__ void SinhCustom(GM_ADDR x, GM_ADDR y, int32_t totalCnt) {
//     EleWiseOp<SinhComputeFunc, Input<float>, Output<float>, Temp<float, float>>().Run(x, y, totalCnt);
// }
