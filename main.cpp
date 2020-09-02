#include "stdafx.h"

INT main(INT argc, LPCSTR *argv) {

			/* ----------- Variables ---------- */
	LPCSTR forkKnifeProcess = "FortniteClient-Win64-Shipping.exe";
	LPCSTR moduleToExpand = "dxgi.dll";

	if (!Comm::Setup()) {
		return 1;
	}
	Comm::Process process(StrToWStr(forkKnifeProcess));
	if (!process.Valid()) {
		printf("Fortnite not found!");
		return 1;
	}

	auto entry = Map::ExtendMap(process, StrToWStr(moduleToExpand));
	if (!entry) {
		return 1;
	}

	printf("\n[-] entry point: %p\n", entry);

	if (!Hijack::HijackViaHook(process, entry, L"user32.dll", "PeekMessageW")) {
		return 1;
	}
	
	return 0;
}