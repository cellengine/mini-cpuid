const {cpuid} = require("./build/Release/cpuid.node");

const EAX = 0;
const EBX = 1;
const ECX = 2;
const EDX = 3;

function supportsAVX() {
	return cpuid(ECX, 1) & (1 << 28) !== 0;
}

function supportsAVX2() {
	return cpuid(EBX, 7) & (1 << 5) !== 0;
}

function supportsAVX512() {
	// 30 is AVX512_BW.
	return cpuid(EBX, 7) & (1 << 30) !== 0;
}

module.exports.getArch = function getArch() {
	if (supportsAVX512())
		return "/arch:AVX512";
	if (supportsAVX2())
		return "/arch:AVX2";
	if (supportsAVX())
		return "/arch:AVX";
	return ""; // SSE2 default for x86_64
}

module.exports.cpuid = cpuid;
