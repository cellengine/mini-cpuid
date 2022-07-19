export function getArch(): "/arch:AVX"|"/arch:AVX2"|"/arch:AVX512"|"";
export function cpuid(outRegIdx: number, initEax: number, initEcx?: number): number
