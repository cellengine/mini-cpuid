A tiny, cross-platform module to execute `cpuid`. Intended to be used in
binding.gyp files to set MSVC's `/arch` in the same way that gcc and clang
support `-march=native`, but can be used to retrieve any info.

### In binding.gyp:

```gyp
  ...
  "msvs_settings": {
    "VCCLCompilerTool": {
      "AdditionalOptions": [
        "<!@(node -p \"require('mini-cpuid').getArch()\")"
      ]
    }
  }
  ...
```

### API

> ```ts
> cpuid.getArch(): "/arch:AVX"|"/arch:AVX2"|"/arch:AVX512"|""
> ```

Currently supports x86_64.

> ```ts
> cpuid.cpuid(outRegIdx: number, initEax: number, initEcx: number = 0): number
> ```

Returns the `outRegIdx`th (0-3) register value (a uint32) after calling `cpuid`
with the initial EAX and ECX values `initEax` and `initEcx`, respectively.

Example:

```js
import cpuid from "mini-cpuid";
// Get EBX register value when `cpuid` is invoked with EAX set to 7:
const ebx = cpuid(1, 7);
// Test if AVX2 is supported:
const isAVX2Supported = ebx & (1 << 5);
```

### Notes

* *Why use `AdditionalOptions` instead of `EnableEnhancedInstructionSet`?*
  Because the latter doesn't support AVX-512.

* *Why not use one of the other cpuid npm modules?* As of July 2022, they're
  either big (depend on libCPUID), not maintained and/or not cross-platform.

* *Why not use CPU dispatching?* If you're shipping prebuilt Node.js modules,
  you should do this. But if you're compiling locally, dispatching requires
  creating per-extension builds, which increases code size.
