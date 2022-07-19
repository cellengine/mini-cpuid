{
	"targets": [{
		"target_name": "cpuid",
		"cflags!": [
			"-fno-exceptions",
		],
		"cflags_cc!": [
			"-fno-exceptions",
		],
		"cflags_cc": [
			"-Wall", "-Wpedantic", "-Wextra",
		],
		"msvs_settings": {
			"VCCLCompilerTool": {
				"ExceptionHandling": 1,
				"AdditionalOptions": [
					"/arch:AVX2"
				],
			},
		},
		"sources": [
			"init.cc"
		],
		"include_dirs": [
			"<!@(node -p \"require('node-addon-api').include\")",
		],
		"conditions": [
			['OS=="mac"', {
				"cflags+": [
					"-fvisibility=hidden"
				],
				"xcode_settings": {
					"GCC_SYMBOLS_PRIVATE_EXTERN": "YES", # -fvisibility=hidden
					"GCC_ENABLE_CPP_EXCEPTIONS": "YES",
					"CLANG_CXX_LIBRARY": "libc++",
					"MACOSX_DEPLOYMENT_TARGET": "10.15",
				},
			}],
			['OS=="win"', {
				"defines": [
					"_HAS_EXCEPTIONS=1"
				],
			}],
		]
	}]
}
