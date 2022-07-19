#include "napi.h"
#include <cstdint>

#if defined(__x86_64__) || defined(_M_X64)

#ifdef __GNUC__
# include <immintrin.h>
#elif defined(_MSC_VER)
# include <intrin.h>
#endif

using std::uint8_t;
using std::uint32_t;

static uint32_t cpuid_(uint8_t outreg, uint32_t initEax, uint32_t initEcx = 0) {
	uint32_t regs[4];
#ifdef _MSC_VER
	__cpuidex(reinterpret_cast<int32_t*>(regs), initEax, initEcx);
#else
	asm volatile("cpuid"
		: "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
		: "0" (initEax), "2" (initEcx));
#endif
	return regs[outreg];
}

Napi::Number cpuid(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	const uint8_t outreg = static_cast<uint8_t>(info[0].ToNumber().Uint32Value());
	const uint32_t initEax = info[1].ToNumber().Uint32Value();
	const uint32_t initEcx = info[2].IsNumber() ? info[2].ToNumber().Uint32Value() : 0;
	return Napi::Number::New(env, cpuid_(outreg, initEax, initEcx));
}

#else // x86_64
// TODO put ARM IID_AA64_ISAR here
Napi::Number cpuid(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	return Napi::Number::New(env, 0);
}

#endif // x86_64

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set(Napi::String::New(env, "cpuid"), Napi::Function::New(env, cpuid));
	return exports;
}

NODE_API_MODULE(cpuid, Init)
